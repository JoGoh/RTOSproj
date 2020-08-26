/*****************************************************************************
 @Project  : SEP200-250
 @File     : spim.c
 @Details  : SPI Master hardware layer                    
 @Author   : Liang TANG
 @Hardware : STM32F722
 
 --------------------------------------------------------------------------
 @Revision  :
  Ver    Author      Date          Changes
 --------------------------------------------------------------------------
   1.0  Lian Chai   2018-Sep-01    Initial Release
   1.1  Liang       2019-Jan-18    Remove the SPI design code, and provide
                                   the template for DMA related functions.
******************************************************************************/
#include <Common.h>
#include "math.h"
#include "Hal.h"

#ifdef _DMA_EN
  #include "Dma.h"
#endif

#include "spim.h"


/*****************************************************************************
 Define
******************************************************************************/
#define TOTAL_SPI      5U

#define SPI_CAST_8BIT( x )  (*(__IO uint8_t *)(x))


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Local File Variables
******************************************************************************/
/*****************************************************************************
 g_pSpiIrqhandles is an array to store all SPI handler's addresses.
 1) During the SPI Init, the corresponding SPI handler address should be written 
    to the specified address of this array.
 2) During the SPI interrupt ISR, based on which SPI is triggered, the corresponding
    g_pSpiIrqhandles address is accessed to retrieve the desired SPI hander address.
 
 The mapping between the array address and SPI ID is:
   g_pSpiIrqhandles[0]: SPI 1;
   g_pSpiIrqhandles[1]: SPI 2;
   ...
   g_pSpiIrqhandles[4]: SPI 5;
******************************************************************************/
static volatile PSPIM_HANDLE g_pSpiIrqhandles[TOTAL_SPI] = { 0, 0, 0, 0, 0 };

#ifdef _DMA_EN
  static void spi_cbDmaTxHalf( void *pContext );
  static void spi_cbDmaRxHalf( void *pContext );
  static void spi_cbDmaTxComp( void *pContext );
  static void spi_cbDmaRxComp( void *pContext );
  static void spi_cbDmaTxError( void *pContext );
  static void spi_cbDmaRxError( void *pContext );
#endif

/*****************************************************************************
 Local Helpers
******************************************************************************/
#ifdef _DMA_EN
  static void  spi_DmaTx( void *pHandle, void const *pData, int nSize );
  static void  spi_DmaRx( void *pHandle, void *pData, int nSize );
#endif

static void SPI_Handler( PSPIM_HANDLE pHandle );


/*****************************************************************************
 Export functions
******************************************************************************/;


/*****************************************************************************
 Implementation
******************************************************************************/
int
SpimInit(
  void              *pHandle,
  char               nPort,
  int                nSpeed,
  SPIM_CFG           ClkInactive,
  SPIM_CFG           ClkEdge,
  SPIM_CFG           DATA_SIZE )
{
  ASSERT( 0 != pHandle );
  ASSERT( 0 != nSpeed );
  ASSERT( 0 != nPort );
  /********************************************************
  * To do:
   1) Based on the nPort, determine:
     spi (which SPI, or which address for the pointer), irq and apb.
   And these info shoudl be stored in the "handle".
   2) Store the handle address to the array: g_pSpiIrqhandles;
   3) Set the SPI register via the spi-> pointers.
   At beginning, a fixed speed can be used, instead of automatic
   speed setting.
   4) Use the NVIC_EnableIRQ function to enable the irq.
  ********************************************************/


}



void
SpimLinkDMA(
  void              *pHandle,
  void              *pDmaTxHandle,
  void              *pDmaRxHandle
  )
{
#ifdef _DMA_EN
  PSPIM_HANDLE handle      = (PSPIM_HANDLE)pHandle;
  SPI_TypeDef *spi         = (SPI_TypeDef *)handle->pSpi;
  DMA_HANDLE  *dmaTxHandle = (DMA_HANDLE *)pDmaTxHandle;
  DMA_HANDLE  *dmaRxHandle = (DMA_HANDLE *)pDmaRxHandle;

  ASSERT( 0 != pHandle );

  handle->pDmaTx = pDmaTxHandle;
  handle->pDmaRx = pDmaRxHandle;

  if( 0 != pDmaTxHandle )
  {
    dmaTxHandle->pLinkContext = handle;
    DmaAddCallback(
    pDmaTxHandle,
    spi_cbDmaTxHalf,
    spi_cbDmaTxComp,
    spi_cbDmaTxError );
  }

  if( 0 != pDmaRxHandle )
  {
    dmaRxHandle->pLinkContext = handle;
    DmaAddCallback(
    pDmaRxHandle,
    spi_cbDmaRxHalf,
    spi_cbDmaRxComp,
    spi_cbDmaRxError );
  }
#endif
}


int SpimSetDataSize( void *pHandle, SPIM_CFG DATA_SIZE )
{
  /********************************************************
  * To do:
  * This function's implementation can be skipped at beginning. 
  ********************************************************/


}


int SpimSetSpeed( void *pHandle, int nSpeed )
{
  /********************************************************
  * To do: 
  * This function's implementation can be skipped at beginning.
  ********************************************************/


}


void SpimAddCallbackTransferDone(
  void              *phandle,
  SPIM_CB_TRFR_DONE *pfDone )
{
  PSPIM_HANDLE handle = (PSPIM_HANDLE)phandle;
  
  ASSERT( 0 != phandle );
  ASSERT( 0 != pfDone );
  
  handle->pfDone = pfDone;
}


void SpimTransfer(
  void              *phandle,
  void const        *pTxBuf,
  void              *pRxBuf,
  int                nSize
  )
{
  PSPIM_HANDLE  handle = (PSPIM_HANDLE)phandle;
  SPI_TypeDef   *spi   = (SPI_TypeDef *)handle->pSpi;
  
  ASSERT( 0 != phandle );
  ASSERT( 0 != pTxBuf );
  ASSERT( 0 != nSize );
  
    
  handle->nTxCount  = 0;
  handle->nRxCount  = 0;
  
  /* This driver need to modify if datasize more than 8 bits */
  if( FALSE == handle->bTransferWord )
  {
    handle->pRxBuf   = (char *)pRxBuf;
    handle->pTxBuf   = (char *)pTxBuf;
    handle->nSize  = nSize;

#ifdef _DMA_EN
    if( 0 != handle->pDmaRx )
    {
      if( 0 != pRxBuf )
      {
        spi_DmaRx( handle, handle->pRxBuf, nSize );
      }
      else
      {
        spi_DmaRx( handle, &handle->Dummy, nSize );
      }
    }

    if( 0 != handle->pDmaTx )
    {
      spi_DmaTx( handle, handle->pTxBuf, nSize );
      return;
    }
#endif
    SPI_CAST_8BIT( &spi->DR ) = handle->pTxBuf[0];
  }
  else
  {
    handle->pRxWordBuf   = (uint16_t *)pRxBuf;
    handle->pTxWordBuf   = (uint16_t *)pTxBuf;
    handle->nSize  = nSize>>1;

#ifdef _DMA_EN
    if( 0 != handle->pDmaRx )
    {
      if( 0 != pRxBuf )
      {
        spi_DmaRx( handle, handle->pRxWordBuf, nSize );
      }
      else
      {
        spi_DmaRx( handle, &handle->Dummy, nSize );
      }
    }

    if( 0 != handle->pDmaTx )
    {
      spi_DmaTx( handle, handle->pTxWordBuf, nSize );
      return;
    }
#endif
    spi->DR = handle->pTxWordBuf[0];
  }

  /********************************************************   
  * To do: increase nTxCount, config CR2 REG, and start SPI                                                    
  ********************************************************/   

}


/*****************************************************************************
 Callback functions: these DMA related callback functions can be ignored.
******************************************************************************/
#ifdef _DMA_EN
static void spi_cbDmaTxHalf( void *pContext )
{
}


static void spi_cbDmaRxHalf( void *pContext )
{
}


static void spi_cbDmaTxComp( void *pContext )
{

}


static void spi_cbDmaRxComp( void *pContext )
{
  PSPIM_HANDLE  handle   = (PSPIM_HANDLE)pContext;

  /* Callback to application */
  if( 0 != handle->pfDone )  /* The pointer maybe 0 */
  {
    handle->pfDone();
  }
}


static void spi_cbDmaTxError( void *pContext )
{
}


static void spi_cbDmaRxError( void *pContext )
{
}
#endif

/*****************************************************************************
 Local functions
******************************************************************************/
#ifdef _DMA_EN
static void  spi_DmaTx( void *pHandle, void const *pData, int nSize )
{
  PSPIM_HANDLE  handle = (PSPIM_HANDLE)pHandle;
  SPI_TypeDef   *spi   = handle->pSpi;
  int size = nSize;

  ASSERT( 0 != pHandle );
  ASSERT( 0 != pData );
  ASSERT( 0 != nSize );

  spi->CR2 &= ~SPI_CR2_TXDMAEN;
  spi->CR1 &= ~SPI_CR1_SPE;

  spi->CR2 &= ~SPI_CR2_LDMATX;

  if( 16 == handle->DataSize )
  {
    if ((nSize & 0x1U) == 0x0U)
    {
      spi->CR2 &= ~SPI_CR2_LDMATX;
      size = nSize>>1;
    }
    else
    {
      spi->CR2 |= SPI_CR2_LDMATX;
      size = (nSize>>1) + 1;
    }
  }

  DmaStart( handle->pDmaTx, (uint32_t)pData, (uint32_t)(&spi->DR), size );
  spi->CR2 |= SPI_CR2_TXDMAEN;
  spi->CR1 |= SPI_CR1_SPE;
}


static void  spi_DmaRx( void *pHandle, void *pData, int nSize )
{
  PSPIM_HANDLE  handle   = (PSPIM_HANDLE)pHandle;
  SPI_TypeDef   *spi   = handle->pSpi;
  int size = nSize;

  ASSERT( 0 != pHandle );
  ASSERT( 0 != pData );
  ASSERT( 0 != nSize );

  spi->CR2 &= ~SPI_CR2_RXDMAEN;
  spi->CR1 &= ~SPI_CR1_SPE;

  if( handle->DataSize > 8 )
  {
    spi->CR2 &= ~SPI_CR2_FRXTH;
  }
  else
  {
    spi->CR2 |= SPI_CR2_FRXTH;
  }

  spi->CR2 &= ~SPI_CR2_LDMATX;

  if( 16 == handle->DataSize )
  {
    if ((nSize & 0x1U) == 0x0U)
    {
      spi->CR2 &= ~SPI_CR2_LDMARX;
            size = nSize>>1;
    }
    else
    {
      spi->CR2 |= SPI_CR2_LDMARX;
      size = (size>>1) + 1;
    }
  }

  DmaStart( handle->pDmaRx, (uint32_t)(&spi->DR), (uint32_t)pData, size );

  spi->CR2 |= SPI_CR2_RXDMAEN;
}

#endif


/******************************************************************************
 @Description: This is the SPI ISR implementation, which is called by one of 
               the ISR trigger functions from SPI1_IRQHandler to SPI5_IRQHandler.
               Similar to the UART driver, when this function is triggered, it 
               means there is either TX empty or RX not empty interrupt (and some
               others, based on the interrupt enable setting).
               Then this function needs to handle these interrupts, and process 
               the transmission data buffer or the receiving data buffers.
 @param      : pHandle: SPI handle pointer/address
 @revision   : 1.0.0
******************************************************************************/
static void SPI_Handler( PSPIM_HANDLE pHandle )
{
  /********************************************************
  * To do: 
  ********************************************************/


}


/*****************************************************************************
 Interrupt
******************************************************************************/
void SPI1_IRQHandler( void )
{
  ASSERT( 0 != g_pSpiIrqhandles[0] );
  
  SPI_Handler( g_pSpiIrqhandles[0] );

}


void SPI2_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/

}


void SPI3_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/

}


void SPI4_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/

}


void SPI5_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/

}

