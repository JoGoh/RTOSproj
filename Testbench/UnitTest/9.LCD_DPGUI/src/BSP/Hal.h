/*****************************************************************************
 @Project	: 
 @File 		: 
 @Details  	: All Ports and peripherals configuration                    
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#ifndef __HAL_DOT_H__
#define __HAL_DOT_H__


/*****************************************************************************
 Define
******************************************************************************/
#define GPIO_MODE_INPUT 	0x00U
#define GPIO_MODE_OUTPUT 	0x01U
#define GPIO_MODE_AF		0x02U
#define GPIO_MODE_ANALOGUE	0x03U

#define GPIO_PULL_DIS		0x00U
#define GPIO_PULL_UP		0x01U
#define GPIO_PULL_DWN		0x02U

#define GPIO_SPEED_MIN		0x00U
#define GPIO_SPEED_MEDIUM	0x01U
#define GPIO_SPEED_HIGH 	0x02U
#define GPIO_SPEED_MAX 		0x03U

#define GPIO_PWM_AF1		0x01U
#define GPIO_PWM_AF2		0x02U
#define GPIO_I2C2_AF4		0x04U
#define GPIO_SPI1_AF5		0x05U
#define GPIO_SPI2_AF5		0x05U
#define GPIO_SPI3_AF6       0x06U
#define GPIO_USART2_AF7		0x07U
#define GPIO_UART7_AF8		0x08U


/*****************************************************************************
 Define - Pins
******************************************************************************/
#define PB_UWB_IRQ			6U

#define PE_M1_CTRL_IN1		2U
#define PE_M2_CTRL_IN1		3U
#define PE_M3_CTRL_IN1		4U
#define PE_M4_CTRL_IN1		5U

#define PC_M1_PWM_CH1		6U
#define PC_M2_PWM_CH2		7U
#define PC_M3_PWM_CH3		8U
#define PC_M4_PWM_CH4		9U

#define PG_M1_ENC_IN1		0U
#define PG_M1_ENC_IN2		1U
#define PG_M2_ENC_IN1		2U
#define PG_M2_ENC_IN2		3U
#define PG_M3_ENC_IN1		4U
#define PG_M3_ENC_IN2		5U
#define PG_M4_ENC_IN1		6U
#define PG_M4_ENC_IN2		7U

#define PD_SERVO_PWM_CH1	12U

#define PB_LED_BLUE			7U
#define PB_LED_RED			14U

#define PB_US_TRIG			10U
#define PB_US_ECHO			11U

#define PD_USART2_TX_DBG	5U			
#define PD_USART2_RX_DBG	6U

#define PB_LASER_IRQ		5U
#define PB_LASER_XSHUT		4U

#define PA_UWB_SPI1_CS		4U
#define PA_UWB_SPI1_CLK		5U
#define PA_UWB_SPI1_MISO	6U
#define PA_UWB_SPI1_MOSI	7U

#define PE_LCD_RESET		6U
#define PE_LCD_DC			8U
#define PE_LCD_BL			0U
#define PB_LCD_SPI2_CS		13U
#define PD_LCD_SPI2_CLK		3U
#define PB_LCD_SPI2_MISO	14U
#define PB_LCD_SPI2_MOSI	15U

#define PA_IMU_SPI3_CS      15U
#define PC_IMU_SPI3_SCK     10U
#define PC_IMU_SPI3_MISO    11U
#define PC_IMU_SPI3_MOSI    12U
#define PC_IMU_DATA_RDY		3U

//#define PE_UART7_RX			7U
//#define PE_UART7_TX			8U

#define PF_US1_TRIG         8U
#define PF_US2_TRIG         9U
#define PF_US3_TRIG         10U
#define PF_US4_TRIG         11U
#define PF_US5_TRIG         12U
#define PF_US6_TRIG         13U
#define PF_US7_TRIG         14U
#define PF_US8_TRIG         15U

#define PG_US1_ECHO         8U
#define PG_US2_ECHO         9U
#define PG_US3_ECHO         10U
#define PG_US4_ECHO         11U
#define PG_US5_ECHO         12U
#define PG_US6_ECHO         13U
#define PG_US7_ECHO         14U
#define PG_US8_ECHO         15U


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Macro
******************************************************************************/
#define BIT( x )					(1U<<(x))

/* LEDs */
#define LED_RED_ON()				(GPIOB->BSRR = BIT(PB_LED_RED))
#define LED_RED_OFF()				(GPIOB->BSRR = (BIT(PB_LED_RED)<<16U))
#define LED_RED_SET( x )			((x)? LED_RED_ON() : LED_RED_OFF())

#define LED_BLUE_ON()				(GPIOB->BSRR = BIT(PB_LED_BLUE))
#define LED_BLUE_OFF()				(GPIOB->BSRR = (BIT(PB_LED_BLUE)<<16U))
#define LED_BLUE_SET( x )			((x)? LED_BLUE_ON() : LED_BLUE_OFF())

/* LCD */
#define LCD_RESET_LOW()				(GPIOE->BSRR = (BIT(PE_LCD_RESET)<<16U))
#define LCD_RESET_HIGH()			(GPIOE->BSRR = BIT(PE_LCD_RESET))
#define LCD_RESET_SET( x )			((x)? LCD_RESET_HIGH() : LCD_RESET_LOW())

#define LCD_DC_HIGH()				(GPIOE->BSRR = BIT(PE_LCD_DC))
#define LCD_DC_LOW()				(GPIOE->BSRR = (BIT(PE_LCD_DC)<<16U))
#define LCD_DC_SET( x )				((x)? LCD_DC_HIGH() : LCD_DC_LOW())

#define LCD_BL_ON()					(GPIOE->BSRR = BIT(PE_LCD_BL))
#define LCD_BL_OFF()				(GPIOE->BSRR = (BIT(PE_LCD_BL)<<16U))
#define LCD_BL_SET( x )				((x)? LCD_BL_ON() : LCD_BL_OFF())

#define LCD_CS_LOW()				(GPIOB->BSRR = (BIT(PB_LCD_SPI2_CS)<<16U))
#define LCD_CS_HIGH()			(GPIOB->BSRR = BIT(PB_LCD_SPI2_CS))


/******************************************************************************
 Global functions
******************************************************************************/


/******************************************************************************
 @Description 	: 

 @param			: 
 
 @revision		: 1.0.0
 
******************************************************************************/
void PortInit( void );



#endif /* __HAL_DOT_H__ */









