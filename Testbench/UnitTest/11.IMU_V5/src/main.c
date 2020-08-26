/*****************************************************************************
 @Project	: 
 @File 		: main.c
 @Details  	: Main entry         
 @Author	: lcgan
 @Hardware	: STM32
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "BSP.h"
#include "IRQ.h"
#include "Timer.h"
#include "i2c.h"
#include "PololuV5.h"
#include "imu.h"

#include "Dma.h"
#include "Spim.h"
#include "LCD.h"
#include "gui.h"


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS					500
#define TIMER1_TICK_HZ				2000U		/* 2KHz */

#define LCD_BUF_SIZE				4096
#define LCD_UPDATE_MS				5

/*****************************************************************************
 Type definition
******************************************************************************/
#define IMU_TICK_MS					100U
#define IMU_SAMLE_FREQ				5.0f		/* IMU sample frequency in Hz */


/*****************************************************************************
 Global Variables
******************************************************************************/
void GUI_AppDraw( BOOL bFrameStart );


/*****************************************************************************
 Const Local Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int 		g_nSysTick 			= SYS_TICK_MS;
static volatile BOOL 		g_bLEDToggle		= FALSE;
static volatile int			g_nDelayms			= 0;

static TIMER_HANDLE			g_Timer1Handle;
static I2C_HANDLE			g_I2cHandle;

static volatile BOOL		g_bImuTick		= FALSE;
static volatile int			g_nImuTick		= IMU_TICK_MS;

static IMU_POLOLU_DATA		g_ImuData;
static float				g_dPitch;
static float				g_dRoll;
static float				g_dYaw;
static int16_t				g_aImuOffset[3];
static volatile int			g_nImuCalCount		= 0;
static volatile	int			g_nTimestamp = 0;
static volatile	int			g_nImuSync = 0;

static volatile int			g_nLCDTick			= LCD_UPDATE_MS;
static volatile BOOL		g_bLCDUpdate		= FALSE;
static SPIM_HANDLE			g_SpimLcdHandle;
static GUI_DATA				g_aBuf[LCD_BUF_SIZE];
static GUI_MEMDEV			g_MemDev;
static DMA_HANDLE			g_Dma1Spi2TxHandle;
static DMA_HANDLE			g_Dma1Spi2RxHandle;
static volatile BOOL		g_bLcdFree			= TRUE;
static char					g_aLcdString[128];


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_I2cInit( void );
static float main_convertRawAcceleration( int16_t nRaw );
static float main_convertRawGyro( int16_t nRaw );
static float main_convertRawMag( int nRaw );
static void main_ImuUpdate( void );
static void main_SpimInit( void );
static void main_LcdInit( void );
static void main_Delayms( int ms );


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbGuiFrameEnd( void );
static void main_cbLcdTransferDone( void );


/*****************************************************************************
 Implementation 
******************************************************************************/
/* NOTE: 
 This example is to use PWM to turn motors in 8 directions.
 This program is prepared based on Pin Assignment Table and its wheel direction
*/

int main( void )
{
	 IMU_POLOLU_STS      imuSts;

	/* Board Support Package initialization */
    BSPInit();
	
	TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz", SystemCoreClock );

	/* WARNING:
	 System tick is called direct from ARM Core. Do not use for heavy processing.
	 System tick normally use for increase or decrease a counter or set/reset a flag.
	 Heavy processing in System Tick will caused MCU not responsive!
	*/
	/* Generate interrupt each 1 ms as system tick */
	SysTick_Config( SystemCoreClock/1000 );

	TimerInit( &g_Timer1Handle, 5, TIMER1_TICK_HZ );

    main_SpimInit();

	main_LcdInit(); /* LCD intialization */

	IMU_PWR_OFF();
	main_Delayms( 100 );
    IMU_PWR_ON();

	main_Delayms( 100 );

	main_I2cInit();

	main_Delayms( 100 );

	/* Kick timer to run */
    TimerStart( &g_Timer1Handle );

    imuSts = ImuPololuInit( &g_I2cHandle, &g_Timer1Handle, TIMER1_TICK_HZ, 100 );
	ASSERT( IMU_POLOLU_STS_OK == imuSts );
	TRACE( "IMU OK\r\n" );

	ImuInit( FALSE );

	/* If using fix sample rate */
  //  ImuSetSampleRate( IMU_SAMLE_FREQ );

	g_nImuCalCount = 40;



    IRQInit();

	/* TODO: */
	/* Students can test for the rest of the direction */


	/* Runtime for loop */
    for(;;)
    {
		/******************************
		 IMU processing - sample at 200ms
		*******************************/
		if( FALSE != g_bImuTick )
		{
			g_bImuTick = FALSE;

			main_ImuUpdate();
		}

        /* NOTE: 
		 LCD periodically update
		*/
		if( FALSE != g_bLCDUpdate )
		{
			if( 0 != g_bLcdFree )
			{
				g_bLCDUpdate = FALSE;
				g_bLcdFree = FALSE;

			   /* Draw every block.Consume less time  */
				GUI_Draw_Exe(); 
			}
		}

	}
}


/*****************************************************************************
 Callback functions
******************************************************************************/
void GUI_AppDraw( BOOL bFrameStart )
{
 /* NOTE: 
  This is the callback from GUI library. */
	if( TRUE == bFrameStart )
	{


		if( 0 != g_nImuCalCount )
		{
			sprintf(
				g_aLcdString,
				"DO NOT MOVE.\r\nCalibrating...\r\n %d",
				g_nImuCalCount );
		}
		else
		{
        	sprintf( 
				g_aLcdString,
				"Roll:%.2f\r\nYaw:%.2f\r\nPitch:%.2f",
				g_dRoll,
				g_dYaw,
				g_dPitch );
		}
	}
	
	/* Set background to blue.Refer to gui.h for color code */
	GUI_Clear( ClrBlue ); 

	/* Display string */
	GUI_SetFont( &g_sFontCalibri24 );
	GUI_PrintString( "DP GUI", ClrLawnGreen, 10, 10 );

	GUI_SetFont( &g_sFontCalibri10 );
	GUI_PrintString( g_aLcdString, ClrYellow, 10, 50 );
}


static void main_cbLcdTransferDone( void )
{
	g_bLcdFree = TRUE;
}


static void main_cbGuiFrameEnd( void )
{
	g_bLcdFree = TRUE;
}


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void )
{
	int res;

	res = DmaInit(
			&g_Dma1Spi2TxHandle,
			1,
			DMA1_SPI2_TX_CH,
			0,
			DMA_DIR_MEM_TO_PERI,
			DMA_MEM_INC_EN,
			DMA_DATA_ALIGN_BYTE,
			DMA_PERI_INC_DIS,
			DMA_DATA_ALIGN_BYTE );
	ASSERT( DMA_OK == res );

	res = DmaInit(
			&g_Dma1Spi2RxHandle,
			1,
			DMA1_SPI2_RX_CH,
			0,
			DMA_DIR_PERI_TO_MEM,
			DMA_MEM_INC_DIS,
			DMA_DATA_ALIGN_BYTE,
			DMA_PERI_INC_DIS,
			DMA_DATA_ALIGN_BYTE );
	ASSERT( DMA_OK == res );

	/* LCD SPI */
	NVIC_SetPriority( SPI2_IRQn, 0x0f );
	SpimInit(
		&g_SpimLcdHandle,
		2,
		25000000,
		SPI_CLK_INACT_LOW,
		SPI_CLK_RISING_EDGE,
		SPI_DATA_SIZE_8 );

	SpimLinkDMA(
		&g_SpimLcdHandle,
		&g_Dma1Spi2TxHandle,
		&g_Dma1Spi2RxHandle );	
}


static void main_LcdInit( void )
{
	int screenx;
	int screeny;
	int res;
	
	/* g_SpimLcdHandle shall be initialized before use */
	
	/* Choosing a landscape orientation */
	LcdInit( &g_SpimLcdHandle, LCD_PORTRAIT );
	
	/* Get physical LCD size in pixels */
	LCD_GetSize( &screenx, &screeny );
	
	/* Initialize GUI */
	GUI_Init(
		&g_MemDev,
		screenx,
		screeny,
		g_aBuf,
		sizeof(g_aBuf) );


	res = DmaInit(
			&g_Dma1Spi2TxHandle,
			1,
			DMA1_SPI2_TX_CH,
			0,
			DMA_DIR_MEM_TO_PERI,
			DMA_MEM_INC_EN,
			DMA_DATA_ALIGN_HALF_WORD,
			DMA_PERI_INC_DIS,
			DMA_DATA_ALIGN_HALF_WORD );
	ASSERT( DMA_OK == res );

	res = DmaInit(
			&g_Dma1Spi2RxHandle,
			1,
			DMA1_SPI2_RX_CH,
			0,
			DMA_DIR_PERI_TO_MEM,
			DMA_MEM_INC_DIS,
			DMA_DATA_ALIGN_HALF_WORD,
			DMA_PERI_INC_DIS,
			DMA_DATA_ALIGN_HALF_WORD );
	ASSERT( DMA_OK == res );


	GUI_16BitPerPixel( TRUE );

    	/* Switch to transfer word for faster performance */
	SpimSetDataSize( &g_SpimLcdHandle, SPI_DATA_SIZE_16 );
	/* Clear LCD screen to Blue */
	GUI_Clear( ClrBlue );

    /* set font color background */
    GUI_SetFontBackColor( ClrBlue );
	
	LCD_AddCallback( main_cbLcdTransferDone );
	
	GUI_AddCbFrameEnd( main_cbGuiFrameEnd );
	
	/* Backlight ON */
	LCD_BL_ON();
}


static void main_I2cInit( void )
{
	int res;
		
	res = I2cInit( &g_I2cHandle, 1, 400000U );
	ASSERT( I2C_STS_OK == res );
}


static float main_convertRawAcceleration( int16_t nRaw )
{
	float a = (float)((int32_t)nRaw) * 0.000061f;
	return a;
}


static float main_convertRawGyro( int16_t nRaw )
{
	float g = (float)((int32_t)nRaw)  * 0.00875f; 
	return g;
}


static float main_convertRawMag( int nRaw )
{
	float g = (float)((int32_t)nRaw)  / 6842.0f;
	return g;
}


static void main_ImuUpdate( void )
{
    IMU_POLOLU_STS	imuSts;
    IMU_DATA		data;
	int16_t gx;
	int16_t gy;
    int16_t gz;
	int timestamp = g_nTimestamp;

	imuSts = ImuPololuReadData( &g_ImuData );
	if( IMU_POLOLU_STS_OK == imuSts )
	{
		/* Calibration will happen if g_nImuCalCount is none zero */
		if( 0 != g_nImuCalCount )
		{
			g_nImuCalCount--;
			if( 0 == g_nImuCalCount )
			{
				g_aImuOffset[0] = g_ImuData.nGyroX;
				g_aImuOffset[1] = g_ImuData.nGyroY;
				g_aImuOffset[2] = g_ImuData.nGyroZ;

				TRACE( "IMU calibrated\r\n" );

				g_nImuSync = 5;
			}
			else
			{
				/* Calibration Offset have not yet done */
				return;
			}
		}
#if 1
		TRACE( "Accl: %d %d %d  Gyro: %d %d %d\r\n", 
			g_ImuData.nAcclX,
			g_ImuData.nAcclY,
			g_ImuData.nAcclZ,
			g_ImuData.nGyroX,
			g_ImuData.nGyroY,
			g_ImuData.nGyroZ );
#endif

		if( 0 != g_nImuSync )
		{
			g_nImuSync--;
			g_nTimestamp = 0;

			return;
		}

		gx = g_ImuData.nGyroX;
		if( ABS(g_ImuData.nGyroX - g_aImuOffset[0]) < 40 )
		{
             gx = g_aImuOffset[0];
		}

		gy = g_ImuData.nGyroY;
		if( ABS(g_ImuData.nGyroY - g_aImuOffset[1]) < 40 )
		{
             gy = g_aImuOffset[1];
		}

		gz = g_ImuData.nGyroZ;
		if( ABS(g_ImuData.nGyroZ - g_aImuOffset[2]) < 40 )
		{
             gz = g_aImuOffset[2];
		}

		data.gx = main_convertRawGyro( gx - g_aImuOffset[0] );
		data.gy = main_convertRawGyro( gy - g_aImuOffset[1] );
		data.gz = main_convertRawGyro( gz - g_aImuOffset[2] );
		data.ax = main_convertRawAcceleration( g_ImuData.nAcclX );
		data.ay = main_convertRawAcceleration( g_ImuData.nAcclY );
		data.az = main_convertRawAcceleration( g_ImuData.nAcclZ );

		/* Set timestamp to 0 if using fix sample rate */
		ImuUpdateAcclGyro( &data, timestamp );
        g_nTimestamp = 0;
#if 1
		ImuComputeResult( &g_dRoll, &g_dPitch, &g_dYaw );

		TRACE( "%.2f %.2f %.2f, %d\r\n", g_dRoll, g_dPitch, g_dYaw, timestamp );
#endif
	}
	else
	{
		LED_BLUE_ON();
	}
}


static void main_Delayms( int ms )
{
	g_nDelayms = ms;
	while( 0 != g_nDelayms );
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void SysTick_Handler( void )
{
	/* NOTE:
	It is more efficient to compare to 0 for Cortex M
	*/
	g_nTimestamp++;

	if( 0 != g_nDelayms )
	{
		g_nDelayms--;
	}

	/* Provide system tick with a specified period 
	decided by macro SYS_TICK_MS */
	if( 0 != g_nSysTick )
	{
		g_nSysTick--;
		
		if( 0 == g_nSysTick )
		{
			g_nSysTick = SYS_TICK_MS;

			g_bLEDToggle = !g_bLEDToggle;
            LED_RED_SET( g_bLEDToggle );
		}
	}

	/* IMU Tick */
	if( 0 != g_nImuTick )
	{
		g_nImuTick--;
		if( 0 == g_nImuTick )
		{
			g_nImuTick = IMU_TICK_MS;
			g_bImuTick = TRUE;
		}
	}

    if( 0 != g_nLCDTick )
	{
		g_nLCDTick--;
		if( 0 == g_nLCDTick )
		{
			g_nLCDTick = LCD_UPDATE_MS;
			g_bLCDUpdate = TRUE;
		}
	}
}

