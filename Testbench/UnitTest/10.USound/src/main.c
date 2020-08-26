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
#include "Timer.h"
#include "Dma.h"
#include "Spim.h"
#include "LCD.h"
#include "gui.h"
#include "UltraSound.h"
#include "IRQ.h"


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS				500
#define LCD_BUF_SIZE			4096
#define LCD_UPDATE_MS			5
#define TIMER9_TICK_HZ			10000U		/* 10KHz */

#define USONIC_TOTAL			8U


/*****************************************************************************
 Type definition
******************************************************************************/
typedef union _tagUsonic_State
{
	uint8_t nState;

	struct
	{
		uint8_t bUS1	:1;
		uint8_t bUS2	:1;
		uint8_t bUS3	:1;
		uint8_t bUS4	:1;
		uint8_t bUS5	:1;
		uint8_t bUS6	:1;
		uint8_t bUS7	:1;
		uint8_t bUS8	:1;
	}b;
} USONIC_STATE, *PUSONIC_STATE;


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
static volatile BOOL 		g_bSysTickReady 	= FALSE;

static volatile int			g_nLCDTick			= LCD_UPDATE_MS;
static volatile BOOL		g_bLCDUpdate		= FALSE;

static BOOL					g_bBlueToggle		= FALSE;
static BOOL					g_bRedToggle		= FALSE;

static SPIM_HANDLE			g_SpimLcdHandle;
static GUI_DATA				g_aBuf[LCD_BUF_SIZE];

static GUI_MEMDEV			g_MemDev;

static double				g_nCount			= 0;
volatile BOOL				g_bLcdFree			= TRUE;

static DMA_HANDLE			g_Dma1Spi2TxHandle;
static DMA_HANDLE			g_Dma1Spi2RxHandle;

static volatile int			g_nDelayms			= 0;

static TIMER_HANDLE			g_Timer9Handle;

static USONIC_HANDLE		g_USHandles[USONIC_TOTAL];
static uint32_t				g_aUsonicDist[USONIC_TOTAL];
static USONIC_STATE			g_UsonicState;

static char					g_aLcdString[512];


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void );
static void main_LcdInit( void );
static void main_USoundInit( void );


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbGuiFrameEnd( void );
static void main_cbLcdTransferDone( void );

static void main_cbUS1OnTrigger( BOOL bON );
static void main_cbUS2OnTrigger( BOOL bON );
static void main_cbUS3OnTrigger( BOOL bON );
static void main_cbUS4OnTrigger( BOOL bON );
static void main_cbUS5OnTrigger( BOOL bON );
static void main_cbUS6OnTrigger( BOOL bON );
static void main_cbUS7OnTrigger( BOOL bON );
static void main_cbUS8OnTrigger( BOOL bON );

static void main_cbUS1OnReady( void );
static void main_cbUS2OnReady( void );
static void main_cbUS3OnReady( void );
static void main_cbUS4OnReady( void );
static void main_cbUS5OnReady( void );
static void main_cbUS6OnReady( void );
static void main_cbUS7OnReady( void );
static void main_cbUS8OnReady( void );


/*****************************************************************************
 Implementation 
******************************************************************************/
int main( void )
{
	int res;
	uint32_t tmp;

    BSPInit();
	
	TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz", SystemCoreClock );

	/* Generate interrupt each 1 ms as system tick */
	SysTick_Config( SystemCoreClock/1000 );

	TimerInit( &g_Timer9Handle, 9, TIMER9_TICK_HZ );

	main_USoundInit();

	main_SpimInit();

	main_LcdInit(); /* LCD initialization */

    TimerStart( &g_Timer9Handle );

    IRQInit();

	USonicTrigger( &g_USHandles[1] );

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
		}

		if( FALSE != g_UsonicState.b.bUS1 )
		{
			g_UsonicState.b.bUS1 = FALSE;
			g_aUsonicDist[0] = USonicRead( &g_USHandles[0] );

            USonicTrigger( &g_USHandles[1] );
		}

		if( FALSE != g_UsonicState.b.bUS2 )
		{
			g_UsonicState.b.bUS2 = FALSE;
			g_aUsonicDist[1] = USonicRead( &g_USHandles[1] );

            USonicTrigger( &g_USHandles[2] );
		}

		if( FALSE != g_UsonicState.b.bUS3 )
		{
			g_UsonicState.b.bUS3 = FALSE;
			g_aUsonicDist[2] = USonicRead( &g_USHandles[2] );

            USonicTrigger( &g_USHandles[3] );
		}

		if( FALSE != g_UsonicState.b.bUS4 )
		{
			g_UsonicState.b.bUS4 = FALSE;
			g_aUsonicDist[3] = USonicRead( &g_USHandles[3] );

            USonicTrigger( &g_USHandles[4] );
		}

		if( FALSE != g_UsonicState.b.bUS5 )
		{
			g_UsonicState.b.bUS5 = FALSE;
			g_aUsonicDist[4] = USonicRead( &g_USHandles[4] );

            USonicTrigger( &g_USHandles[5] );
		}

		if( FALSE != g_UsonicState.b.bUS6 )
		{
			g_UsonicState.b.bUS6 = FALSE;
			g_aUsonicDist[5] = USonicRead( &g_USHandles[5] );

            USonicTrigger( &g_USHandles[6] );
		}

		if( FALSE != g_UsonicState.b.bUS7 )
		{
			g_UsonicState.b.bUS7 = FALSE;
			g_aUsonicDist[6] = USonicRead( &g_USHandles[6] );

            USonicTrigger( &g_USHandles[7] );
		}

		if( FALSE != g_UsonicState.b.bUS8 )
		{
			g_UsonicState.b.bUS8 = FALSE;
			g_aUsonicDist[7] = USonicRead( &g_USHandles[7] );

            USonicTrigger( &g_USHandles[0] );
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
        sprintf(
			g_aLcdString,
			"US1:%d\r\nUS2:%d\r\nUS3:%d\r\nUS4:%d\r\nUS5:%d\r\nUS6:%d\r\nUS7:%d\r\nUS8:%d\r\n",
			g_aUsonicDist[0],
            g_aUsonicDist[1],
            g_aUsonicDist[2],
            g_aUsonicDist[3],
            g_aUsonicDist[4],
            g_aUsonicDist[5],
            g_aUsonicDist[6],
            g_aUsonicDist[7] );
	}
	
	/* Set background to blue.Refer to gui.h for color code */
	GUI_Clear( ClrBlue ); 

	GUI_SetFont( &g_sFontCalibri10 );
	GUI_PrintString( g_aLcdString, ClrWhite, 10, 10 );
}


static void main_cbLcdTransferDone( void )
{
	g_bLcdFree = TRUE;
}


static void main_cbGuiFrameEnd( void )
{
	g_bLcdFree = TRUE;
}


static void main_cbUS1OnTrigger( BOOL bON )
{
    US1_TRIG_SET( bON );
}


static void main_cbUS2OnTrigger( BOOL bON )
{
    US2_TRIG_SET( bON );
}


static void main_cbUS3OnTrigger( BOOL bON )
{
    US3_TRIG_SET( bON );
}


static void main_cbUS4OnTrigger( BOOL bON )
{
    US4_TRIG_SET( bON );
}


static void main_cbUS5OnTrigger( BOOL bON )
{
    US5_TRIG_SET( bON );
}


static void main_cbUS6OnTrigger( BOOL bON )
{
    US6_TRIG_SET( bON );
}


static void main_cbUS7OnTrigger( BOOL bON )
{
    US7_TRIG_SET( bON );
}


static void main_cbUS8OnTrigger( BOOL bON )
{
    US8_TRIG_SET( bON );
}

static void main_cbUS1OnReady( void )
{
	g_UsonicState.b.bUS1 = TRUE;
}


static void main_cbUS2OnReady( void )
{
	g_UsonicState.b.bUS2 = TRUE;
}


static void main_cbUS3OnReady( void )
{
	g_UsonicState.b.bUS3 = TRUE;
}


static void main_cbUS4OnReady( void )
{
	g_UsonicState.b.bUS4 = TRUE;
}


static void main_cbUS5OnReady( void )
{
	g_UsonicState.b.bUS5 = TRUE;
}


static void main_cbUS6OnReady( void )
{
	g_UsonicState.b.bUS6 = TRUE;
}


static void main_cbUS7OnReady( void )
{
	g_UsonicState.b.bUS7 = TRUE;
}


static void main_cbUS8OnReady( void )
{
	g_UsonicState.b.bUS8 = TRUE;
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
    
    /* Set font */
    GUI_SetFont( &g_sFontCalibri24 );
	
	LCD_AddCallback( main_cbLcdTransferDone );
	
	GUI_AddCbFrameEnd( main_cbGuiFrameEnd );
	
	/* Backlight ON */
	LCD_BL_ON();
}


static void main_USoundInit( void )
{
	/* Ultrasonic initialization. share same timer as remote controller */
	USonicInit( &g_Timer9Handle, TIMER9_TICK_HZ );
	
	/* Add a callback to get notify when ultrasonic sensor is ready to read */
	UsonicAddDevice( &g_USHandles[0], 0U, main_cbUS1OnTrigger, main_cbUS1OnReady );
	UsonicAddDevice( &g_USHandles[1], 1U, main_cbUS2OnTrigger, main_cbUS2OnReady );
	UsonicAddDevice( &g_USHandles[2], 2U, main_cbUS3OnTrigger, main_cbUS3OnReady );
	UsonicAddDevice( &g_USHandles[3], 3U, main_cbUS4OnTrigger, main_cbUS4OnReady );
	UsonicAddDevice( &g_USHandles[4], 4U, main_cbUS5OnTrigger, main_cbUS5OnReady );
	UsonicAddDevice( &g_USHandles[5], 5U, main_cbUS6OnTrigger, main_cbUS6OnReady );
	UsonicAddDevice( &g_USHandles[6], 6U, main_cbUS7OnTrigger, main_cbUS7OnReady );
	UsonicAddDevice( &g_USHandles[7], 7U, main_cbUS8OnTrigger, main_cbUS8OnReady );	
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
}


void EXTI8_US1_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[0], IN_US1_ECHO() );
}

void EXTI9_US2_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[1], IN_US2_ECHO() );
}


void EXTI10_US3_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[2], IN_US3_ECHO() );
}


void EXTI11_US4_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[3], IN_US4_ECHO() );
}


void EXTI12_US5_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[4], IN_US5_ECHO() );
}


void EXTI13_US6_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[5], IN_US6_ECHO() );
}


void EXTI14_US7_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[6], IN_US7_ECHO() );
}


void EXTI15_US8_ECHO_IRQHandler( uint32_t Status )
{
	UsonicISR( &g_USHandles[7], IN_US8_ECHO() );
}
