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

#define GPIO_TIM1_AF1		0x01U
#define GPIO_TIM2_AF1		0x01U
#define GPIO_PWM_AF1		0x01U
#define GPIO_PWM_AF2		0x02U
#define GPIO_TIM4_AF2		0x02U
#define GPIO_TIM5_AF2		0x02U
#define GPIO_PWM_AF3		0x03U
#define GPIO_I2C1_AF4		0x04U
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

#define PB_LCD_RESET		0U
#define PB_LCD_DC			1U
#define PB_LCD_BL			2U
#define PB_LCD_SPI2_CS		12U
#define PB_LCD_SPI2_CLK		13U
#define PB_LCD_SPI2_MISO	14U
#define PB_LCD_SPI2_MOSI	15U

#define PA_IMU_SPI3_CS      15U
#define PC_IMU_SPI3_SCK     10U
#define PC_IMU_SPI3_MISO    11U
#define PC_IMU_SPI3_MOSI    12U
#define PC_IMU_DATA_RDY		3U

#define PE_UART7_RX			7U
#define PE_UART7_TX			8U


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

/* Optical Sensor */
#define OPTICAL_XSHUT_ON()			(GPIOB->BSRR = BIT(PB_LASER_XSHUT))
#define OPTICAL_XSHUT_OFF()			(GPIOB->BSRR = (BIT(PB_LASER_XSHUT)<<16U))
#define OPTICAL_XSHUT_SET( x )		((x)? OPTICAL_XSHUT_ON() : OPTICAL_XSHUT_OFF())

/* Motors */
#define M1_DIR_CTRL_ON()			(GPIOE->BSRR = BIT(PE_M1_CTRL_IN1))
#define M1_DIR_CTRL_OFF()			(GPIOE->BSRR = (BIT(PE_M1_CTRL_IN1)<<16U))
#define M1_DIR_CTRL_SET( x )		((x)? M1_DIR_CTRL_ON() : M1_DIR_CTRL_OFF())

#define M1_PWM_OUT_EN()				GPIOC->MODER &= ~GPIO_MODER_MODER6;			\
									GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER6_Pos);							
#define M1_PWM_OUT_DIS()			GPIOC->MODER &= ~GPIO_MODER_MODER6;			\
									GPIOC->MODER |= (GPIO_MODE_INPUT<<GPIO_MODER_MODER6_Pos);								
#define M1_PWM_OUT_SET( x )			((x)? M1_PWM_OUT_EN() : M1_PWM_OUT_DIS())

#define M2_DIR_CTRL_ON()			(GPIOE->BSRR = BIT(PE_M2_CTRL_IN1))
#define M2_DIR_CTRL_OFF()			(GPIOE->BSRR = (BIT(PE_M2_CTRL_IN1)<<16U))
#define M2_DIR_CTRL_SET( x )		((x)? M2_DIR_CTRL_ON() : M2_DIR_CTRL_OFF())

#define M2_PWM_OUT_EN()				GPIOC->MODER &= ~GPIO_MODER_MODER7;			\
									GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER7_Pos);
#define M2_PWM_OUT_DIS()			GPIOC->MODER &= ~GPIO_MODER_MODER7;			\
									GPIOC->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER7_Pos);
#define M2_PWM_OUT_SET( x )			((x)? M2_PWM_OUT_EN() : M2_PWM_OUT_DIS())

#define M3_DIR_CTRL_ON()			(GPIOE->BSRR = BIT(PE_M3_CTRL_IN1))
#define M3_DIR_CTRL_OFF()			(GPIOE->BSRR = (BIT(PE_M3_CTRL_IN1)<<16U))
#define M3_DIR_IN_SET( x )			((x)? M3_DIR_CTRL_ON() : M3_DIR_CTRL_OFF())

#define M3_PWM_OUT_EN()				GPIOC->MODER &= ~GPIO_MODER_MODER8;			\
									GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER8_Pos);
#define M3_PWM_OUT_DIS()			GPIOC->MODER &= ~GPIO_MODER_MODER8;			\
									GPIOC->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER8_Pos);
#define M3_PWM_OUT_SET( x )			((x)? M3_PWM_OUT_EN() : M3_PWM_OUT_DIS())

#define M4_DIR_CTRL_ON()			(GPIOE->BSRR = BIT(PE_M4_CTRL_IN1))
#define M4_DIR_CTRL_OFF()			(GPIOE->BSRR = (BIT(PE_M4_CTRL_IN1)<<16U))
#define M4_DIR_CTRL_SET( x )		((x)? M4_DIR_CTRL_ON() : M4_DIR_CTRL_OFF())

#define M4_PWM_OUT_EN()				GPIOC->MODER &= ~GPIO_MODER_MODER9;			\
									GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER9_Pos);
#define M4_PWM_OUT_DIS()			GPIOC->MODER &= ~GPIO_MODER_MODER9;			\
									GPIOC->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER9_Pos);
#define M4_PWM_OUT_SET( x )			((x)? M4_PWM_OUT_EN() : M4_PWM_OUT_DIS())

#define IN_M1_ENC_IN1()				((GPIOG->IDR & BIT(PG_M1_ENC_IN1))? TRUE : FALSE)
#define IN_M1_ENC_IN2()				((GPIOG->IDR & BIT(PG_M1_ENC_IN2))? TRUE : FALSE)

#define IN_M2_ENC_IN1()				((GPIOG->IDR & BIT(PG_M2_ENC_IN1))? TRUE : FALSE)
#define IN_M2_ENC_IN2()				((GPIOG->IDR & BIT(PG_M2_ENC_IN2))? TRUE : FALSE)

#define IN_M3_ENC_IN1()				((GPIOG->IDR & BIT(PG_M3_ENC_IN1))? TRUE : FALSE)
#define IN_M3_ENC_IN2()				((GPIOG->IDR & BIT(PG_M3_ENC_IN2))? TRUE : FALSE)

#define IN_M4_ENC_IN1()				((GPIOG->IDR & BIT(PG_M4_ENC_IN1))? TRUE : FALSE)
#define IN_M4_ENC_IN2()				((GPIOG->IDR & BIT(PG_M4_ENC_IN2))? TRUE : FALSE)

#define US_TRIG_ON()				(GPIOB->BSRR = BIT(PB_US_TRIG))
#define US_TRIG_OFF()				(GPIOB->BSRR = (BIT(PB_US_TRIG)<<16U))
#define US_TRIG_SET( x )			((x)? US_TRIG_ON() : US_TRIG_OFF())
#define IN_US_ECHO()				((GPIOB->IDR & BIT(PB_US_ECHO))? TRUE : FALSE)

#define UWB_CS_ASSERT()				GPIOA->BSRR = GPIO_BSRR_BR_4;
#define UWB_CS_DEASSERT()			GPIOA->BSRR = GPIO_BSRR_BS_4;

#define LCD_RESET_ASSERT()			(GPIOB->BSRR = (BIT(PB_LCD_RESET)<<16U))
#define LCD_RESET_DEASSERT()		(GPIOB->BSRR = BIT(PB_LCD_RESET))

#define LCD_RESET_ASSERT()			(GPIOB->BSRR = (BIT(PB_LCD_RESET)<<16U))
#define LCD_RESET_DEASSERT()		(GPIOB->BSRR = BIT(PB_LCD_RESET))

#define LCD_DC_ON()					(GPIOB->BSRR = BIT(PB_LCD_DC));\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP()
#define LCD_DC_OFF()				(GPIOB->BSRR = (BIT(PB_LCD_DC)<<16U));\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP()

#define LCD_DC_SET( x )			((x)? LCD_DC_ON() : LCD_DC_OFF())

#define LCD_BL_ON()					(GPIOB->BSRR = BIT(PB_LCD_BL))
#define LCD_BL_OFF()				(GPIOB->BSRR = (BIT(PB_LCD_BL)<<16U))
#define LCD_BL_SET( x )			((x)? LCD_BL_ON() : LCD_BL_OFF())

#define LCD_CS_ASSERT()			(GPIOB->BSRR = (BIT(PB_LCD_SPI2_CS)<<16U));\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP()
#define LCD_CS_DEASSERT()		(GPIOB->BSRR = BIT(PB_LCD_SPI2_CS));\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP()

#define MPU_CS_ASSERT()			(GPIOA->BSRR = (BIT(PA_IMU_SPI3_CS)<<16U));\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP()
#define MPU_CS_DEASSERT()		(GPIOA->BSRR = BIT(PA_IMU_SPI3_CS));\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP();\
															__NOP()

#define MPU_SPI_CLK_DIS()      GPIOC->MODER &= ~GPIO_MODER_MODER10; \
                                GPIOC->MODER |= (GPIO_MODE_OUTPUT<<GPIO_MODER_MODER10_Pos); \
                                (GPIOC->BSRR = (BIT(PC_IMU_SPI3_SCK)<<16U))

#define MPU_SPI_CLK_EN()       GPIOC->MODER &= ~GPIO_MODER_MODER10; \
                                GPIOC->MODER |= (GPIO_MODE_AF<<GPIO_MODER_MODER10_Pos)





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









