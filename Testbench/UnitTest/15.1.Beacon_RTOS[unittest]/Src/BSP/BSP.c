/*****************************************************************************
 @Project	: 
 @File 		: BSP.c
 @Details  	:
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "Clock.h"
#include "BSP.h"
#include "Serial.h"


/*****************************************************************************
 Define
******************************************************************************/
#define NVIC_PriorityGroup_0         ((uint32_t)0x700) /* 0 bits for pre-emption priority
                                                     4 bits for subpriority */
#define NVIC_PriorityGroup_1         ((uint32_t)0x600) /* 1 bits for pre-emption priority
                                                     3 bits for subpriority */
#define NVIC_PriorityGroup_2         ((uint32_t)0x500) /* 2 bits for pre-emption priority
                                                     2 bits for subpriority */
#define NVIC_PriorityGroup_3         ((uint32_t)0x400) /* 3 bits for pre-emption priority
                                                     1 bits for subpriority */
#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /* 4 bits for pre-emption priority
                                                     0 bits for subpriority */

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
extern UART_DRIVER const STM32F103X_UART_DRV;
UART_HANDLE		g_DebugSerialHandle;

static char 	g_aUsart1TxBuf[256];
static char 	g_aUsart1RxBuf[32];


/*****************************************************************************
 Local Variables
******************************************************************************/


/*****************************************************************************
 Local Functions
******************************************************************************/
static void bsp_UartInit( void );


/*****************************************************************************
 Implementation
******************************************************************************/
void BSPInit( void )
{
	/* Use Internal Crystal = 8Mhz */
	Clock8MInternalInit();

	/* Update SystemCoreClock */
	SystemCoreClockUpdate();

	/* Hardware abstraction layer initialization */
	PortInit();

    NVIC_SetPriorityGrouping( NVIC_PriorityGroup_4 );

    bsp_UartInit();
}


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/
static void bsp_UartInit( void )
{
	int res;

	/* Bluetooth comport */
	SerialInit(
		&g_DebugSerialHandle,
		&STM32F103X_UART_DRV,
		1U,
		460800 );
	
	SerialConfig(
		&g_DebugSerialHandle, 
		UART_BITS_8, 
		UART_NONE,
		UART_ONE );

    SerialBuffer(
        &g_DebugSerialHandle,
		g_aUsart1TxBuf,
		sizeof(g_aUsart1TxBuf),
		g_aUsart1RxBuf,
		sizeof(g_aUsart1RxBuf) );
}



/*****************************************************************************
 Interrupt functions
******************************************************************************/
void HardFault_Handler( void )
{
	/* Hardware errors, wrong configuration on hardware,
	clock failure will stop here */
	TRACE( "Hard fault\n" );
	ASSERT( FALSE );
	
#ifndef _DEBUG
	NVIC_SystemReset();
#endif
}






















