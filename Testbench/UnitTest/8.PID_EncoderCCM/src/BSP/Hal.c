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
					| RCC_AHB1ENR_GPIOIEN
                                        | RCC_AHB1ENR_DMA1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN
					| RCC_APB1ENR_TIM3EN
					| RCC_APB1ENR_TIM4EN
					| RCC_APB1ENR_TIM5EN
					| RCC_APB1ENR_TIM6EN
					| RCC_APB1ENR_TIM7EN
                    | RCC_APB1ENR_TIM12EN
					| RCC_APB1ENR_TIM13EN
                    | RCC_APB1ENR_TIM14EN
                                        | RCC_APB1ENR_USART2EN
                                        | RCC_APB1ENR_I2C1EN;

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
	 Motors control pins
	********************************/
	GPIOE->MODER &= ~GPIO_MODER_MODER2;									/* PE_M1_CTRL_IN1 */
	GPIOE->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER2_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR2_Msk;
	GPIOE->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR2_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR2;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR2_Pos);
	GPIOE->BSRR = GPIO_BSRR_BR_2;
	
	GPIOE->MODER &= ~GPIO_MODER_MODER3;									/* PE_M2_CTRL_IN1 */
	GPIOE->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER3_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR3_Msk;
	GPIOE->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR3_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR3_Pos);
	GPIOE->BSRR = GPIO_BSRR_BR_3;
	
	GPIOE->MODER &= ~GPIO_MODER_MODER4;									/* PE_M3_CTRL_IN1 */
	GPIOE->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER4_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR4_Msk;
	GPIOE->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR4_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR4;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR4_Pos);
	GPIOE->BSRR = GPIO_BSRR_BR_4;

	GPIOE->MODER &= ~GPIO_MODER_MODER5;									/* PE_M4_CTRL_IN1 */
	GPIOE->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER5_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR5_Msk;
	GPIOE->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR5_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR5_Pos);
	GPIOE->BSRR = GPIO_BSRR_BR_5;
	
	GPIOC->MODER &= ~GPIO_MODER_MODER6;									/* PC_M1_PWM_CH1 */
	GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER6_Pos);
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR6_Msk;
	GPIOC->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR6_Pos);
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR8;
	GPIOC->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR6_Pos);
	GPIOC->AFR[0] &= ~GPIO_AFRL_AFRL6;
	GPIOC->AFR[0] |= (GPIO_PWM_AF3<<GPIO_AFRH_AFRH6_Pos);
	
	GPIOC->MODER &= ~GPIO_MODER_MODER7;									/* PC_M2_PWM_CH2 */
	GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER7_Pos);
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR7_Msk;
	GPIOC->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR7_Pos);
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR7;
	GPIOC->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR7_Pos);
	GPIOC->AFR[0] &= ~GPIO_AFRL_AFRL7;
	GPIOC->AFR[0] |= (GPIO_PWM_AF3<<GPIO_AFRL_AFRL7_Pos);
	
	GPIOC->MODER &= ~GPIO_MODER_MODER8;									/* PC_M3_PWM_CH3 */
	GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER8_Pos);
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR8_Msk;
	GPIOC->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR8_Pos);
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR8;
	GPIOC->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR8_Pos);
	GPIOC->AFR[1] &= ~GPIO_AFRH_AFRH0;
	GPIOC->AFR[1] |= (GPIO_PWM_AF3<<GPIO_AFRH_AFRH0_Pos);
	
	GPIOC->MODER &= ~GPIO_MODER_MODER9;									/* PC_M4_PWM_CH4 */
	GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER9_Pos);
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR9_Msk;
	GPIOC->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR9_Pos);
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR9;
	GPIOC->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR9_Pos);
	GPIOC->AFR[1] &= ~GPIO_AFRH_AFRH1;
	GPIOC->AFR[1] |= (GPIO_PWM_AF3<<GPIO_AFRH_AFRH1_Pos);



#if 0
	/*******************************
	 Motors Encoder pins
	********************************/
	GPIOG->MODER &= ~GPIO_MODER_MODER0;									/* PG0 M1 Encoder IN1 */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER0_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR0_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR0_Pos);
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0;
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR0_Pos);
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0_Msk;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PG;
	EXTI->EMR |= EXTI_EMR_MR0;
	EXTI->IMR |= EXTI_EMR_MR0;
	EXTI->RTSR |= EXTI_FTSR_TR0;
    EXTI->FTSR &= ~EXTI_FTSR_TR0;
	
	GPIOG->MODER &= ~GPIO_MODER_MODER1;									/* PG1 M1 Encoder IN2 */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER1_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR1_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR1_Pos);
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR1_Pos);
	
	GPIOG->MODER &= ~GPIO_MODER_MODER2;									/* PG2 M2 Encoder IN1 */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER2_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR2_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR2_Pos);
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR2;
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR2_Pos);
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2_Msk;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PG;
	EXTI->EMR |= EXTI_EMR_MR2;
	EXTI->IMR |= EXTI_EMR_MR2;
	EXTI->RTSR |= EXTI_FTSR_TR2;
    EXTI->FTSR &= ~EXTI_FTSR_TR2;
	
	GPIOG->MODER &= ~GPIO_MODER_MODER3;									/* PG3 M2 Encoder IN2 */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER3_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR3_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR3_Pos);
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR3_Pos);
	
	GPIOG->MODER &= ~GPIO_MODER_MODER4;									/* PG4 M3 Encoder IN1 */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER4_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR4_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR4_Pos);
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR4;
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR4_Pos);
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI4_Msk;
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PG;
	EXTI->EMR |= EXTI_EMR_MR4;
	EXTI->IMR |= EXTI_EMR_MR4;
	EXTI->RTSR |= EXTI_FTSR_TR4;
    EXTI->FTSR &= ~EXTI_FTSR_TR4;
	
	GPIOG->MODER &= ~GPIO_MODER_MODER5;									/* PG5 M3 Encoder IN2 */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER5_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR5_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR5_Pos);
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR5_Pos);
	
	GPIOG->MODER &= ~GPIO_MODER_MODER6;									/* PG6 M4 Encoder IN1 with Interrupt */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER6_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR6_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR6_Pos);
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR6_Pos);	
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI6_Msk;
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI6_PG;
	EXTI->EMR |= EXTI_EMR_MR6;
	EXTI->IMR |= EXTI_EMR_MR6;
	EXTI->RTSR |= EXTI_FTSR_TR6;
    EXTI->FTSR &= ~EXTI_FTSR_TR6;
	
	GPIOG->MODER &= ~GPIO_MODER_MODER7;									/* PG7 M4 Encoder IN2 */
	GPIOG->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER7_Pos);
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPDR7_Msk;
	GPIOG->PUPDR |= (GPIO_PULL_DWN<<GPIO_PUPDR_PUPDR7_Pos);
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR7;
	GPIOG->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR7_Pos);
#endif

	/*******************************
	 Encoders input pins
	********************************/

	/* QEncoder 1 - TIM1 */
	GPIOE->MODER &= ~GPIO_MODER_MODER9;
	GPIOE->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER9_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR9_Msk;
	GPIOE->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR9_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR9;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR9_Pos);
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFRH1;
	GPIOE->AFR[1] |= (GPIO_TIM1_AF1<<GPIO_AFRH_AFRH1_Pos);

	GPIOE->MODER &= ~GPIO_MODER_MODER11;
	GPIOE->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER11_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR11_Msk;
	GPIOE->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR11_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR11;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR11_Pos);
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFRH3;
	GPIOE->AFR[1] |= (GPIO_TIM1_AF1<<GPIO_AFRH_AFRH3_Pos);

	/* QEncoder 2 - TIM3 */
	GPIOB->MODER &= ~GPIO_MODER_MODER4;
	GPIOB->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER4_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4_Msk;
	GPIOB->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR4_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR4;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR4_Pos);
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL4;
	GPIOB->AFR[0] |= (GPIO_TIM4_AF2<<GPIO_AFRL_AFRL4_Pos);

	GPIOB->MODER &= ~GPIO_MODER_MODER5;
	GPIOB->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER5_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR5_Msk;
	GPIOB->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR5_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR5_Pos);
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL5;
	GPIOB->AFR[0] |= (GPIO_TIM4_AF2<<GPIO_AFRL_AFRL5_Pos);

	/* QEncoder 3 - TIM2 */
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
	GPIOA->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER0_Pos);
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0_Msk;
	GPIOA->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR0_Pos);
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0;
	GPIOA->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR0_Pos);
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL0;
	GPIOA->AFR[0] |= (GPIO_TIM2_AF1<<GPIO_AFRL_AFRL0_Pos);

	GPIOA->MODER &= ~GPIO_MODER_MODER1;
	GPIOA->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER1_Pos);
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR1_Msk;
	GPIOA->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR1_Pos);
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR1;
	GPIOA->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR1_Pos);
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL1;
	GPIOA->AFR[0] |= (GPIO_TIM2_AF1<<GPIO_AFRL_AFRL1_Pos);

	/* QEncoder 4 */
	GPIOD->MODER &= ~GPIO_MODER_MODER12;
	GPIOD->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER12_Pos);
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR12_Msk;
	GPIOD->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR12_Pos);
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR12;
	GPIOD->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR12_Pos);
	GPIOD->AFR[1] &= ~GPIO_AFRH_AFRH4;
	GPIOD->AFR[1] |= (GPIO_PWM_AF2<<GPIO_AFRH_AFRH4_Pos);

	GPIOD->MODER &= ~GPIO_MODER_MODER13;
	GPIOD->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER13_Pos);
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR13_Msk;
	GPIOD->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR13_Pos);
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13;
	GPIOD->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR13_Pos);
	GPIOD->AFR[1] &= ~GPIO_AFRH_AFRH5;
	GPIOD->AFR[1] |= (GPIO_PWM_AF2<<GPIO_AFRH_AFRH5_Pos);

}


























