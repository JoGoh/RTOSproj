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
#include "Pwm.h"


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS				500


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Const Local Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int 		g_nSysTick 			= SYS_TICK_MS;
static volatile BOOL 		g_bLEDToggle		= FALSE;

static PWM_HANDLE			g_PwmHandle;


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Implementation 
******************************************************************************/
/* NOTE:
 Connect your buzzer input pin to PF6 */
int main( void )
{
    BSPInit();
	
	TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz", SystemCoreClock );

	/* Generate interrupt each 1 ms as system tick */
	SysTick_Config( SystemCoreClock/1000 );

	/* PWM for Buzzer Initialization */
	PWMInit( &g_PwmHandle, 10U, 3200U ); /* 2.5KHz to 3.8KHz */

	/* Buzzer is Active LOW */
	PWMEnable( &g_PwmHandle, 1, 50.0, TRUE );

	/* Runtime for loop */
    for(;;)
    {
		/* TODO: */
	}
}


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void SysTick_Handler( void )
{
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
}

