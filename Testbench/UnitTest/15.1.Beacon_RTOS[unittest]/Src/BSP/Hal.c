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
	//RCC->APB1ENR |= RCC_APB1ENR_USBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN 
					| RCC_APB2ENR_IOPBEN
					| RCC_APB2ENR_TIM1EN
					| RCC_APB2ENR_IOPCEN
					| RCC_APB2ENR_IOPDEN
					| RCC_APB2ENR_AFIOEN;

	//GPIOB->CRH &= ~GPIO_CRH_CNF11;
	//GPIOB->CRH |= GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1; /* LED PB11 */

#if 0
    /*******************************
	 Wireless USART
	********************************/		
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	GPIOA->CRL |= GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1;		/* PA2 USART2 TX */
	GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
	GPIOA->CRL |= GPIO_CRL_CNF2_1;

	GPIOA->CRL &= ~(GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1);	/* PA3 USART2 RX */
	GPIOA->CRL |= GPIO_CRL_CNF3_0;
	GPIOA->CRL &= ~GPIO_CRL_CNF3_1;

	//AFIO->MAPR |= (2<<AFIO_MAPR_SWJ_CFG_NOJNTRST_Pos);
    GPIOC->CRL &= ~GPIO_CRL_CNF2;
	GPIOC->CRL |= GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1; /* WIFI RESET */

    GPIOC->CRL &= ~GPIO_CRL_CNF1;
	GPIOC->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1; /* WIFI EN */

    GPIOC->CRL &= ~GPIO_CRL_CNF3;
	GPIOC->CRL |= GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1; /* WIFI PROG */
#endif

	/*******************************
	 Bluetooth USART
	********************************/		
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1;			/* PA9 USART1 TX */
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
	GPIOA->CRH |= GPIO_CRH_CNF9_1;

	GPIOA->CRH &= ~(GPIO_CRH_MODE10_0 | GPIO_CRH_MODE10_1);		/* PA10 USART1 RX */
	GPIOA->CRH |= GPIO_CRH_CNF10_0;
	GPIOA->CRH &= ~GPIO_CRH_CNF10_1;


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


























