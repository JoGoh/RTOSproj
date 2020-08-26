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
#include "Pwm.h"
#include "Ccm.h"
#include "motors.h"
#include "Encoder.h"
#include "PID.h"
#include "UltraSound.h"
#include "Serial.h"
#include "i2c.h"
#include "PololuV5.h"
#include "imu.h"
#include "term.h"

#include "Dma.h"
#include "Spim.h"
#include "LCD.h"
#include "gui.h"
#include "Cube3D.h"
#include "ips.h"
/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS				500
#define LCD_BUF_SIZE			4096
#define LCD_UPDATE_MS			5

#define TIMER5_TICK_HZ				2000U		/* 2KHz */
#define ENCODER_SMPL_INTRVL_MS		100U		/* 100ms */

#define DEFAULT_DUTY				20
#define PID_TARGET_DEFAULT_RPM		35
#define DUTY_CYCLE_MIN				06U
#define DUTY_CYCLE_MAX				50U
#define OUTPUT_FACTOR				0.072f

#define NEAR_DIST 100
#define FAR_DIST 150
#define SENSOR_DIST 2000
#define SENSOR_NEAR_DIST 1500
#define SENSOR_FAR_DIST 10000

#define IPS_DELAY_MS                    50
/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
void GUI_AppDraw( BOOL bFrameStart );


/*****************************************************************************
 Const Local Variables
******************************************************************************/
extern double  g_nCurrentCoordinate[2]; /*[0]= x-coord, [1]= y-coord (ips.c)*/

/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int 		g_nSysTick 			= SYS_TICK_MS;
static volatile BOOL 		g_bSysTickReady 	= FALSE;

static volatile int			g_nLCDTick			= LCD_UPDATE_MS;
static volatile BOOL		g_bLCDUpdate		= FALSE;

static BOOL					g_bBlueToggle		= FALSE;
static BOOL					g_bRedToggle		= FALSE;

static SPIM_HANDLE			g_SpimLcdHandle;
static GUI_DATA				g_aBuf[LCD_BUF_SIZE];
static GUI_MEMDEV			g_MemDev;

static SPIM_HANDLE			g_SpimUWBHandle;

static double				g_nCount			= 0;
static uint8_t				g_nMove				= 0;
static BOOL					g_bFwd				= TRUE;
volatile BOOL				g_bLcdFree			= TRUE;

static DMA_HANDLE			g_Dma1Spi2TxHandle;
static DMA_HANDLE			g_Dma1Spi2RxHandle;

static volatile int			g_nDelayms			= 0;
static 	char				g_aStrbuf[64];


static TIMER_HANDLE			g_Timer5Handle;

static SHAFT_ENC_HANDLE		g_ShaftEncHandles[TOTAL_MOTOR];
static volatile BOOL		g_bEncoderData = FALSE;

static CCM_HANDLE			g_CcmHandles[TOTAL_MOTOR];
static int16_t g_rpm[4];
static double g_SetX_Coord = 0.0;
static double g_SetY_Coord = 0.0;
static double g_SetXYCoord[20] = {150,130};
//static double g_CurrentCoordinate[20] = {130,150};
static volatile int x = 0, y = 1;
static volatile double Current_X = 0, Current_Y = 0, True_XY_dist = 0,
                       Diag_XY_Dist = 0;
static volatile int algo = 0, g_nAlgo = 0;

static volatile int statechange1 = 0;
static volatile int Movright = 0;
static BOOL                              g_bIPS = FALSE;
static volatile int                     g_nIPSDelayms                    =IPS_DELAY_MS;


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void );
static void main_LcdInit( void );

static void main_EncodersInit( void );
/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbGuiFrameEnd( void );
static void main_cbLcdTransferDone( void );

static void main_cbEncoderRdy( void );
static void main_CtrlUpdateWheelSpeed( void );
static void main_I2cInit(void);
static float main_convertRawAcceleration(int16_t nRaw);
static float main_convertRawGyro(int16_t nRaw);
static float main_convertRawMag(int nRaw);
static void main_ImuUpdate(void);
static void main_Delayms(int ms);
/*****************************************************************************
 Implementation 
******************************************************************************/
int main( void )
{
	int res;

        
    IMU_POLOLU_STS imuSts;
    BSPInit();
	
	TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz", SystemCoreClock );

	/* Generate interrupt each 1 ms as system tick */
	SysTick_Config( SystemCoreClock/1000 );

	main_SpimInit();

	main_LcdInit(); /* LCD initialization */
    TimerInit( &g_Timer5Handle, 5, TIMER5_TICK_HZ );

	main_EncodersInit();

    MotorsInit();

	MotorsPIDConfig(
		DEFAULT_DUTY,
		PID_TARGET_DEFAULT_RPM,
		ENCODER_SMPL_INTRVL_MS,
		DUTY_CYCLE_MIN,
		DUTY_CYCLE_MAX,
		OUTPUT_FACTOR );

	/* NOTE: At start, Motors shall stops for Safety issue */
    MotorsStop();
 /* IMU Power up sequence */
//  IMU_PWR_OFF();
//  main_Delayms(100);
//  IMU_PWR_ON();
//
//  main_Delayms(100);
//
//  main_I2cInit();
//
//  main_Delayms(100);

	/* Move front */
	
    MotorsMoveFront( DEFAULT_DUTY );
	/* Kick timer to run */
    TimerStart( &g_Timer5Handle );

//   IpsInit( &g_SpimUWBHandle );
 /*IMU*/
  /* TODO: */
  /* Students can test for the rest of the direction */
  // imuSts = ImuPololuInit( &g_I2cHandle, &g_Timer1Handle, TIMER1_TICK_HZ, 100 );
//  imuSts = ImuPololuInit(&g_I2cHandle, &g_Timer6Handle, TIMER5_TICK_HZ, 100);
//  ASSERT(IMU_POLOLU_STS_OK == imuSts);
//  TRACE("IMU OK\r\n");
//
//  ImuInit(FALSE);
//
//
//
//  /* If using fix sample rate */
//  //  ImuSetSampleRate( IMU_SAMLE_FREQ );
//
//  g_nImuCalCount = 40;
     IpsInit( &g_SpimUWBHandle );

   IRQInit();

	/* Runtime for loop */
    for(;;)
    {
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
                if(g_bIPS)
                {
                    g_bIPS = FALSE;
                      IpsTimer();
                      }
                   Current_X = ABS( g_SetXYCoord[x] - g_nCurrentCoordinate[0] );
                   Current_Y = ABS( g_SetXYCoord[y] - g_nCurrentCoordinate[1] );
                      if(Current_X >= FAR_DIST && Current_Y>=FAR_DIST)
                       {
                           if(statechange1==0)
                           {
                               MotorsMoveFront(DEFAULT_DUTY);
                               statechange1=1;
                           }
  
                       }
                       if((g_nCurrentCoordinate[0]>=g_SetXYCoord[x]) &&
                       (g_nCurrentCoordinate[0]<=g_SetXYCoord[x]+50)) //X movement
                       {
                          if(Movright==0)
                          {
                            MotorsMoveRight(DEFAULT_DUTY);
                            Movright=1;
                          }
                       }
                       if((g_nCurrentCoordinate[1]>=g_SetXYCoord[y]) &&
                       (g_nCurrentCoordinate[1]<=g_SetXYCoord[y]+50)) //Y movement
                       {
                          if(Movright==0)
                          {
                            MotorsMoveRight(DEFAULT_DUTY);
                            Movright=1;
                          }
                       }
//                          if((g_CurrentCoordinate[0]>=g_SetXYCoord[x]) &&
//                           (g_CurrentCoordinate[0]<=g_SetXYCoord[x]+50)) //X movement
//                           {
//                              if(Movright==0)
//                              {
//                                MotorsMoveLeft(DEFAULT_DUTY);
//                                Movright=1;
//                              }
//                           }
//                           if((g_CurrentCoordinate[1]>=g_SetXYCoord[y]) &&
//                           (g_CurrentCoordinate[1]<=g_SetXYCoord[y]+50)) //Y movement
//                           {
//                              if(Movright==0)
//                              {
//                                MotorsMoveRight(DEFAULT_DUTY);
//                                Movright=1;
//                              }
//                           }
		}
                  

                if( TRUE == g_bEncoderData )
		{
			/* Only Encoder data count is ready only will execute */
			g_bEncoderData = FALSE;
			main_CtrlUpdateWheelSpeed();
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

//        double Xcoord =0,Ycoord =0;

	if( TRUE == bFrameStart )
	{
		g_nCount++;

		if( TRUE == g_bFwd )
		{
			g_nMove++;
			if( g_nMove > 40 )
			{
				g_bFwd = FALSE;
			}
		}
		else
		{
			if( 0 != g_nMove )
			{
				g_nMove--;
				if( 0 == g_nMove )
				{
					g_bFwd = TRUE;
				}
			}
		}
//              Xcoord= IPSGetPositionX();
//              Ycoord= IPSGetPositionX();

//		sprintf(
//			g_aStrbuf,
//			"B0:%.2f\r\nB1:%.2f\r\nB2:%.2f\r\n%.2f",
//			IPSGetDistance( 0 ),
//            IPSGetDistance( 1 ),
//            IPSGetDistance( 2 ),
//			g_nCount );
                    sprintf( g_aStrbuf,
                     "B1: %.2f\r\nB2: %.2f\r\nB3: %.2f\r\nX-Cord: "
                     "%.2f\r\nY-Cord: %.2f\r\n",
                     IPSGetDistance( 0 ), IPSGetDistance( 1 ),
                     IPSGetDistance( 2 ), g_nCurrentCoordinate[0],
                    g_nCurrentCoordinate[1]);

//                     sprintf( g_aStrbuf,
//                     "B1: %.2f\r\nB2: %.2f\r\nB3: %.2f\r\nX-Cord: "
//                     "%.2f\r\nY-Cord: %.2f\r\n",
//                      g_dIpsCoordinate[0],
//                     IPSGetPositionY());

//                     sprintf( g_aStrbuf,
//                     "B1: %.2f\r\nB2: %.2f\r\nB3: %.2f\r\nX-Cord: "
//                     "%.2f\r\nY-Cord: %.2f\r\n",
//                     IPSGetDistance( 0 ), IPSGetDistance( 1 ),
//                     IPSGetDistance( 2 ), Xcoord,Ycoord);

//                     sprintf(
//            g_aStrbuf,
//            "Encoder1:%d\n\rEncoder2:%d\n\rEncoder3:%d\n\rEncoder4:%d\n\r",
//            g_rpm[0], g_rpm[1], g_rpm[2], g_rpm[3] );


	}
	
 GUI_SetFont(&g_sFontCalibri10);
//  GUI_PrintString(g_aLcdString, ClrWhite, 10, 10);
/* Set background to blue.Refer to gui.h for color code */
	GUI_Clear( ClrBlue ); 

	/* Display string */
	//GUI_SetFont( GUI_ARIMO20_FONT );
	GUI_PrintString( "DP GUI", ClrLawnGreen, 1, 1 );

	//GUI_SetFont( GUI_CONSOLE10_FONT );
	GUI_PrintString( g_aStrLcdBuf, ClrWhite, 1, 10 );


static void main_cbLcdTransferDone( void )
{
	g_bLcdFree = TRUE;
}


static void main_cbGuiFrameEnd( void )
{
	g_bLcdFree = TRUE;
}

static void main_cbEncoderRdy( void )
{
	g_bEncoderData = TRUE;
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


	/* UWB SPI */
    SpimInit(
		&g_SpimUWBHandle,
		1,
		1000000,
		SPI_CLK_INACT_LOW,
		SPI_CLK_RISING_EDGE,
		SPI_DATA_SIZE_8 );
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
    
    /* Set font */
    //GUI_SetFont( GUI_ARIMO20_FONT );
	
	LCD_AddCallback( main_cbLcdTransferDone );
	
	GUI_AddCbFrameEnd( main_cbGuiFrameEnd );
	
	/* Backlight ON */
	LCD_BL_ON();
}
static void main_EncodersInit( void )
{
	int res;
	res = CCMInit( &g_CcmHandles[0], 1U );
	ASSERT( CCM_OK == res );

	res = CCMInit( &g_CcmHandles[1], 3U );
	ASSERT( CCM_OK == res );

	res = CCMInit( &g_CcmHandles[2], 2U );
	ASSERT( CCM_OK == res );

	res = CCMInit( &g_CcmHandles[3], 4U );
	ASSERT( CCM_OK == res );

	CCMEncoderMode( &g_CcmHandles[0], CCM_ENC_INPUT_AB );
	CCMEncoderMode( &g_CcmHandles[1], CCM_ENC_INPUT_AB );
        CCMEncoderMode( &g_CcmHandles[2], CCM_ENC_INPUT_AB );
	CCMEncoderMode( &g_CcmHandles[3], CCM_ENC_INPUT_AB );

	ShaftEncoderInit(
		&g_Timer5Handle,
		TIMER5_TICK_HZ,
		main_cbEncoderRdy,
		ENCODER_SMPL_INTRVL_MS );

	ShaftEncoderCfg(
		64,
		70,
		ENCODER_SMPL_INTRVL_MS );

	/* Add 4 available encoders */
	ShaftEncoderAdd( &g_ShaftEncHandles[0], 0, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[1], 1, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[2], 2, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[3], 3, 0 );

	/* Link to CCM for high performance */
        ShaftEncoderLinkCCM( &g_ShaftEncHandles[0], &g_CcmHandles[0] );
        ShaftEncoderLinkCCM( &g_ShaftEncHandles[1], &g_CcmHandles[1] );
        ShaftEncoderLinkCCM( &g_ShaftEncHandles[2], &g_CcmHandles[2] );
	ShaftEncoderLinkCCM( &g_ShaftEncHandles[3], &g_CcmHandles[3] );
}

/*****************************************************************************
 Local functions
******************************************************************************/

static void main_CtrlUpdateWheelSpeed( void )
{
	int			rpm;
	uint32_t	cnt;

	TRACE("Encoder : ");
	for( cnt=0; cnt<TOTAL_MOTOR; cnt++ )
	{
		rpm = ShaftEncoderReadRPM( &g_ShaftEncHandles[cnt] );
		TRACE( "%d ", rpm );
                g_rpm[cnt] = rpm;
		if( rpm<0 )
		{
			rpm = -rpm;
		}
	
		if( (0 != rpm)&&(-1 != rpm) )
		{
			if( rpm<0 )
			{
				rpm = -rpm;
			}

			/* PID running */
			MotorsRunPID( cnt, rpm );
		}
	}
	TRACE("\r\n");
}

/*****************************************************************************
 Interrupt functions
******************************************************************************/
void SysTick_Handler( void )
{
	/* NOTE:
	It is more efficient to compare to 0 for Cortex M
	*/

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
			g_bSysTickReady = TRUE;
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
           if( 0 != g_nIPSDelayms )
	{
		g_nIPSDelayms--;
		
		if( 0 == g_nIPSDelayms )
		{
			g_nIPSDelayms = IPS_DELAY_MS;
			g_bIPS = TRUE;
		}
	}

    IPSSysTimeout1msTimer();
}

