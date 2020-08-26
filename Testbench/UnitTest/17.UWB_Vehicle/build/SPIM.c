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
	 1.2  goh.j      2020-Jan-16    Completed the missing portions for init,
									Set size, speed & Handler.
   1.3  goh.j      2020-Jan-16    Implemented the transfer done fn & the 
								bottom portion of the SPI Transfer fn.
	 1.4  goh.j      2020-Jan-16    Implemented the SPIx_IRQHandlers.
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
 Local Variables
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
  void     *pHandle,
  char     nPort,
  int       nSpeed,
  SPIM_CFG  ClkInactive,
  SPIM_CFG  ClkEdge,
  SPIM_CFG  DATA_SIZE )
{
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
  IRQn_Type		irq;
  SPI_TypeDef	*spi;
  int32_t		tmp = 0;
  int			apb = 0;
  uint32_t		clock;
  int			div;
  int			prescale;
  PSPIM_HANDLE	handle = (PSPIM_HANDLE)pHandle;
  
  ASSERT( 0 != pHandle );
  ASSERT( 0 != nSpeed );
  ASSERT( 0 != nPort );
  
  
  switch( nPort )
  {
		case 1:
			spi = SPI1;
			irq = SPI1_IRQn;
			apb = 2;
		break;
		
		case 2:
			spi = SPI2;
			irq = SPI2_IRQn;
			apb = 1;
		break;
		
		case 3:
			spi = SPI3;
			irq = SPI3_IRQn;
			apb = 1;
		break;
		
		case 4:
			spi = SPI4;
			irq = SPI4_IRQn;
			apb = 2;
		break;
		
		case 5:
			spi = SPI5;
			irq = SPI5_IRQn;
			apb = 2;
		break;
		default:
			return SPIM_E_INVALID_PORT;
  }
  handle->pSpi = spi;
  handle->Irq = irq;
  handle->Apb = apb;
  
  g_pSpiIrqhandles[nPort-1] = handle;
  
  spi->CR1 &= ~SPI_CR1_SPE;
  spi->I2SCFGR &= ~SPI_I2SCFGR_I2SMOD;
  
  tmp |= SPI_CR1_MSTR;
  
  switch( ClkInactive )
  {
		case SPI_CLK_INACT_LOW:
			tmp &= ~SPI_CR1_CPOL;
		break;
		
		case SPI_CLK_INACT_HIGH:
			tmp |= SPI_CR1_CPOL;
		break;
		
		default:
			return SPIM_E_INVALID_CLK_POLARITY;	  
  }
  
  switch( ClkEdge )
  {
		case SPI_CLK_RISING_EDGE:
			tmp &= ~SPI_CR1_CPHA;
		break;
		
		case SPI_CLK_FALLING_EDGE:
			tmp |= SPI_CR1_CPHA;
		break;
		
		default:
			return SPIM_E_INVALID_CLK_EDGE;
  }
  
  if( 1 == apb)
  {
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
	  
  }
  else if( 2 == apb )
  {
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
			
			case RCC_CFGR_PPRE2_DIV16:
				clock = SystemCoreClock>>4U;
			break;
			
			default:
			break;
	  }
	  
  }
  else 
  {
	  ASSERT( FALSE );
  }
  
  prescale = clock / nSpeed;
  div =0;
  do
  {
	  prescale /= 2;
	  div++;
  }while( 0 != prescale );
  
  tmp &= ~SPI_CR1_BR;
  tmp |= ((div-1)<<SPI_CR1_BR_Pos);
  spi->CR1 = tmp;
  
  spi->CR2 |= SPI_CR2_SSOE;
  spi->CR2 &= ~SPI_CR2_DS;
  
  switch( DATA_SIZE )
  {
		case SPI_DATA_SIZE_4:
			spi->CR2 |= (3U<<SPI_CR2_DS_Pos);
			handle-> DataSize = 4;
		break;
		
		case SPI_DATA_SIZE_5:
			spi->CR2 |= (4U<<SPI_CR2_DS_Pos);
			handle->DataSize = 5;
		break;
		
		case SPI_DATA_SIZE_6:
			spi->CR2 |= (5U<<SPI_CR2_DS_Pos);
			handle->DataSize = 6;
		break;
		
		case SPI_DATA_SIZE_7:
			spi->CR2 |= (6U<<SPI_CR2_DS_Pos);
			handle->DataSize = 7;
		break;
		
		case SPI_DATA_SIZE_8:
			spi->CR2 |= (7U<<SPI_CR2_DS_Pos);
			handle->DataSize = 8;
		break;
		
		case SPI_DATA_SIZE_9:
			spi->CR2 |= (8U<<SPI_CR2_DS_Pos);
			handle->DataSize = 9;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_10:
			spi->CR2 |= (9U<<SPI_CR2_DS_Pos);
			handle->DataSize = 10;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_11:
			spi->CR2 |= (10U<<SPI_CR2_DS_Pos);
			handle->DataSize = 11;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_12:
			spi->CR2 |= (11U<<SPI_CR2_DS_Pos);
			handle->DataSize = 12;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_13:
			spi->CR2 |= (12U<<SPI_CR2_DS_Pos);
			handle->DataSize = 13;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_14:
			spi->CR2 |= (13U<<SPI_CR2_DS_Pos);
			handle->DataSize = 14;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_15:
			spi->CR2 |= (14U<<SPI_CR2_DS_Pos);
			handle->DataSize = 15;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_16:
			spi->CR2 |= (15U<<SPI_CR2_DS_Pos);
			handle->DataSize = 16;
			handle->bTransferWord = TRUE;
		break;
		
		default:
			return SPIM_E_INVALID_DATASIZE;
  }
  if( handle->DataSize > 8 )
  {
	  spi->CR2 &= ~SPI_CR2_FRXTH;
  }
  else
  {
	  spi->CR2 |= SPI_CR2_FRXTH;
  }
  
  NVIC_EnableIRQ( irq );
  
  
  return SPIM_STS_OK;


}


void
SpimLinkDMA(
  void            *pHandle,
  void      *pDmaTxHandle,
  void      *pDmaRxHandle
  )
{
#ifdef _DMA_EN
  PSPIM_HANDLE handle = (PSPIM_HANDLE)pHandle;
  SPI_TypeDef *spi   = (SPI_TypeDef *)handle->pSpi;
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
	PSPIM_HANDLE handle =(PSPIM_HANDLE)pHandle;
  SPI_TypeDef *spi = (SPI_TypeDef*)handle->pSpi;

  ASSERT( 0 != pHandle );
  
  spi->CR1 &= ~SPI_CR1_SPE;
  spi->CR2 &= ~SPI_CR2_DS;
  
  switch( DATA_SIZE )
  {
		case SPI_DATA_SIZE_4:
			spi->CR2 |= (3U<<SPI_CR2_DS_Pos);
			handle-> DataSize = 4;
		break;
		
		case SPI_DATA_SIZE_5:
			spi->CR2 |= (4U<<SPI_CR2_DS_Pos);
			handle->DataSize = 5;
		break;
		
		case SPI_DATA_SIZE_6:
			spi->CR2 |= (5U<<SPI_CR2_DS_Pos);
			handle->DataSize = 6;
		break;
		
		case SPI_DATA_SIZE_7:
			spi->CR2 |= (6U<<SPI_CR2_DS_Pos);
			handle->DataSize = 7;
		break;
		
		case SPI_DATA_SIZE_8:
			spi->CR2 |= (7U<<SPI_CR2_DS_Pos);
			handle->DataSize = 8;
		break;
		
		case SPI_DATA_SIZE_9:
			spi->CR2 |= (8U<<SPI_CR2_DS_Pos);
			handle->DataSize = 9;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_10:
			spi->CR2 |= (9U<<SPI_CR2_DS_Pos);
			handle->DataSize = 10;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_11:
			spi->CR2 |= (10U<<SPI_CR2_DS_Pos);
			handle->DataSize = 11;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_12:
			spi->CR2 |= (11U<<SPI_CR2_DS_Pos);
			handle->DataSize = 12;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_13:
			spi->CR2 |= (12U<<SPI_CR2_DS_Pos);
			handle->DataSize = 13;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_14:
			spi->CR2 |= (13U<<SPI_CR2_DS_Pos);
			handle->DataSize = 14;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_15:
			spi->CR2 |= (14U<<SPI_CR2_DS_Pos);
			handle->DataSize = 15;
			handle->bTransferWord = TRUE;
		break;
		
		case SPI_DATA_SIZE_16:
			spi->CR2 |= (15U<<SPI_CR2_DS_Pos);
			handle->DataSize = 16;
			handle->bTransferWord = TRUE;
		break;
		
		default:
			return SPIM_E_INVALID_DATASIZE;
  }
 return SPIM_STS_OK;

}


int SpimSetSpeed( void *pHandle, int nSpeed )
{
  /********************************************************
  * To do: 
  * This function's implementation can be skipped at beginning.
  ********************************************************/

	uint32_t clock;
  int tmp;
  int prescale;
  int div;
  
  ASSERT( 0 != pHandle );
  ASSERT( 0 != nSpeed );
  
  PSPIM_HANDLE handle =(PSPIM_HANDLE)pHandle;
  SPI_TypeDef *spi = (SPI_TypeDef*)handle->pSpi;
  
  if( 1 == handle->Apb )
  {
	  switch( RCC->CFGR & RCC_CFGR_PPRE1)
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
	  
  }
  else if( 2 == handle->Apb)
  {
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
			
			case RCC_CFGR_PPRE2_DIV16:
				clock = SystemCoreClock>>4U;
			break;
			
			default:
			break;
	  }
	  
	  
  }
   else 
  {
	  ASSERT( FALSE );
  }
  
  prescale = clock / nSpeed;
  div =0;
  do
  {
	  prescale /= 2;
	  div++;
  }while( 0 != prescale );
  
  spi->CR1 &= ~SPI_CR1_SPE;
  tmp = spi->CR1;
  tmp &= ~SPI_CR1_BR;
  tmp |=((div-1)<<SPI_CR1_BR_Pos);
  spi->CR1 = tmp;
  
  spi->CR1 |= SPI_CR1_SPE;
  
  clock = clock/ pow(2.0,div);
  
  return clock;

}


void
SpimAddCallbackTransferDone(
  void         *phandle,
  SPIM_CB_TRFR_DONE   *pfDone )
{
  /********************************************************
  * To do: 
  ********************************************************/
  PSPIM_HANDLE handle = (PSPIM_HANDLE)phandle;
  
  ASSERT( 0 != phandle);
  ASSERT( 0 != pfDone);
  
  handle->pfDone = pfDone;
}


void
SpimTransfer(
  void     *phandle,
  void const   *pTxBuf,
  void     *pRxBuf,
  int     nSize
  )
{
  PSPIM_HANDLE  handle   = (PSPIM_HANDLE)phandle;
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
	handle->nTxCount++;
	
	spi->CR2 |= SPI_CR2_RXNEIE | SPI_CR2_TXEIE;
	spi->CR1 |= SPI_CR1_SPE;
}


/*****************************************************************************
 Callback functions
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
  PSPIM_HANDLE  handle   = (PSPIM_HANDLE)pHandle;
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
  SPI_TypeDef *spi = pHandle->pSpi;
  int status = spi->SR;
  uint8_t data;
  
  ASSERT( 0 != pHandle);
  if( 0 == (status & SPI_SR_BSY) )
  {
	  if( 0 != (status & SPI_SR_RXNE) )
	  {
		  data = spi->DR;
		  
		  if( FALSE == pHandle->bTransferWord)
		  {
			  if( 0 != pHandle->pRxBuf)
			  {
				  pHandle->pRxBuf[pHandle->nRxCount] = data;
			  }
		  }
		  else
		  {
			  if( 0 != pHandle->pRxWordBuf)
			  {
				  pHandle->pRxWordBuf[pHandle->nRxCount] = data;
			  }
		  }
		  
		  pHandle->nRxCount++;
		  
		  if(pHandle->nRxCount >= pHandle->nSize)
		  {
			  spi->CR2 &= ~SPI_CR2_RXNEIE;
			  spi->CR1 &= ~SPI_CR1_SPE;
			  
			  if(0 != pHandle->pfDone)
			  {
				  pHandle->pfDone();
			  }
		  }
	  }
	  
	  if( 0 != (status & SPI_SR_TXE))
	  {
		  if( pHandle->nTxCount >= pHandle->nSize)
		  {
			  spi->CR2 &= ~SPI_CR2_TXEIE;
		  }
		  else
		  {
			  if( FALSE == pHandle->bTransferWord)
			  {
                              if(0 != pHandle->pRxBuf)
                              {
				  SPI_CAST_8BIT(&spi->DR)= pHandle->pTxBuf[pHandle->nTxCount];
                              }
			  }
			  else
			  {
                                  if( 0 != pHandle->pRxWordBuf)
                                  {
				  spi->DR = pHandle->pTxWordBuf[pHandle->nTxCount];
                                  }
			  }
			  pHandle->nTxCount++;
		  }
	  }
  }
}


/*****************************************************************************
 Interrupt
******************************************************************************/
void SPI1_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/
  ASSERT( 0 != g_pSpiIrqhandles[0] );
  
  SPI_Handler( g_pSpiIrqhandles[0] );
}


void SPI2_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/
  ASSERT( 0 != g_pSpiIrqhandles[1] );
  
  SPI_Handler( g_pSpiIrqhandles[1] );
}


void SPI3_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/
  ASSERT( 0 != g_pSpiIrqhandles[2] );
  
  SPI_Handler( g_pSpiIrqhandles[2] );
}


void SPI4_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/
  ASSERT( 0 != g_pSpiIrqhandles[3] );
  
  SPI_Handler( g_pSpiIrqhandles[3] );
}


void SPI5_IRQHandler( void )
{
  /********************************************************
  * To do: 
  ********************************************************/
  ASSERT( 0 != g_pSpiIrqhandles[4] );
  
  SPI_Handler( g_pSpiIrqhandles[4] );
}

