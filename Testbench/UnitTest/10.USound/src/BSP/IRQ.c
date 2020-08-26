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


/*****************************************************************************
 Define
******************************************************************************/


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/
extern void EXTI8_US1_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI9_US2_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI10_US3_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI11_US4_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI12_US5_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI13_US6_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI14_US7_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI15_US8_ECHO_IRQHandler( uint32_t Status ) __attribute__((weak));


/*****************************************************************************
 Local Variables
******************************************************************************/
void IRQInit( void )
{
	NVIC_EnableIRQ( EXTI9_5_IRQn );
	NVIC_EnableIRQ( EXTI15_10_IRQn );
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
	UNUSE( irqStatus );

	if( 0 != (irqStatus & EXTI_PR_PR8) )
	{
		EXTI->PR = EXTI_PR_PR8;
		EXTI8_US1_ECHO_IRQHandler( irqStatus );
	}

 	if( 0 != (irqStatus & EXTI_PR_PR9) )
	{
		EXTI->PR = EXTI_PR_PR9;
		EXTI9_US2_ECHO_IRQHandler( irqStatus );
	}   
}


void EXTI15_10_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );

 	if( 0 != (irqStatus & EXTI_PR_PR10) )
	{
		EXTI->PR = EXTI_PR_PR10;
		EXTI10_US3_ECHO_IRQHandler( irqStatus );
	}   

	if( 0 != (irqStatus & EXTI_PR_PR11) )
	{
		EXTI->PR = EXTI_PR_PR11;
		EXTI11_US4_ECHO_IRQHandler( irqStatus );
	}

	if( 0 != (irqStatus & EXTI_PR_PR12) )
	{
		EXTI->PR = EXTI_PR_PR12;
		EXTI12_US5_ECHO_IRQHandler( irqStatus );
	}

 	if( 0 != (irqStatus & EXTI_PR_PR13) )
	{
		EXTI->PR = EXTI_PR_PR13;
		EXTI13_US6_ECHO_IRQHandler( irqStatus );
	}

  	if( 0 != (irqStatus & EXTI_PR_PR14) )
	{
		EXTI->PR = EXTI_PR_PR14;
		EXTI14_US7_ECHO_IRQHandler( irqStatus );
	}

  	if( 0 != (irqStatus & EXTI_PR_PR15) )
	{
		EXTI->PR = EXTI_PR_PR15;
		EXTI15_US8_ECHO_IRQHandler( irqStatus );
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






















