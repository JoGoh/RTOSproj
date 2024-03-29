/******************************************************************************
 @filename      Serial.c

 @project      
 
 @description    
 
 @version       1.0.0

 @revision    
******************************************************************************/

#include "Common.h"
#include "Dma.h"
#include "Serial.h"


/******************************************************************************
 Define
******************************************************************************/


/******************************************************************************
 Global variables
******************************************************************************/


/******************************************************************************
 Typedef
******************************************************************************/


/******************************************************************************
 Local variables
******************************************************************************/


/*****************************************************************************
 Callback functions
*****************************************************************************/
#ifdef __UART_DMA
static void serial_cbDmaTxHalf( void *pContext );
static void serial_cbDmaRxHalf( void *pContext );
static void serial_cbDmaTxComp( void *pContext );
static void serial_cbDmaRxComp( void *pContext );
static void serial_cbDmaTxError( void *pContext );
static void serial_cbDmaRxError( void *pContext );
#endif


/*****************************************************************************
 Local function
*****************************************************************************/
static int  buf_Pull( PUART_FIFO pFifo, char *pData );
static int  buf_Push( PUART_FIFO pFifo, char data );


/*****************************************************************************
 Implementations
*****************************************************************************/
int
SerialInit(
  PUART_HANDLE         pHandle,
  UART_DRIVER const   *pDriver,
  uint8_t             nPort,
  uint32_t            nBaud
  )
{
  int res = UART_STS_NO_PORT;
  
  ASSERT( 0 != pHandle );
  
  memset( pHandle, 0, sizeof( UART_HANDLE ) );
    
  pHandle->pDriver = pDriver;
  res = pDriver->pfInit( pHandle, nPort, nBaud );
  
  return res;
}


void
SerialBuffer(
  PUART_HANDLE    pHandle,
  char         *pTxBuf,
  uint32_t       nTxSize,
  char         *pRxBuf,
  uint32_t       nRxSize
  )
{
  ASSERT( 0 != pHandle );

  pHandle->TxFifo.nSize   = nTxSize;
  pHandle->TxFifo.pBuf   = pTxBuf;
  pHandle->RxFifo.nSize   = nRxSize;
  pHandle->RxFifo.pBuf   = pRxBuf;
}


int  
SerialBaudrate(
  PUART_HANDLE  pHandle,
  uint32_t    nBaud
  )
{
  ASSERT( 0 != pHandle );
  
  return pHandle->pDriver->pfBaudrate( pHandle, nBaud );
}


int
SerialConfig(
  UART_HANDLE const  *pHandle, 
  UART_CFG       Databit, 
  UART_CFG       Parity,
  UART_CFG       Stopbit )
{
  ASSERT( 0 != pHandle );
  
  return pHandle->pDriver->pfConfig(
                                    pHandle,
                                    Databit,
                                    Parity,
                                    Stopbit );
}


void 
SerialAddCallback(
  PUART_HANDLE  pHandle,
  UART_CB_ONTX  *pfOnTx,
  UART_CB_ONRX  *pfOnRx
  )
{
  ASSERT( 0 != pHandle );
  
  if( 0 != pfOnTx )
  {
    pHandle->pfOnTx = pfOnTx;
  }

  if( 0 != pfOnRx )
  {
    pHandle->pfOnRx = pfOnRx;
  }
 
}


int
SerialWrite(
  PUART_HANDLE   pHandle,
  char           Data
  )
{
  int    res = 0;
  char  tmp;
  
  ASSERT( 0 != pHandle );

  if( 0 != pHandle->pDmaTx )
  {
    /* NOTE: 
     This function only use for Interrupt driven, not for DMA use */
    return UART_STS_MISMATCH_MODE;
  }
  
  /* lock interrupt to prevent data contention */
  pHandle->pDriver->pfLock( pHandle );
  
  /* Check UART is ready to transmit */
  if( 0 == pHandle->pDriver->pfIsTxReady( pHandle ) )
  {
    /* Hardware buffer full, we push into software ring buffer */
    res = buf_Push( &pHandle->TxFifo, Data );
    
    /* Unlock the interrupt, lets it run */
    pHandle->pDriver->pfUnlock( pHandle );

    if( 0 == res )
    {
      /* s/w FIFO full */
      return UART_STS_BUF_OVER;
    }
  }
  else
  {
    if( pHandle->TxFifo.nHead != pHandle->TxFifo.nTail )
    {
      /* Hardware buffer full, we push into software ring buffer */
      res = buf_Push( &pHandle->TxFifo, Data );
      
      if( 1 == buf_Pull( &pHandle->TxFifo, &tmp ) )
      {
        /* Unlock the interrupt, lets it run */
        pHandle->pDriver->pfUnlock( pHandle );
        
        /* UART is empty, ready to write the data */
        pHandle->pDriver->pfWrite( pHandle, tmp );
      }
      else
      {    
        /* Unlock the interrupt, lets it run */
        pHandle->pDriver->pfUnlock( pHandle );
      }
    }
    else
    {
      /* Unlock the interrupt, lets it run */
      pHandle->pDriver->pfUnlock( pHandle );
      
      /* UART is empty, ready to write the data */
      pHandle->pDriver->pfWrite( pHandle, Data );
    }
  }
  
  return UART_STS_OK;
}


int
SerialWriteEx(
  PUART_HANDLE   pHandle,
  void const    *pData,
  int            nSize
  )
{
  int res = 0;
  char const *data = (char const *)pData;

  
  ASSERT( 0 != pHandle );


  while( 0 == pHandle->pDriver->pfIsTxReady( pHandle ) );
  
  /* cap at maximum size FIFO available */
  res = MIN( pHandle->TxFifo.nSize, nSize );

  /* Move into FIFO */
  memcpy( pHandle->TxFifo.pBuf, pData, res );
  /********************************************************
  * To do: update pHandle's TxFifo.nTail and TxFifo.nHead 
  ********************************************************/

  if (nSize >= res) 
  {
     pHandle->TxFifo.nHead = res;
     pHandle->TxFifo.nTail++;
     //pHandle->TxFifo.nTail = 1;
  }

  /* UART is empty, ready to write the data */
  pHandle->pDriver->pfWrite( pHandle, *data );

  return res;
}


char SerialRead( PUART_HANDLE pHandle )
{
  char  data = 0;
  int   res  = 0;
  
  ASSERT( 0 != pHandle );
  
  if( 0 != pHandle->pDmaRx )
  {
    /* NOTE: 
    This function only use for Interrupt driven, not for DMA use */
    return UART_STS_MISMATCH_MODE;
  }

  /* atomic the process */
  pHandle->pDriver->pfLock( pHandle );

  /********************************************************
  * To do: use buf_Pull to read data
  ********************************************************/

    res = buf_Pull(&pHandle->RxFifo, &data);


  pHandle->pDriver->pfUnlock( pHandle );
  
  /* ring buffer is empty will return 0 */
  return ((0 == res)? 0 : data);
}


/********************************************************
* No need to be implemented now!
********************************************************/
int SerialReadEx( PUART_HANDLE pHandle, char *pBuf, int nSize )
{
  ASSERT( 0 != pHandle );
}


/********************************************************
* No need to be implemented now!
********************************************************/
void SerialTxEmpty( UART_HANDLE *pHandle )
{
  ASSERT( 0 != pHandle );
  
}


/********************************************************
* No need to be implemented now!
********************************************************/
void SerialRxEmpty( UART_HANDLE *pHandle )
{
  ASSERT( 0 != pHandle );
  
}


/********************************************************
* No need to be implemented now!
********************************************************/
BOOL SerialIsTxEmpty( UART_HANDLE *pHandle )
{
  BOOL res;
  ASSERT( 0 != pHandle );
  
  return res;
}


BOOL SerialIsTxReady( UART_HANDLE *pHandle )
{
  int  cnt   = 0;
  int tail   = 0;
  
  ASSERT( 0 != pHandle );
  
  pHandle->pDriver->pfLock( pHandle );
  cnt = pHandle->TxFifo.nHead + 1U;
  if( cnt >= pHandle->TxFifo.nSize )
  {
    /* point back to the top of the FIFO ring buffer */
    cnt = 0;
  }
  tail = pHandle->TxFifo.nTail;
  pHandle->pDriver->pfUnlock( pHandle );
  
  /* FIFO full will return 0 */
  return ((cnt == tail)? FALSE : TRUE);
}


BOOL SerialIsRxReady( UART_HANDLE const *pHandle )
{
  ASSERT( 0 != pHandle );
  
  return ((pHandle->RxFifo.nHead != pHandle->RxFifo.nTail)? TRUE : FALSE);
}



/*****************************************************************************
 Callbacks functions
*****************************************************************************/



/*****************************************************************************
 IRQ handler
*****************************************************************************/
void UartIsrTx( PUART_HANDLE pHandle )
{
  char data;
  
  ASSERT( 0 != pHandle );
  
  if( 1 == buf_Pull( &pHandle->TxFifo, &data ) )
  {
    /* Send it now */
    pHandle->pDriver->pfWrite( pHandle, data );
  }
  else
  {
    /* Nothing else to Tx, disable IRQ */
    pHandle->pDriver->pfTxEnd( pHandle );

    if( 0 != pHandle->pfOnTx )
    {
      pHandle->pfOnTx();
    }
  }
}


void UartIsrRx( PUART_HANDLE pHandle )
{
  char data;
  
  ASSERT( 0 != pHandle );
  
  data = pHandle->pDriver->pfRead( pHandle );

  if( 0 != pHandle->pReadBuf )
  {
    if( 0 != pHandle->nReadbyte )
    {
      pHandle->nReadbyte--;
      *pHandle->pReadBuf++ = data;

      if( 0 == pHandle->nReadbyte )
      {
        if( 0 != pHandle->pfOnRx )
        {
          pHandle->pfOnRx();
        }

        pHandle->pReadBuf = 0;
      }
    }
  }
  else
  {
    if( 0 == buf_Push( &pHandle->RxFifo, data ) )
    {
      pHandle->nError |= UART_ERR_OVERFLOW;
      ASSERT( FALSE );
    }
    else
    {
      if( 0 != pHandle->pfOnRx )
      {
        pHandle->pfOnRx();
      }
    }
  }
}


/*****************************************************************************
 Local helpers
*****************************************************************************/

/* software FIFO access */
static int buf_Push( PUART_FIFO  pFifo, char Data )
{
  int  hd;

  ASSERT( 0 != pFifo );
  ASSERT( 0 != pFifo->pBuf );

  if( 0 == pFifo->nSize )
  {
      return 0;
  }

  /********************************************************
  * To do: store Data to pFifo->pBuf
  * pFifo->nHead needs to be maintained.
  ********************************************************/
   hd = pFifo->nHead+1;

   if (hd >=pFifo->nSize)
   {
        hd = 0;
   }

   if (hd == pFifo->nTail)
   {
        return 0;  // fifo is full
   }

    pFifo->pBuf[pFifo->nHead] = Data;
    pFifo->nHead =hd;

  return 1;
}


static int buf_Pull( PUART_FIFO  pFifo, char *pData)
{
  ASSERT( 0 != pFifo );
  ASSERT( 0 != pData );

  ASSERT( 0 != pFifo->pBuf );

  if( 0 == pFifo->nSize )
  {
      return 0;
  }
  
  if( pFifo->nHead == pFifo->nTail )
  {
    return 0;              /* FIFO empty */
  }

  /********************************************************
  * To do: collect data from pFifo->pBuf and store in *pData.
  * pFifo->nTail needs to be maintained.
  ********************************************************/
*pData = pFifo->pBuf[pFifo->nTail++];

if (pFifo->nTail == pFifo->nSize)
{
       pFifo->nTail = 0; // FIFO is empty
}
    
  return 1;
}


















