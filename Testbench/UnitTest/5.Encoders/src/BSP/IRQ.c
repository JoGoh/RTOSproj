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

/* Weak pulled functions. It only will be called if user define the functions */
extern void EXTI9_M1_ENC_IN1_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI4_M2_ENC_IN1_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI0_M3_ENC_IN1_IRQHandler( uint32_t Status ) __attribute__((weak));
extern void EXTI12_M4_ENC_IN1_IRQHandler( uint32_t Status ) __attribute__((weak));


/*****************************************************************************
 Local Variables
******************************************************************************/
void IRQInit( void )
{
	NVIC_EnableIRQ( EXTI0_IRQn );
	NVIC_EnableIRQ( EXTI4_IRQn );
	NVIC_EnableIRQ( EXTI9_5_IRQn );
	NVIC_EnableIRQ( EXTI15_10_IRQn );
}


/*****************************************************************************
 Implementation
******************************************************************************/
void EXTI0_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	
	if( 0 != (irqStatus & EXTI_PR_PR0) )
	{
		EXTI->PR = EXTI_PR_PR0;
        EXTI0_M3_ENC_IN1_IRQHandler( irqStatus );
	}
}


void EXTI1_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}


void EXTI2_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	
	if( 0 != (irqStatus & EXTI_PR_PR2) )
	{
		EXTI->PR = EXTI_PR_PR2;
	}
}


void EXTI3_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;

	if( 0 != (irqStatus & EXTI_PR_PR3) )
	{
		EXTI->PR = EXTI_PR_PR3;
	}
}


void EXTI4_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	
	if( 0 != (irqStatus & EXTI_PR_PR4) )
	{
		EXTI->PR = EXTI_PR_PR4;
		EXTI4_M2_ENC_IN1_IRQHandler( irqStatus );
	}
}


void EXTI9_5_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	if( 0 != (irqStatus & EXTI_PR_PR9) )
	{
		EXTI->PR = EXTI_PR_PR9;
		EXTI9_M1_ENC_IN1_IRQHandler( irqStatus );
	}
}


void EXTI15_10_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	
	if( 0 != (irqStatus & EXTI_PR_PR12) )
	{
		EXTI->PR = EXTI_PR_PR12;
        EXTI12_M4_ENC_IN1_IRQHandler( irqStatus );
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






















