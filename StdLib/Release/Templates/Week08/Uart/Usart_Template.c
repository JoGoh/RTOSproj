/******************************************************************************
 @filename      Uart.c

 @project       UART hardware driver
 
 @description    
 
 @version       1.0.0

 @revision    
******************************************************************************/

#include "Common.h"
#include "Dma.h"
#include "Serial.h"
#include "Hal.h"


/******************************************************************************
 Define
******************************************************************************/
#define TOTAL_PORT        4U
#define APB1              1U
#define APB2              2U


/******************************************************************************
 Export functions
******************************************************************************/
static int  UartInit( void *pHandle, uint8_t nPort, uint32_t nBaud );
static void UartSetIrqLevel( void const  *pHandle, uint32_t nLevel );
static int  UartSetBaud( void const *pHandle, uint32_t nBaud );
static int  UartSetCfg( void const *pHandle, UART_CFG Databit, UART_CFG Parity, UART_CFG Stopbit );
static int  UartLoopback( void const *pHandle, int bEnable );
static void UartWrite( void const *pHandle, char Data );
static void UartDmaTx( void *pHandle, void const *pData, int nSize );
static char UartRead( void const *pHandle );
static void UartDmaRx( void *pHandle, void *pData, int nSize );
static int  UartIsTxEnd( void const *pHandle );
static int  UartIsTxReady( void const *pHandle );
static int  UartIsRxReady( void const *pHandle );
static void UartTxEnd( void const *pHandle );
static void UartRxEnd( void const *pHandle );
static void UartLock( void *pHandle );
static void UartUnlock( void *pHandle );


/******************************************************************************
 Global variables
******************************************************************************/
UART_DRIVER const STM32F722X_USART_DRV = 
{
  UartInit,
  UartSetBaud,
  UartSetCfg,
  UartSetIrqLevel,
  UartLoopback,
  UartWrite,
  UartDmaTx,
  UartRead,
  UartDmaRx,
  UartIsTxEnd,
  UartIsTxReady,
  UartIsRxReady,
  UartTxEnd,
  UartRxEnd,
  UartLock,
  UartUnlock
};

/******************************************************************************
 Local const variables
******************************************************************************/
static const int BUS_CLOCK[] = { 0, APB2, APB1, APB1, 0, 0, APB2 };


/******************************************************************************
 Local variables
******************************************************************************/
static volatile PUART_HANDLE g_UartIrqHandles[TOTAL_PORT];
static volatile int g_bToggle = 0;

/******************************************************************************
 Implementations
******************************************************************************/
static int
UartInit(
  void    *pHandle,
  uint8_t    nPort,
  uint32_t  nBaud
  )
{
  USART_TypeDef  *uart;
  IRQn_Type      irq;
  int32_t        div;
  uint8_t        port;
  int32_t        frac;
  int32_t        clock = SystemCoreClock;
  UART_HANDLE    *handle = (UART_HANDLE *)pHandle;
  
  ASSERT( 0 != pHandle );
  
  /* Determined base port pointer and 
     Enable the clock to the selected UART */
  switch( nPort )
  {
    case 1:
      port = 0;
      uart = USART1;
      irq = USART1_IRQn;
    break;

    case 2:
    /********************************************************
    * To do: ...                                             
    ********************************************************/
    break;

    case 3:
    /********************************************************
    * To do: ...                                             
    ********************************************************/
    break;

    case 6:
    /********************************************************
    * To do: ...                                             
    ********************************************************/
    break;
    
    default:
      return UART_STS_NO_PORT;
  }
  
  /* Store uart parameters */
  handle->pUART   = uart;
  handle->Irq     = irq;
  handle->nPort   = nPort;

  /* Keep a copy of handle for the port */
  g_UartIrqHandles[port] = handle;
  
  /* Enable UART */
  uart->CR1 &= ~USART_CR1_UE;
  uart->CR1 |= USART_CR1_OVER8;
  
  /*NOTE:
  We can select USART clock source from RCC DCKCFGR2 register. 
  By default, APB1/2 will be selected */
  /* Calculate the clock frequency into UART. */
  switch( BUS_CLOCK[nPort] )
  {
    case APB1:
      /* Re-calculate current bus clock. User may change it in Hal.c */
      switch( RCC->CFGR & RCC_CFGR_PPRE1 )
      {
        case RCC_CFGR_PPRE1_DIV1:
          clock = SystemCoreClock;
        break;
    
        case RCC_CFGR_PPRE1_DIV2:
          clock = SystemCoreClock>>1U;
        break;
    
        case RCC_CFGR_PPRE1_DIV4:
          clock = SystemCoreClock>>2U;
        break;
    
        case RCC_CFGR_PPRE1_DIV8:
          clock = SystemCoreClock>>3U;
        break;
    
        case RCC_CFGR_PPRE1_DIV16:
          clock = SystemCoreClock>>4U;
        break;

        default:
        break;
      }
    break;

    case APB2:
            /* Re-calculate current bus clock. User may change it in Hal.c */
      switch( RCC->CFGR & RCC_CFGR_PPRE2 )
      {
        case RCC_CFGR_PPRE2_DIV1:
          clock = SystemCoreClock;
        break;
    
        case RCC_CFGR_PPRE2_DIV2:
          clock = SystemCoreClock>>1U;
        break;
    
        case RCC_CFGR_PPRE2_DIV4:
          clock = SystemCoreClock>>2U;
        break;
    
        case RCC_CFGR_PPRE2_DIV8:
          clock = SystemCoreClock>>3U;
        break;
    
        case RCC_CFGR_PPRE1_DIV16:
          clock = SystemCoreClock>>4U;
        break;

        default:
        break;
      }
    break;

    default:
    break;
  }

  /********************************************************
  * To do: ...
  * Based on the nBaud, calculate the div variable.
  ********************************************************/
  uart->BRR = div;
  
  /********************************************************
  * To do: ...
  * Turn on necessary interrupts, and enable USART.
  ********************************************************/

  
  return UART_STS_OK;
}


static int
UartSetBaud(
  void const   *pHandle,
  uint32_t     nBaud
  )
{
  int32_t  div;
  int32_t  frac;
  int32_t  clock = SystemCoreClock;
  UART_HANDLE const *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef *uart = (USART_TypeDef *)handle->pUART;
  
  ASSERT( 0 != pHandle );
  
  NVIC_DisableIRQ( (IRQn_Type)handle->Irq );
  
  uart->CR1 &= ~USART_CR1_UE;
  
  RCC->DCKCFGR2 &= ~RCC_DCKCFGR2_USART2SEL_Msk;
  RCC->DCKCFGR2 |= RCC_DCKCFGR2_USART2SEL_0;
  
  /* Enable UART */
  uart->CR1 &= ~USART_CR1_UE;
  uart->CR1 |= USART_CR1_OVER8;
  
  /* Calculate the clock frequency into UART */
  switch( BUS_CLOCK[handle->nPort] )
  {
    case APB1:
      /* Re-calculate current bus clock. User may change it in Hal.c */
      switch( RCC->CFGR & RCC_CFGR_PPRE1 )
      {
        case RCC_CFGR_PPRE1_DIV1:
          clock = SystemCoreClock;
        break;
    
        case RCC_CFGR_PPRE1_DIV2:
          clock = SystemCoreClock>>1U;
        break;
    
        case RCC_CFGR_PPRE1_DIV4:
          clock = SystemCoreClock>>2U;
        break;
    
        case RCC_CFGR_PPRE1_DIV8:
          clock = SystemCoreClock>>3U;
        break;
    
        case RCC_CFGR_PPRE1_DIV16:
          clock = SystemCoreClock>>4U;
        break;

        default:
        break;
      }
    break;

    case APB2:
            /* Re-calculate current bus clock. User may change it in Hal.c */
      switch( RCC->CFGR & RCC_CFGR_PPRE2 )
      {
        case RCC_CFGR_PPRE2_DIV1:
          clock = SystemCoreClock;
        break;
    
        case RCC_CFGR_PPRE2_DIV2:
          clock = SystemCoreClock>>1U;
        break;
    
        case RCC_CFGR_PPRE2_DIV4:
          clock = SystemCoreClock>>2U;
        break;
    
        case RCC_CFGR_PPRE2_DIV8:
          clock = SystemCoreClock>>3U;
        break;
    
        case RCC_CFGR_PPRE1_DIV16:
          clock = SystemCoreClock>>4U;
        break;

        default:
        break;
      }
    break;

    default:
    break;
  }
  
  /********************************************************
  * To do: ...
  * Based on the nBaud, calculate the div variable.
  ********************************************************/
  uart->BRR = div;
  
  /********************************************************
  * To do: ...
  * Turn on necessary interrupts, and enable USART.
  ********************************************************/
  
  return UART_STS_OK;
}


static int
UartSetCfg(
  void const   *pHandle,
  UART_CFG   Databit,
  UART_CFG   Parity,
  UART_CFG   Stopbit
  )
{
  UART_HANDLE const *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef     *uart   = (USART_TypeDef *)handle->pUART;

  ASSERT( 0 != pHandle );
  
  uart->CR1 &= ~USART_CR1_PCE;
  uart->CR2 &= ~(USART_CR2_CPOL | USART_CR2_STOP);

  /* Configure the UART's databit */
  switch( Databit )
  {
    case UART_BITS_8:
      uart->CR1 &= ~USART_CR1_M;
    break;
      
    case UART_BITS_9:
      uart->CR1 |= USART_CR1_M;
    break;
    
    default:
      return UART_STS_NO_CFG;
  }
  
  /* Configure parity */
  switch( Parity )
  {
  /********************************************************
  * To do: ...
  ********************************************************/
  }

  /* Configure stopbit */
  uart->CR2 &= ~USART_CR2_STOP;
  switch( Stopbit )
  {
  /********************************************************
  * To do: ...
  * Turn on necessary interrupts, and enable USART.
  ********************************************************/
  }

  return UART_STS_OK;
}


static void
UartSetIrqLevel(
  void const *pHandle,
  uint32_t   nLevel
  )
{
  UART_HANDLE const *handle = (UART_HANDLE const *)pHandle;
  
  ASSERT( 0 != pHandle );
  
  NVIC_SetPriority( (IRQn_Type)handle->Irq, nLevel );
}


static int
UartLoopback(
  void const *pHandle,
  int        bEnable
  )
{
  ASSERT( 0 != pHandle );
  
  UNUSE( bEnable );
  /* No implemantation. LPC17XX not supported */
  return UART_STS_OK;
}


static void
UartWrite(
  void const   *pHandle,
  char         Data
  )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef       *uart   = (USART_TypeDef *)handle->pUART;

  ASSERT( 0 != pHandle );
  
  /********************************************************
  * To do: Write data to the UART transmission register,
  * and enable the necessary interrnupt.
  ********************************************************/

}


static void  UartDmaTx( void *pHandle, void const *pData, int nSize )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef       *uart   = (USART_TypeDef *)handle->pUART;

  ASSERT( 0 != pHandle );
  ASSERT( 0 != pData );
  ASSERT( 0 != nSize );

  uart->CR1 &= ~USART_CR1_TXEIE;

  DmaStart( handle->pDmaTx, (uint32_t)pData, (uint32_t)(&uart->TDR), nSize );

  uart->ICR = USART_ICR_TCCF;
  uart->CR3 |= USART_CR3_DMAT;
}


static char UartRead( void const *pHandle )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;

  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: Read data from the UART receiving register,
  * and return this value.
  ********************************************************/

}


static void  UartDmaRx( void *pHandle, void *pData, int nSize )
{
  char dummy;
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;

  ASSERT( 0 != pHandle );
  ASSERT( 0 != pData );
  ASSERT( 0 != nSize );

  DmaStop( handle->pDmaRx );

  uart->CR1 &= ~USART_CR1_RXNEIE;
  uart->ICR = 0xffffffff;
  dummy = uart->RDR;
  while( 0 != (uart->ISR&USART_ISR_RXNE) )
  {
    dummy = uart->RDR;
  }
  
  DmaStart( handle->pDmaRx, (uint32_t)(&uart->RDR), (uint32_t)pData, nSize );

  uart->ICR = USART_ICR_ORECF;
  uart->CR3 |= USART_CR3_DMAR;
}


static int UartIsTxEnd( void const *pHandle )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;
  
  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: decide the return value:
  TRUE: TX end, FALSE: else;
  ********************************************************/

}


static int UartIsTxReady( void const *pHandle )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;
  
  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: decide the return value:
  TRUE: TX ready, FALSE: else;
  ********************************************************/

}


static int UartIsRxReady( void const *pHandle )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;
  
  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: decide the return value:
  TRUE: RX ready, FALSE: else;
  ********************************************************/

}


static void UartTxEnd( void const *pHandle )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;
  
  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: processing when transmission is finished.
  ********************************************************/

}


static void UartRxEnd( void const *pHandle )
{
  UART_HANDLE const   *handle = (UART_HANDLE const *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;
  
  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: processing when receiving is finished.
  ********************************************************/

}


static void UartLock( void *pHandle )
{
  UART_HANDLE *handle = (UART_HANDLE *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;

  ASSERT( 0 != pHandle );
  handle->lparam = uart->CR1;
  //NVIC_DisableIRQ( (IRQn_Type)handle->Irq );
  uart->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_RXNEIE);
}


static void UartUnlock( void *pHandle )
{
  UART_HANDLE *handle = (UART_HANDLE *)pHandle;
  USART_TypeDef   *uart   = (USART_TypeDef *)handle->pUART;
  ASSERT( 0 != pHandle );
  
  //NVIC_EnableIRQ( (IRQn_Type)handle->Irq );
  uart->CR1 = handle->lparam;
}


static void uart_Handler( PUART_HANDLE pHandle, USART_TypeDef *pUart )
{
  int status;
  int tmp;

  ASSERT( 0 != pUart );
  ASSERT( 0 != pHandle );

  status   = pUart->ISR;

  /* Check for Tx IRQ */
  if( 0 != (status & USART_ISR_TC) )
  {
    UartIsrTx( pHandle );
  }

    /* Check for Rx IRQ */
  if( 0 != (status & USART_ISR_RXNE) )
  {
    UartIsrRx( pHandle );
  }

  if( 0 != (status & USART_ISR_ORE) )
  {
      tmp = pUart->RDR;
      pUart->ICR |= USART_ICR_ORECF;
  }
}


/******************************************************************************
 Interrupt Service Routines
******************************************************************************/
void USART1_IRQHandler( void ) __attribute__ ((interrupt));
void USART1_IRQHandler( void )
{
  uart_Handler( g_UartIrqHandles[0], USART1 );
}


void USART2_IRQHandler( void ) __attribute__ ((interrupt));
void USART2_IRQHandler( void )
{
    uart_Handler( g_UartIrqHandles[1], USART2 );
}


void USART3_IRQHandler( void ) __attribute__ ((interrupt));
void USART3_IRQHandler( void )
{
    uart_Handler( g_UartIrqHandles[2], USART3 );
}


void USART6_IRQHandler( void ) __attribute__ ((interrupt));
void USART6_IRQHandler( void )
{
    uart_Handler( g_UartIrqHandles[3], USART6 );
}


















