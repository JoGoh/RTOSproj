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
#include "Cube3D.h"


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS				500
#define LCD_BUF_SIZE			4096*3
#define LCD_UPDATE_MS			5


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
static uint8_t				g_nMove				= 0;
static BOOL					g_bFwd				= TRUE;
volatile BOOL				g_bLcdFree			= TRUE;

static DMA_HANDLE			g_Dma1Spi2TxHandle;
static DMA_HANDLE			g_Dma1Spi2RxHandle;

static volatile int			g_nDelayms			= 0;

static char                 g_aLcdstr[128];
static int					g_Screenx = 0;
static int					g_Screeny = 0;

/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void );
static void main_LcdInit( void );


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbGuiFrameEnd( void );
static void main_cbLcdTransferDone( void );


/*****************************************************************************
 Implementation 
******************************************************************************/
int main( void )
{
	int res;

    BSPInit();
	
	TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz", SystemCoreClock );

	/* Generate interrupt each 1 ms as system tick */
	SysTick_Config( SystemCoreClock/1000 );

	main_SpimInit();

	main_LcdInit(); /* LCD initialization */

    CubesInit();

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
		g_nCount++;
        sprintf( g_aLcdstr, "%.2f", g_nCount );  /* Update lcd string */

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

        /* This is demo for 3D cube. Remove it during code integration */
        CubesUpdate();
	}
	
	/* Set background to blue.Refer to gui.h for color code */
	GUI_Clear( ClrBlue ); 

	/* Display string */
	GUI_SetFont( &g_sFontCalibri24 );
	GUI_PrintString( "DP GUI", ClrLawnGreen, 35, 10 );

	GUI_SetFont( &g_sFontCalibri10 );
	GUI_PrintString( g_aLcdstr, ClrWhite, 50, 120 );

    /* Draw a circle */
    GUI_SetColor( ClrYellow );
	GUI_DrawCircle( 60, 50, 10+g_nMove, FALSE );

    GUI_SetColor( ClrRed );
    GUI_DrawRect(
        80,
        50+g_nMove,
        120,
        90+g_nMove );

    GUI_SetColor( ClrGold );

    /* This is demo for 3D cube. Remove it during code integration */
    CubesDrawAll();
}


static void main_cbLcdTransferDone( void )
{
    /* NOTE
    A frame of LCD consist of several blocks. block size is determine 
    by user during GUI_Init() */

    /* This callback inform application that a memory block 
    of pixel has been sent to LCD RAM */
	g_bLcdFree = TRUE;
}


static void main_cbGuiFrameEnd( void )
{
    /* This callback inform application that a frame or a 
    full screen size of pixels has been sent */

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
		25000000,       /* NOTE: LCD normally can run more than 40Mhz SPI 
                        speed but MCU cannot. 25MHz is the limit for MCU */
		SPI_CLK_INACT_LOW,
		SPI_CLK_RISING_EDGE,
		SPI_DATA_SIZE_8 );

    /* Since DMA is enabled and configured, switch to it now */
	SpimLinkDMA(
		&g_SpimLcdHandle,
		&g_Dma1Spi2TxHandle,
		&g_Dma1Spi2RxHandle );	
}


static void main_LcdInit( void )
{
	int res;
	
	/* g_SpimLcdHandle shall be initialized before use */
	
	/* Choosing a landscape orientation */
	LcdInit( &g_SpimLcdHandle, LCD_PORTRAIT );
	
	/* Get physical LCD size in pixels */
	LCD_GetSize( &g_Screenx, &g_Screeny );
	
	/* Initialize GUI */
	GUI_Init(
		&g_MemDev,
		g_Screenx,
		g_Screeny,
		g_aBuf,
		sizeof(g_aBuf) );

    /* Initialize the DMA channels for SPI2. This is fix by hardware in MCU */
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
	
    /* Enable Callback when LCD transfer is done */
	LCD_AddCallback( main_cbLcdTransferDone );
	
	GUI_AddCbFrameEnd( main_cbGuiFrameEnd );
	
	/* Backlite ON if support */
	LCD_BL_ON();
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

