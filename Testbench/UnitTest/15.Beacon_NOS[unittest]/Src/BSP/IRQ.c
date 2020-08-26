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
#include "BSP.h"
#include "IRQ.h"


/*****************************************************************************
 Define
******************************************************************************/


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
 extern void EXTI9_UWB_INT_IRQHandler( uint32_t Status );


/*****************************************************************************
 Local Variables
******************************************************************************/
void IRQInit( void )
{
	NVIC_SetPriority( EXTI9_5_IRQn, 0x0a );
    NVIC_EnableIRQ( EXTI9_5_IRQn );
}


/*****************************************************************************
 Implementation
******************************************************************************/
void EXTI0_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}


void EXTI1_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
    UNUSE( irqStatus );
}


void EXTI2_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
    UNUSE( irqStatus );
}


void EXTI3_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}


void EXTI4_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}


void EXTI9_5_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;

    if( 0 != (irqStatus&EXTI_PR_PR9) )
    {
        EXTI->PR = EXTI_PR_PR9;
        EXTI9_UWB_INT_IRQHandler( irqStatus );
    }
}


void EXTI15_10_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
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






















