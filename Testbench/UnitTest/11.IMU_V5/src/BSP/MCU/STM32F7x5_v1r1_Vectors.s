/*****************************************************************************
 *                   SEGGER Microcontroller GmbH & Co. KG                    *
 *            Solutions for real time microcontroller applications           *
 *****************************************************************************
 *                                                                           *
 *               (c) 2017 SEGGER Microcontroller GmbH & Co. KG               *
 *                                                                           *
 *           Internet: www.segger.com   Support: support@segger.com          *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                         Preprocessor Definitions                          *
 *                         ------------------------                          *
 * VECTORS_IN_RAM                                                            *
 *                                                                           *
 *   If defined, an area of RAM will large enough to store the vector table  *
 *   will be reserved.                                                       *
 *                                                                           *
 *****************************************************************************/

  .syntax unified
  .code 16

  .section .init, "ax"
  .align 0

/*****************************************************************************
 * Default Exception Handlers                                                *
 *****************************************************************************/

  .thumb_func
  .weak NMI_Handler
NMI_Handler:
  b .

  .thumb_func
  .weak HardFault_Handler
HardFault_Handler:
  b .

  .thumb_func
  .weak SVC_Handler
SVC_Handler:
  b .

  .thumb_func
  .weak PendSV_Handler
PendSV_Handler:
  b .

  .thumb_func
  .weak SysTick_Handler
SysTick_Handler:
  b .

  .thumb_func
Dummy_Handler:
  b .

#if defined(__OPTIMIZATION_SMALL)

  .weak WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,Dummy_Handler

  .weak PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Dummy_Handler

  .weak TAMP_STAMP_IRQHandler
  .thumb_set TAMP_STAMP_IRQHandler,Dummy_Handler

  .weak RTC_WKUP_IRQHandler
  .thumb_set RTC_WKUP_IRQHandler,Dummy_Handler

  .weak FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Dummy_Handler

  .weak RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Dummy_Handler

  .weak EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Dummy_Handler

  .weak EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Dummy_Handler

  .weak EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Dummy_Handler

  .weak EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Dummy_Handler

  .weak EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Dummy_Handler

  .weak DMA1_Stream0_IRQHandler
  .thumb_set DMA1_Stream0_IRQHandler,Dummy_Handler

  .weak DMA1_Stream1_IRQHandler
  .thumb_set DMA1_Stream1_IRQHandler,Dummy_Handler

  .weak DMA1_Stream2_IRQHandler
  .thumb_set DMA1_Stream2_IRQHandler,Dummy_Handler

  .weak DMA1_Stream3_IRQHandler
  .thumb_set DMA1_Stream3_IRQHandler,Dummy_Handler

  .weak DMA1_Stream4_IRQHandler
  .thumb_set DMA1_Stream4_IRQHandler,Dummy_Handler

  .weak DMA1_Stream5_IRQHandler
  .thumb_set DMA1_Stream5_IRQHandler,Dummy_Handler

  .weak DMA1_Stream6_IRQHandler
  .thumb_set DMA1_Stream6_IRQHandler,Dummy_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Dummy_Handler

  .weak CAN1_TX_IRQHandler
  .thumb_set CAN1_TX_IRQHandler,Dummy_Handler

  .weak CAN1_RX0_IRQHandler
  .thumb_set CAN1_RX0_IRQHandler,Dummy_Handler

  .weak CAN1_RX1_IRQHandler
  .thumb_set CAN1_RX1_IRQHandler,Dummy_Handler

  .weak CAN1_SCE_IRQHandler
  .thumb_set CAN1_SCE_IRQHandler,Dummy_Handler

  .weak EXTI9_5_IRQHandler
  .thumb_set EXTI9_5_IRQHandler,Dummy_Handler

  .weak TIM1_BRK_TIM9_IRQHandler
  .thumb_set TIM1_BRK_TIM9_IRQHandler,Dummy_Handler

  .weak TIM1_UP_TIM10_IRQHandler
  .thumb_set TIM1_UP_TIM10_IRQHandler,Dummy_Handler

  .weak TIM1_TRG_COM_TIM11_IRQHandler
  .thumb_set TIM1_TRG_COM_TIM11_IRQHandler,Dummy_Handler

  .weak TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler,Dummy_Handler

  .weak TIM2_IRQHandler
  .thumb_set TIM2_IRQHandler,Dummy_Handler

  .weak TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,Dummy_Handler

  .weak TIM4_IRQHandler
  .thumb_set TIM4_IRQHandler,Dummy_Handler

  .weak I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Dummy_Handler

  .weak I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Dummy_Handler

  .weak I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler,Dummy_Handler

  .weak I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Dummy_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Dummy_Handler

  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Dummy_Handler

  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Dummy_Handler

  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Dummy_Handler

  .weak USART3_IRQHandler
  .thumb_set USART3_IRQHandler,Dummy_Handler

  .weak EXTI15_10_IRQHandler
  .thumb_set EXTI15_10_IRQHandler,Dummy_Handler

  .weak RTC_ALARM_IRQHandler
  .thumb_set RTC_ALARM_IRQHandler,Dummy_Handler

  .weak OTG_FS_WKUP_IRQHandler
  .thumb_set OTG_FS_WKUP_IRQHandler,Dummy_Handler

  .weak TIM8_BRK_TIM12_IRQHandler
  .thumb_set TIM8_BRK_TIM12_IRQHandler,Dummy_Handler

  .weak TIM8_UP_TIM13_IRQHandler
  .thumb_set TIM8_UP_TIM13_IRQHandler,Dummy_Handler

  .weak TIM8_TRG_COM_TIM14_IRQHandler
  .thumb_set TIM8_TRG_COM_TIM14_IRQHandler,Dummy_Handler

  .weak TIM8_CC_IRQHandler
  .thumb_set TIM8_CC_IRQHandler,Dummy_Handler

  .weak DMA1_Stream7_IRQHandler
  .thumb_set DMA1_Stream7_IRQHandler,Dummy_Handler

  .weak FMC_IRQHandler
  .thumb_set FMC_IRQHandler,Dummy_Handler

  .weak SDMMC1_IRQHandler
  .thumb_set SDMMC1_IRQHandler,Dummy_Handler

  .weak TIM5_IRQHandler
  .thumb_set TIM5_IRQHandler,Dummy_Handler

  .weak SPI3_IRQHandler
  .thumb_set SPI3_IRQHandler,Dummy_Handler

  .weak UART4_IRQHandler
  .thumb_set UART4_IRQHandler,Dummy_Handler

  .weak UART5_IRQHandler
  .thumb_set UART5_IRQHandler,Dummy_Handler

  .weak TIM6_DAC_IRQHandler
  .thumb_set TIM6_DAC_IRQHandler,Dummy_Handler

  .weak TIM7_IRQHandler
  .thumb_set TIM7_IRQHandler,Dummy_Handler

  .weak DMA2_Stream0_IRQHandler
  .thumb_set DMA2_Stream0_IRQHandler,Dummy_Handler

  .weak DMA2_Stream1_IRQHandler
  .thumb_set DMA2_Stream1_IRQHandler,Dummy_Handler

  .weak DMA2_Stream2_IRQHandler
  .thumb_set DMA2_Stream2_IRQHandler,Dummy_Handler

  .weak DMA2_Stream3_IRQHandler
  .thumb_set DMA2_Stream3_IRQHandler,Dummy_Handler

  .weak DMA2_Stream4_IRQHandler
  .thumb_set DMA2_Stream4_IRQHandler,Dummy_Handler

  .weak ETH_IRQHandler
  .thumb_set ETH_IRQHandler,Dummy_Handler

  .weak ETH_WKUP_IRQHandler
  .thumb_set ETH_WKUP_IRQHandler,Dummy_Handler

  .weak CAN2_TX_IRQHandler
  .thumb_set CAN2_TX_IRQHandler,Dummy_Handler

  .weak CAN2_RX0_IRQHandler
  .thumb_set CAN2_RX0_IRQHandler,Dummy_Handler

  .weak CAN2_RX1_IRQHandler
  .thumb_set CAN2_RX1_IRQHandler,Dummy_Handler

  .weak CAN2_SCE_IRQHandler
  .thumb_set CAN2_SCE_IRQHandler,Dummy_Handler

  .weak OTG_FS_IRQHandler
  .thumb_set OTG_FS_IRQHandler,Dummy_Handler

  .weak DMA2_Stream5_IRQHandler
  .thumb_set DMA2_Stream5_IRQHandler,Dummy_Handler

  .weak DMA2_Stream6_IRQHandler
  .thumb_set DMA2_Stream6_IRQHandler,Dummy_Handler

  .weak DMA2_Stream7_IRQHandler
  .thumb_set DMA2_Stream7_IRQHandler,Dummy_Handler

  .weak USART6_IRQHandler
  .thumb_set USART6_IRQHandler,Dummy_Handler

  .weak I2C3_EV_IRQHandler
  .thumb_set I2C3_EV_IRQHandler,Dummy_Handler

  .weak I2C3_ER_IRQHandler
  .thumb_set I2C3_ER_IRQHandler,Dummy_Handler

  .weak OTG_HS_EP1_OUT_IRQHandler
  .thumb_set OTG_HS_EP1_OUT_IRQHandler,Dummy_Handler

  .weak OTG_HS_EP1_IN_IRQHandler
  .thumb_set OTG_HS_EP1_IN_IRQHandler,Dummy_Handler

  .weak OTG_HS_WKUP_IRQHandler
  .thumb_set OTG_HS_WKUP_IRQHandler,Dummy_Handler

  .weak OTG_HS_IRQHandler
  .thumb_set OTG_HS_IRQHandler,Dummy_Handler

  .weak DCMI_IRQHandler
  .thumb_set DCMI_IRQHandler,Dummy_Handler

  .weak RNG_IRQHandler
  .thumb_set RNG_IRQHandler,Dummy_Handler

  .weak FPU_IRQHandler
  .thumb_set FPU_IRQHandler,Dummy_Handler

  .weak UART7_IRQHandler
  .thumb_set UART7_IRQHandler,Dummy_Handler

  .weak UART8_IRQHandler
  .thumb_set UART8_IRQHandler,Dummy_Handler

  .weak SPI4_IRQHandler
  .thumb_set SPI4_IRQHandler,Dummy_Handler

  .weak SPI5_IRQHandler
  .thumb_set SPI5_IRQHandler,Dummy_Handler

  .weak SPI6_IRQHandler
  .thumb_set SPI6_IRQHandler,Dummy_Handler

  .weak SAI1_IRQHandler
  .thumb_set SAI1_IRQHandler,Dummy_Handler

  .weak LCD_TFT_IRQHandler
  .thumb_set LCD_TFT_IRQHandler,Dummy_Handler

  .weak LTDC_ER_IRQHandler
  .thumb_set LTDC_ER_IRQHandler,Dummy_Handler

  .weak DMA2D_IRQHandler
  .thumb_set DMA2D_IRQHandler,Dummy_Handler

  .weak SAI2_IRQHandler 
  .thumb_set SAI2_IRQHandler ,Dummy_Handler

  .weak QUADSPI_IRQHandler
  .thumb_set QUADSPI_IRQHandler,Dummy_Handler

  .weak LPTIM1_IRQHandler
  .thumb_set LPTIM1_IRQHandler,Dummy_Handler

  .weak CEC_IRQHandler
  .thumb_set CEC_IRQHandler,Dummy_Handler

  .weak I2C4_EV_IRQHandler
  .thumb_set I2C4_EV_IRQHandler,Dummy_Handler

  .weak I2C4_ER_IRQHandler
  .thumb_set I2C4_ER_IRQHandler,Dummy_Handler

  .weak SPDIF_RX_IRQHandler
  .thumb_set SPDIF_RX_IRQHandler,Dummy_Handler

  .weak DFSDM1_FLT0_IRQHandler
  .thumb_set DFSDM1_FLT0_IRQHandler,Dummy_Handler

  .weak DFSDM1_FLT1_IRQHandler
  .thumb_set DFSDM1_FLT1_IRQHandler,Dummy_Handler

  .weak DFSDM1_FLT2_IRQHandler
  .thumb_set DFSDM1_FLT2_IRQHandler,Dummy_Handler

  .weak DFSDM1_FLT3_IRQHandler
  .thumb_set DFSDM1_FLT3_IRQHandler,Dummy_Handler

  .weak SDMMC2_IRQHandler
  .thumb_set SDMMC2_IRQHandler,Dummy_Handler

  .weak CAN3_TX_IRQHandler
  .thumb_set CAN3_TX_IRQHandler,Dummy_Handler

  .weak CAN3_RX0_IRQHandler
  .thumb_set CAN3_RX0_IRQHandler,Dummy_Handler

  .weak CAN3_RX1_IRQHandler
  .thumb_set CAN3_RX1_IRQHandler,Dummy_Handler

  .weak CAN3_SCE_IRQHandler
  .thumb_set CAN3_SCE_IRQHandler,Dummy_Handler

  .weak MDIOS_IRQHandler
  .thumb_set MDIOS_IRQHandler,Dummy_Handler
#else

  .thumb_func
  .weak WWDG_IRQHandler
WWDG_IRQHandler:
  b .

  .thumb_func
  .weak PVD_IRQHandler
PVD_IRQHandler:
  b .

  .thumb_func
  .weak TAMP_STAMP_IRQHandler
TAMP_STAMP_IRQHandler:
  b .

  .thumb_func
  .weak RTC_WKUP_IRQHandler
RTC_WKUP_IRQHandler:
  b .

  .thumb_func
  .weak FLASH_IRQHandler
FLASH_IRQHandler:
  b .

  .thumb_func
  .weak RCC_IRQHandler
RCC_IRQHandler:
  b .

  .thumb_func
  .weak EXTI0_IRQHandler
EXTI0_IRQHandler:
  b .

  .thumb_func
  .weak EXTI1_IRQHandler
EXTI1_IRQHandler:
  b .

  .thumb_func
  .weak EXTI2_IRQHandler
EXTI2_IRQHandler:
  b .

  .thumb_func
  .weak EXTI3_IRQHandler
EXTI3_IRQHandler:
  b .

  .thumb_func
  .weak EXTI4_IRQHandler
EXTI4_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream0_IRQHandler
DMA1_Stream0_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream1_IRQHandler
DMA1_Stream1_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream2_IRQHandler
DMA1_Stream2_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream3_IRQHandler
DMA1_Stream3_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream4_IRQHandler
DMA1_Stream4_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream5_IRQHandler
DMA1_Stream5_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream6_IRQHandler
DMA1_Stream6_IRQHandler:
  b .

  .thumb_func
  .weak ADC_IRQHandler
ADC_IRQHandler:
  b .

  .thumb_func
  .weak CAN1_TX_IRQHandler
CAN1_TX_IRQHandler:
  b .

  .thumb_func
  .weak CAN1_RX0_IRQHandler
CAN1_RX0_IRQHandler:
  b .

  .thumb_func
  .weak CAN1_RX1_IRQHandler
CAN1_RX1_IRQHandler:
  b .

  .thumb_func
  .weak CAN1_SCE_IRQHandler
CAN1_SCE_IRQHandler:
  b .

  .thumb_func
  .weak EXTI9_5_IRQHandler
EXTI9_5_IRQHandler:
  b .

  .thumb_func
  .weak TIM1_BRK_TIM9_IRQHandler
TIM1_BRK_TIM9_IRQHandler:
  b .

  .thumb_func
  .weak TIM1_UP_TIM10_IRQHandler
TIM1_UP_TIM10_IRQHandler:
  b .

  .thumb_func
  .weak TIM1_TRG_COM_TIM11_IRQHandler
TIM1_TRG_COM_TIM11_IRQHandler:
  b .

  .thumb_func
  .weak TIM1_CC_IRQHandler
TIM1_CC_IRQHandler:
  b .

  .thumb_func
  .weak TIM2_IRQHandler
TIM2_IRQHandler:
  b .

  .thumb_func
  .weak TIM3_IRQHandler
TIM3_IRQHandler:
  b .

  .thumb_func
  .weak TIM4_IRQHandler
TIM4_IRQHandler:
  b .

  .thumb_func
  .weak I2C1_EV_IRQHandler
I2C1_EV_IRQHandler:
  b .

  .thumb_func
  .weak I2C1_ER_IRQHandler
I2C1_ER_IRQHandler:
  b .

  .thumb_func
  .weak I2C2_EV_IRQHandler
I2C2_EV_IRQHandler:
  b .

  .thumb_func
  .weak I2C2_ER_IRQHandler
I2C2_ER_IRQHandler:
  b .

  .thumb_func
  .weak SPI1_IRQHandler
SPI1_IRQHandler:
  b .

  .thumb_func
  .weak SPI2_IRQHandler
SPI2_IRQHandler:
  b .

  .thumb_func
  .weak USART1_IRQHandler
USART1_IRQHandler:
  b .

  .thumb_func
  .weak USART2_IRQHandler
USART2_IRQHandler:
  b .

  .thumb_func
  .weak USART3_IRQHandler
USART3_IRQHandler:
  b .

  .thumb_func
  .weak EXTI15_10_IRQHandler
EXTI15_10_IRQHandler:
  b .

  .thumb_func
  .weak RTC_ALARM_IRQHandler
RTC_ALARM_IRQHandler:
  b .

  .thumb_func
  .weak OTG_FS_WKUP_IRQHandler
OTG_FS_WKUP_IRQHandler:
  b .

  .thumb_func
  .weak TIM8_BRK_TIM12_IRQHandler
TIM8_BRK_TIM12_IRQHandler:
  b .

  .thumb_func
  .weak TIM8_UP_TIM13_IRQHandler
TIM8_UP_TIM13_IRQHandler:
  b .

  .thumb_func
  .weak TIM8_TRG_COM_TIM14_IRQHandler
TIM8_TRG_COM_TIM14_IRQHandler:
  b .

  .thumb_func
  .weak TIM8_CC_IRQHandler
TIM8_CC_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_Stream7_IRQHandler
DMA1_Stream7_IRQHandler:
  b .

  .thumb_func
  .weak FMC_IRQHandler
FMC_IRQHandler:
  b .

  .thumb_func
  .weak SDMMC1_IRQHandler
SDMMC1_IRQHandler:
  b .

  .thumb_func
  .weak TIM5_IRQHandler
TIM5_IRQHandler:
  b .

  .thumb_func
  .weak SPI3_IRQHandler
SPI3_IRQHandler:
  b .

  .thumb_func
  .weak UART4_IRQHandler
UART4_IRQHandler:
  b .

  .thumb_func
  .weak UART5_IRQHandler
UART5_IRQHandler:
  b .

  .thumb_func
  .weak TIM6_DAC_IRQHandler
TIM6_DAC_IRQHandler:
  b .

  .thumb_func
  .weak TIM7_IRQHandler
TIM7_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream0_IRQHandler
DMA2_Stream0_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream1_IRQHandler
DMA2_Stream1_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream2_IRQHandler
DMA2_Stream2_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream3_IRQHandler
DMA2_Stream3_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream4_IRQHandler
DMA2_Stream4_IRQHandler:
  b .

  .thumb_func
  .weak ETH_IRQHandler
ETH_IRQHandler:
  b .

  .thumb_func
  .weak ETH_WKUP_IRQHandler
ETH_WKUP_IRQHandler:
  b .

  .thumb_func
  .weak CAN2_TX_IRQHandler
CAN2_TX_IRQHandler:
  b .

  .thumb_func
  .weak CAN2_RX0_IRQHandler
CAN2_RX0_IRQHandler:
  b .

  .thumb_func
  .weak CAN2_RX1_IRQHandler
CAN2_RX1_IRQHandler:
  b .

  .thumb_func
  .weak CAN2_SCE_IRQHandler
CAN2_SCE_IRQHandler:
  b .

  .thumb_func
  .weak OTG_FS_IRQHandler
OTG_FS_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream5_IRQHandler
DMA2_Stream5_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream6_IRQHandler
DMA2_Stream6_IRQHandler:
  b .

  .thumb_func
  .weak DMA2_Stream7_IRQHandler
DMA2_Stream7_IRQHandler:
  b .

  .thumb_func
  .weak USART6_IRQHandler
USART6_IRQHandler:
  b .

  .thumb_func
  .weak I2C3_EV_IRQHandler
I2C3_EV_IRQHandler:
  b .

  .thumb_func
  .weak I2C3_ER_IRQHandler
I2C3_ER_IRQHandler:
  b .

  .thumb_func
  .weak OTG_HS_EP1_OUT_IRQHandler
OTG_HS_EP1_OUT_IRQHandler:
  b .

  .thumb_func
  .weak OTG_HS_EP1_IN_IRQHandler
OTG_HS_EP1_IN_IRQHandler:
  b .

  .thumb_func
  .weak OTG_HS_WKUP_IRQHandler
OTG_HS_WKUP_IRQHandler:
  b .

  .thumb_func
  .weak OTG_HS_IRQHandler
OTG_HS_IRQHandler:
  b .

  .thumb_func
  .weak DCMI_IRQHandler
DCMI_IRQHandler:
  b .

  .thumb_func
  .weak RNG_IRQHandler
RNG_IRQHandler:
  b .

  .thumb_func
  .weak FPU_IRQHandler
FPU_IRQHandler:
  b .

  .thumb_func
  .weak UART7_IRQHandler
UART7_IRQHandler:
  b .

  .thumb_func
  .weak UART8_IRQHandler
UART8_IRQHandler:
  b .

  .thumb_func
  .weak SPI4_IRQHandler
SPI4_IRQHandler:
  b .

  .thumb_func
  .weak SPI5_IRQHandler
SPI5_IRQHandler:
  b .

  .thumb_func
  .weak SPI6_IRQHandler
SPI6_IRQHandler:
  b .

  .thumb_func
  .weak SAI1_IRQHandler
SAI1_IRQHandler:
  b .

  .thumb_func
  .weak LCD_TFT_IRQHandler
LCD_TFT_IRQHandler:
  b .

  .thumb_func
  .weak LTDC_ER_IRQHandler
LTDC_ER_IRQHandler:
  b .

  .thumb_func
  .weak DMA2D_IRQHandler
DMA2D_IRQHandler:
  b .

  .thumb_func
  .weak SAI2_IRQHandler
SAI2_IRQHandler:
  b .

  .thumb_func
  .weak QUADSPI_IRQHandler
QUADSPI_IRQHandler:
  b .

  .thumb_func
  .weak LPTIM1_IRQHandler
LPTIM1_IRQHandler:
  b .

  .thumb_func
  .weak CEC_IRQHandler
CEC_IRQHandler:
  b .

  .thumb_func
  .weak I2C4_EV_IRQHandler
I2C4_EV_IRQHandler:
  b .

  .thumb_func
  .weak I2C4_ER_IRQHandler
I2C4_ER_IRQHandler:
  b .

  .thumb_func
  .weak SPDIF_RX_IRQHandler
SPDIF_RX_IRQHandler:
  b .

  .thumb_func
  .weak DFSDM1_FLT0_IRQHandler
DFSDM1_FLT0_IRQHandler:
  b .

  .thumb_func
  .weak DFSDM1_FLT1_IRQHandler
DFSDM1_FLT1_IRQHandler:
  b .

  .thumb_func
  .weak DFSDM1_FLT2_IRQHandler
DFSDM1_FLT2_IRQHandler:
  b .

  .thumb_func
  .weak DFSDM1_FLT3_IRQHandler
DFSDM1_FLT3_IRQHandler:
  b .

  .thumb_func
  .weak SDMMC2_IRQHandler
SDMMC2_IRQHandler:
  b .

  .thumb_func
  .weak CAN3_TX_IRQHandler
CAN3_TX_IRQHandler:
  b .

  .thumb_func
  .weak CAN3_RX0_IRQHandler
CAN3_RX0_IRQHandler:
  b .

  .thumb_func
  .weak CAN3_RX1_IRQHandler
CAN3_RX1_IRQHandler:
  b .

  .thumb_func
  .weak CAN3_SCE_IRQHandler
CAN3_SCE_IRQHandler:
  b .

  .thumb_func
  .weak MDIOS_IRQHandler 
MDIOS_IRQHandler:
  b .
#endif

/*****************************************************************************
 * Vector Table                                                              *
 *****************************************************************************/

  .section .vectors, "ax"
  .align 0
  .global _vectors
  .extern __stack_end__
  .extern Reset_Handler

_vectors:
  .word __stack_end__
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word SVC_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word PendSV_Handler
  .word SysTick_Handler
  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word TAMP_STAMP_IRQHandler
  .word RTC_WKUP_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_IRQHandler
  .word EXTI1_IRQHandler
  .word EXTI2_IRQHandler
  .word EXTI3_IRQHandler
  .word EXTI4_IRQHandler
  .word DMA1_Stream0_IRQHandler
  .word DMA1_Stream1_IRQHandler
  .word DMA1_Stream2_IRQHandler
  .word DMA1_Stream3_IRQHandler
  .word DMA1_Stream4_IRQHandler
  .word DMA1_Stream5_IRQHandler
  .word DMA1_Stream6_IRQHandler
  .word ADC_IRQHandler
  .word CAN1_TX_IRQHandler
  .word CAN1_RX0_IRQHandler
  .word CAN1_RX1_IRQHandler
  .word CAN1_SCE_IRQHandler
  .word EXTI9_5_IRQHandler
  .word TIM1_BRK_TIM9_IRQHandler
  .word TIM1_UP_TIM10_IRQHandler
  .word TIM1_TRG_COM_TIM11_IRQHandler
  .word TIM1_CC_IRQHandler
  .word TIM2_IRQHandler
  .word TIM3_IRQHandler
  .word TIM4_IRQHandler
  .word I2C1_EV_IRQHandler
  .word I2C1_ER_IRQHandler
  .word I2C2_EV_IRQHandler
  .word I2C2_ER_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word USART3_IRQHandler
  .word EXTI15_10_IRQHandler
  .word RTC_ALARM_IRQHandler
  .word OTG_FS_WKUP_IRQHandler
  .word TIM8_BRK_TIM12_IRQHandler
  .word TIM8_UP_TIM13_IRQHandler
  .word TIM8_TRG_COM_TIM14_IRQHandler
  .word TIM8_CC_IRQHandler
  .word DMA1_Stream7_IRQHandler
  .word FMC_IRQHandler
  .word SDMMC1_IRQHandler
  .word TIM5_IRQHandler
  .word SPI3_IRQHandler
  .word UART4_IRQHandler
  .word UART5_IRQHandler
  .word TIM6_DAC_IRQHandler
  .word TIM7_IRQHandler
  .word DMA2_Stream0_IRQHandler
  .word DMA2_Stream1_IRQHandler
  .word DMA2_Stream2_IRQHandler
  .word DMA2_Stream3_IRQHandler
  .word DMA2_Stream4_IRQHandler
  .word ETH_IRQHandler
  .word ETH_WKUP_IRQHandler
  .word CAN2_TX_IRQHandler
  .word CAN2_RX0_IRQHandler
  .word CAN2_RX1_IRQHandler
  .word CAN2_SCE_IRQHandler
  .word OTG_FS_IRQHandler
  .word DMA2_Stream5_IRQHandler
  .word DMA2_Stream6_IRQHandler
  .word DMA2_Stream7_IRQHandler
  .word USART6_IRQHandler
  .word I2C3_EV_IRQHandler
  .word I2C3_ER_IRQHandler
  .word OTG_HS_EP1_OUT_IRQHandler
  .word OTG_HS_EP1_IN_IRQHandler
  .word OTG_HS_WKUP_IRQHandler
  .word OTG_HS_IRQHandler
  .word DCMI_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word RNG_IRQHandler
  .word FPU_IRQHandler
  .word UART7_IRQHandler
  .word UART8_IRQHandler
  .word SPI4_IRQHandler
  .word SPI5_IRQHandler
  .word SPI6_IRQHandler
  .word SAI1_IRQHandler
  .word LCD_TFT_IRQHandler
  .word LTDC_ER_IRQHandler
  .word DMA2D_IRQHandler
  .word SAI2_IRQHandler              
  .word QUADSPI_IRQHandler           
  .word LPTIM1_IRQHandler            
  .word CEC_IRQHandler               
  .word I2C4_EV_IRQHandler           
  .word I2C4_ER_IRQHandler           
  .word SPDIF_RX_IRQHandler      
#ifdef __STM32F765_SUBFAMILY    
  .word Dummy_Handler /* Reserved */                     
  .word DFSDM1_FLT0_IRQHandler          
  .word DFSDM1_FLT1_IRQHandler          
  .word DFSDM1_FLT2_IRQHandler         
  .word DFSDM1_FLT3_IRQHandler         
  .word SDMMC2_IRQHandler              
  .word CAN3_TX_IRQHandler             
  .word CAN3_RX0_IRQHandler            
  .word CAN3_RX1_IRQHandler            
  .word CAN3_SCE_IRQHandler            
  .word Dummy_Handler /* Reserved */  
  .word MDIOS_IRQHandler        
#endif    
_vectors_end:

#ifdef VECTORS_IN_RAM
  .section .vectors_ram, "ax"
  .align 0
  .global _vectors_ram

_vectors_ram:
  .space _vectors_end - _vectors, 0
#endif
