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
	/* peripherals bus clocks enable */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN 
					| RCC_AHB1ENR_GPIOBEN 
					| RCC_AHB1ENR_GPIOCEN
					| RCC_AHB1ENR_GPIODEN
					| RCC_AHB1ENR_GPIOEEN
					| RCC_AHB1ENR_GPIOFEN
					| RCC_AHB1ENR_GPIOGEN
					| RCC_AHB1ENR_GPIOHEN
					| RCC_AHB1ENR_GPIOIEN;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN
					| RCC_APB1ENR_TIM3EN
					| RCC_APB1ENR_TIM4EN
					| RCC_APB1ENR_TIM5EN
					| RCC_APB1ENR_TIM6EN
					| RCC_APB1ENR_TIM7EN
                    | RCC_APB1ENR_TIM12EN
					| RCC_APB1ENR_TIM13EN
                    | RCC_APB1ENR_TIM14EN;

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN
					| RCC_APB2ENR_TIM1EN
                    | RCC_APB2ENR_TIM8EN
					| RCC_APB2ENR_TIM9EN
					| RCC_APB2ENR_TIM10EN
					| RCC_APB2ENR_TIM11EN;


	/*******************************
	 LED control pins
	********************************/
	GPIOB->MODER &= ~GPIO_MODER_MODER7;									/* PB_LED_BLUE */
	GPIOB->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER7_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7_Msk;
	GPIOB->PUPDR |= (GPIO_PULL_DIS<<GPIO_PUPDR_PUPDR7_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR7;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR7_Pos);
	GPIOB->BSRR = GPIO_BSRR_BR_7;
	
	GPIOB->MODER &= ~GPIO_MODER_MODER14;								/* PB_LED_RED */
	GPIOB->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER14_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR14_Msk;
	GPIOB->PUPDR |= (GPIO_PULL_DIS<<GPIO_PUPDR_PUPDR14_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR14;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR14_Pos);
	GPIOB->BSRR = GPIO_BSRR_BR_14;

	/*******************************
	 Buzzer - TIM10- CH1
	********************************/
	GPIOF->MODER &= ~GPIO_MODER_MODER6;									/* PF6 Buzzer */
	GPIOF->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER6_Pos);
	GPIOF->PUPDR &= ~GPIO_PUPDR_PUPDR6_Msk;
	GPIOF->PUPDR |= (GPIO_PULL_DIS<<GPIO_PUPDR_PUPDR6_Pos);
	GPIOF->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
	GPIOF->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR6_Pos);
	GPIOF->AFR[0] &= ~GPIO_AFRL_AFRL6;
	GPIOF->AFR[0] |= (GPIO_PWM_AF3<<GPIO_AFRH_AFRH6_Pos);

}


























