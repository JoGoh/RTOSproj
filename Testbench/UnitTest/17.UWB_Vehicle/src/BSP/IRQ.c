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
 
extern void EXTI7_UWB_INT_IRQHandler( uint32_t Status );

//extern void EXTI5_OPTICAL_IRQHandler( uint32_t Status ) __attribute__((weak));
//extern void EXTI3_IMU_DATA_RDY_IRQHandler( uint32_t Status ) __attribute__((weak));

/*****************************************************************************
 Local Variables
******************************************************************************/
void IRQInit( void )
{
	NVIC_EnableIRQ( EXTI0_IRQn );
        NVIC_EnableIRQ( EXTI2_IRQn );
        NVIC_EnableIRQ( EXTI3_IRQn );
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
//	if( 0 != (irqStatus & EXTI_PR_PR3) )
//	{
//		EXTI->PR = EXTI_PR_PR3;
//		EXTI3_IMU_DATA_RDY_IRQHandler( irqStatus );
//	}
//if( 0 != (irqStatus & EXTI_PR_PR3) )
//	{
//
//        EXTI->PR = EXTI_PR_PR3;
//        EXTI3_UWB_INT_IRQHandler( irqStatus );
//	}
}


void EXTI4_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
	UNUSE( irqStatus );
}


void EXTI9_5_IRQHandler( void )
{
	uint32_t irqStatus = EXTI->PR;
//     if( 0 != (irqStatus & EXTI_PR_PR5) )
//	{
//		EXTI->PR = EXTI_PR_PR5;
//		EXTI5_OPTICAL_IRQHandler( irqStatus );
//	}
    if( 0 != (irqStatus & EXTI_PR_PR7) )
    {
        EXTI->PR = EXTI_PR_PR7;
        EXTI7_UWB_INT_IRQHandler( irqStatus );
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






















