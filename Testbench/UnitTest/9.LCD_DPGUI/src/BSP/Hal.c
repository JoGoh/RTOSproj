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
                    | RCC_APB1ENR_I2C2EN;

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
	 USART2 BT Port
	********************************/
	GPIOD->MODER &= ~GPIO_MODER_MODER5;						/* PD_USART2_TX_DBG */
	GPIOD->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER5_Pos);
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR5_Msk;
	GPIOD->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR5_Pos);
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
	GPIOD->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR5_Pos);
	GPIOD->AFR[0] &= ~GPIO_AFRL_AFRL5;
	GPIOD->AFR[0] |= (GPIO_USART2_AF7<<GPIO_AFRL_AFRL5_Pos);

	GPIOD->MODER &= ~GPIO_MODER_MODER6;						/* PD_USART2_RX_DBG */
	GPIOD->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER6_Pos);
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR6_Msk;
	GPIOD->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR6_Pos);
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
	GPIOD->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR6_Pos);
	GPIOD->AFR[0] &= ~GPIO_AFRL_AFRL6;
	GPIOD->AFR[0] |= (GPIO_USART2_AF7<<GPIO_AFRL_AFRL6_Pos);


	/*******************************
	 IMU sensors I2C2
	********************************/
	GPIOB->MODER &= ~GPIO_MODER_MODER10;										/* PB10 I2C2 SCL */
	GPIOB->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER10_Pos);
	GPIOB->OTYPER |= GPIO_OTYPER_OT_10;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR10;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR10;
	GPIOB->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR10_Pos);
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR10_Pos);
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH2;
	GPIOB->AFR[1] |= (GPIO_I2C2_AF4<<GPIO_AFRH_AFRH2_Pos);
	
	GPIOB->MODER &= ~GPIO_MODER_MODER11;										/* PB11 I2C2 SDA */	
	GPIOB->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER11_Pos);
	GPIOB->OTYPER |= GPIO_OTYPER_OT_11;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR11;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR11;
	GPIOB->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR11_Pos);
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR11_Pos);
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH3;
	GPIOB->AFR[1] |= (GPIO_I2C2_AF4<<GPIO_AFRH_AFRH3_Pos);


	/*******************************
	 LCD SPI2
	********************************/
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

	GPIOE->MODER &= ~GPIO_MODER_MODER6;									/* PE_LCD_RESET */
	GPIOE->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER6_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR6;
	GPIOE->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR6_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR6_Pos);
	GPIOE->BSRR = GPIO_BSRR_BS_6;

	GPIOE->MODER &= ~GPIO_MODER_MODER8;									/* PE_LCD_DC */
	GPIOE->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER8_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR8;
	GPIOE->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR8_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR8;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR8_Pos);
	GPIOE->BSRR = GPIO_BSRR_BS_8;

	GPIOE->MODER &= ~GPIO_MODER_MODER0;									/* PE_LCD_BL */
	GPIOE->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER0_Pos);
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR0;
	GPIOE->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR0_Pos);
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0;
	GPIOE->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR0_Pos);
	GPIOE->BSRR = GPIO_BSRR_BS_0;

	GPIOB->MODER &= ~GPIO_MODER_MODER13;								/* PB_LCD_SPI2_CS */
	GPIOB->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER13_Pos);
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR13;
	GPIOB->PUPDR |= (GPIO_PULL_UP<<GPIO_PUPDR_PUPDR13_Pos);
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR13_Pos);
	GPIOB->BSRR = GPIO_BSRR_BS_13;

	GPIOD->MODER &= ~GPIO_MODER_MODER3;									/* PD_LCD_SPI2_CLK */
	GPIOD->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER3_Pos);
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR3;
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;
	GPIOD->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR3_Pos);
	GPIOD->AFR[0] &= ~GPIO_AFRL_AFRL3;
	GPIOD->AFR[0] |= (GPIO_SPI2_AF5<<GPIO_AFRL_AFRL3_Pos);
	
	GPIOB->MODER &= ~GPIO_MODER_MODER14;									/* PB_LCD_SPI2_MISO */
	GPIOB->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER14_Pos);
	//GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR14;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR14;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR14_Pos);
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH6;
	GPIOB->AFR[1] |= (GPIO_SPI2_AF5<<GPIO_AFRH_AFRH6_Pos);	
	
	GPIOB->MODER &= ~GPIO_MODER_MODER15;									/* PB_LCD_SPI2_MOSI */	
	GPIOB->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER15_Pos);
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR15;
	//GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR15;
	GPIOB->OSPEEDR |= (GPIO_SPEED_MAX<<GPIO_OSPEEDER_OSPEEDR15_Pos);
	GPIOB->AFR[1] &= ~GPIO_AFRH_AFRH7;
	GPIOB->AFR[1] |= (GPIO_SPI2_AF5<<GPIO_AFRH_AFRH7_Pos);	
}


























