/*****************************************************************************
 @Project	: 
 @File 		: Hal.c
 @Details  	: All Ports and peripherals configuration                    
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


/*****************************************************************************
 Define
******************************************************************************/


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
 Implementation
******************************************************************************/
void PortInit( void )
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN 
					| RCC_APB2ENR_IOPBEN
					| RCC_APB2ENR_TIM1EN
					| RCC_APB2ENR_IOPCEN
					| RCC_APB2ENR_IOPDEN
					| RCC_APB2ENR_AFIOEN;



    /*******************************
	 SPI1 for UWB
	********************************/	
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	/* Reset */
	GPIOB->CRL |= GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1; 
	GPIOB->CRL &= ~GPIO_CRL_CNF5;
	
	/* D/C */
	GPIOC->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1; 
	GPIOC->CRH &= ~GPIO_CRH_CNF9;
	
	GPIOA->CRL |= GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1; 
	GPIOA->CRL &= ~GPIO_CRL_CNF4;
//	GPIOA->CRL |= GPIO_CRL_CNF4_1;
	
	GPIOA->CRL |= GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1; 
	GPIOA->CRL &= ~GPIO_CRL_CNF5_0;
	GPIOA->CRL |= GPIO_CRL_CNF5_1;
	
	GPIOA->CRL |= GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1; 
	GPIOA->CRL &= ~GPIO_CRL_CNF6_0;
	GPIOA->CRL |= GPIO_CRL_CNF6_1;
	
	GPIOA->CRL |= GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1; 
	GPIOA->CRL &= ~GPIO_CRL_CNF7_0;
	GPIOA->CRL |= GPIO_CRL_CNF7_1;

    /* PB9 UWB IRQ */ 
	GPIOB->CRH &= ~GPIO_CRH_MODE9;
	GPIOB->CRH &= ~GPIO_CRH_CNF9;
	GPIOB->CRH |= GPIO_CRH_CNF9_1;
	
	AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI9;
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI9_PB;
	
	EXTI->EMR |= EXTI_EMR_MR9;
	EXTI->IMR |= EXTI_EMR_MR9;
	EXTI->RTSR |= EXTI_FTSR_TR9;
    EXTI->FTSR &= ~EXTI_FTSR_TR9;
}


























