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
#define PB_LED						11U
#define PA_SPI_CS					4U
#define PA_UWB_RESET				8U
#define PA_UWB_IRQ                  9U


/*****************************************************************************
 Type definition
******************************************************************************/

/*****************************************************************************
 Macro
******************************************************************************/
#define LED_OFF()                (GPIOB->BSRR = BIT(PB_LED)) /* Active low */
#define LED_ON()               (GPIOB->BRR = BIT(PB_LED))
#define LED_SET( x )            ((x)? LED_ON() : LED_OFF())

#define UWB_CS_ASSERT()			(GPIOA->BRR = BIT(PA_SPI_CS))
#define UWB_CS_DEASSERT()		(GPIOA->BSRR = BIT(PA_SPI_CS))

/* UWB Reset */
#define UWB_RESET_ON()				(GPIOA->BSRR = BIT(PA_UWB_RESET))
#define UWB_RESET_OFF()				(GPIOA->BSRR = (BIT(PA_UWB_RESET)<<16U))
#define UWB_RESET_SET( x )			((x)? UWB_RESET_ON() : UWB_RESET_OFF())


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









