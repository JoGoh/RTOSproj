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


/*****************************************************************************
 Local Variables
******************************************************************************/


/*****************************************************************************
 Local Functions
******************************************************************************/


/*****************************************************************************
 Implementation
******************************************************************************/
void BSPInit( void )
{
	/* Use External Crystal = 8Mhz */
	Clock8MInternalInit();

	/* Update SystemCoreClock */
	SystemCoreClockUpdate();

	/* Hardware abstraction layer initialization */
	PortInit();

    NVIC_SetPriorityGrouping( NVIC_PriorityGroup_4 );
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






















