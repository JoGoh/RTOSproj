/*****************************************************************************
 @Project  : SEP250 2020 Spring
 @File     : ips_Template.c
 @Details  : STM32F722XX Indoor Positioning System              
 @Author   : Liang Tang
 @Hardware : STM32F722
 
 --------------------------------------------------------------------------
 @Revision  :
  Ver    Author      Date       Changes
 --------------------------------------------------------------------------
   1.0  lcgan     2018-08-29   Initial Release
   1.1  Liang     2019-01-25   Remove some key parts and students are required
                               to fill.
******************************************************************************/

#include <Common.h>
#include "Hal.h"
#include "BSP.h"
#include "Serial.h"
#include "spim.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "ips.h"
/* #include "matrix.h" */


/*****************************************************************************
 Macro
******************************************************************************/


/*****************************************************************************
 Define
******************************************************************************/
/* Default antenna delay values for 64 MHz PRF. See NOTE 2 below. */
#define TX_ANT_DLY          16436
#define RX_ANT_DLY          16436

/* Length of the common part of the message 
(up to and including the function code, see NOTE 3 below). */
#define ALL_MSG_COMMON_LEN      10

/* UWB microsecond (uus) to device time unit (dtu, around 15.65 ps) conversion factor.
 * 1 uus = 512 / 499.2 ?s and 1 ?s = 499.2 * 128 dtu. */
#define UUS_TO_DWT_TIME        65536

/* Delay between frames, in UWB microseconds. See NOTE 1 below. */
#define POLL_RX_TO_RESP_TX_DLY_UUS  500

/* Delay between frames, in UWB microseconds. See NOTE 1 below. */
#define POLL_TX_TO_RESP_RX_DLY_UUS   140

/* Speed of light in air, in metres per second. */
#define SPEED_OF_LIGHT         299702547


/* Buffer to store received response message */
#define RX_BUF_LEN           20

#define AVG_SAMPLE          4.0f


#define GROUP_ID1          'G'
#define GROUP_ID2          'N'

#define DEFAULT_IRQ_TIMEOUT_MS    5


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Const Variables
******************************************************************************/
/* Default communication configuration. We use here EVK1000's mode 4. See NOTE 1 below. */
static dwt_config_t UWB_CFG = 
{
    3,               /* Channel number. */
    DWT_PRF_64M,     /* Pulse repetition frequency. */
    DWT_PLEN_128,    /* Preamble length. Used in TX only. */
    DWT_PAC8,        /* Preamble acquisition chunk size. Used in RX only. */
    9,               /* TX preamble code. Used in TX only. */
    9,               /* RX preamble code. Used in RX only. */
    0,               /* 0 to use standard SFD, 1 to use non-standard SFD. */
    DWT_BR_6M8,      /* Data rate. */
    DWT_PHRMODE_STD, /* PHY header mode. */
    (129 + 8 - 8)    /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};



/*****************************************************************************
 Local Variables
******************************************************************************/
static PSPIM_HANDLE     g_pSpimHandle;
static volatile BOOL    g_bSpiDone = FALSE;

static uint8_t          g_nFrameSeqNum = 0;

static uint8_t          g_aSpiTxBuf[24];
static uint8_t          g_aSpiRxBuf[24];
static uint8_t          g_aUwbRxBuf[RX_BUF_LEN];

static  double          g_dMatA[2][2] = { 0 };
static  double          g_dMatInvA[2][2] = { 0 };
static  double          g_dMatB[2] = { 0 };

static double           g_dIpsCoordinate[2] = { 0 };

static int              g_nBc   = 0;
static int              g_nAvgSample = 0;

static double           g_dAccX    = 0.0;
static double           g_dAccY    = 0.0;

static double           g_dAvgX    = 0.0;
static double           g_dAvgY    = 0.0;

static double           g_dIpsRef1[2] = { 0.0, 0.0 };
static double           g_dIpsRef2[2] = { 0, 820.0 };
static double           g_dIpsRef3[2] = { 600.0, 820.0 };
//static double         g_dIpsRef3[2] = { 360.0, 750.0 };
static double           g_dDistance[3] = { 0.0, 0.0, 0.0 };

static volatile BOOL    g_bRxOK = FALSE;
static volatile BOOL    g_bSts = FALSE;

static volatile int     g_nTimeoutMs = 0;
static int              g_nTimeoutMsConst = DEFAULT_IRQ_TIMEOUT_MS;

static UWB_TX_MSG       g_TxMsg;
static UWB_RX_MSG       g_RespMsg;
static DWT_HANDLE       g_UWBHandle;

static uint16_t         g_aPanId[3] = { 0x4343, 0x4343, 0x4343 };
static uint16_t         g_aDestAddr[3] = { 0x3333, 0xef12, 0x3456 };
static uint8_t          g_aSeqNum[3] = { 0, 0, 0 };

/*****************************************************************************
 Local Functions
******************************************************************************/
static void ips_cbOnSpiDone( void );


/*****************************************************************************
 Callback Functions
******************************************************************************/


/*****************************************************************************
 Implementation
******************************************************************************/
IPS_STS IpsInit( SPIM_HANDLE *pSpimHandle )
{
  int speed;

  g_aSeqNum[0] = 0U;
  g_aSeqNum[1] = 0U;
  g_aSeqNum[2] = 0U;

  ASSERT( 0 != pSpimHandle );

  g_pSpimHandle = pSpimHandle;

  /* Add a SPI callback */
  SpimAddCallbackTransferDone( pSpimHandle, ips_cbOnSpiDone );

  /********************************************************
  * To do: ...
  * Set g_TxMsg struct
  ********************************************************/
  g_TxMsg.b.FrameCtrl    = 0x8841;
  g_TxMsg.b.PANID        = ;
  g_TxMsg.b.Code         = 0xE0;
  g_TxMsg.b.SrcAddr      = ;
  g_TxMsg.b.Resvd[0]     = 0;
  g_TxMsg.b.Resvd[1]     = 0;
  g_TxMsg.b.DestAddr     = ;
  g_TxMsg.b.nSequenceNum = 0;


  /* Reset UWB before any configuration */
  UWB_RESET_ON();

  DWT_SoftReset( &g_UWBHandle );

  if( DWT_Init( &g_UWBHandle, DWT_LOADUCODE) == DWT_ERROR )
  {
    TRACE( "INIT FAILED\r\n" );
    ASSERT( FALSE );

    return IPS_UWB_INIT_ERROR;
  }
  
  speed = SpimSetSpeed( pSpimHandle, 10000000 );
  TRACE( "SPI Speed: %d\r\n", speed );

  DWT_SetLEDs( 3 );

  /* Configure DW1000. */
  DWT_Config( &g_UWBHandle, &UWB_CFG );

  /********************************************************
  * Set PAN ID and Address
  ********************************************************/
  DWT_SetPanID( g_TxMsg.b.PANID );
  DWT_SetAddr16( g_TxMsg.b.DestAddr );


  /* Enable filter so it will not received other groups message */
  DWT_EnableFrameFilter( &g_UWBHandle, DWT_FF_DATA_EN );

  DWT_EnableInterrupt( SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_ERR, 1 );

  /* Set expected response's delay and timeout.
  * only handles one incoming frame with always the same delay and timeout,
  those values can be set here once for all. */
  dwt_setrxaftertxdelay( POLL_TX_TO_RESP_RX_DLY_UUS );

  /* Apply default antenna delay value.*/
  DWT_SetRxAntennaDelay( RX_ANT_DLY );
  DWT_SetTxAntennaDelay( TX_ANT_DLY );



  return IPS_SUCCESS;
}


void IPSAuthID( int nBeacon, uint8_t *pID )
{
  /********************************************************
  * To do: ...
  * Can be implemented later, to dynamically change PAN ID
  * Set PAN ID
  ********************************************************/

}


void IPSSetAddr( int nBeacon, uint8_t *pAddr )
{
  /********************************************************
  * To do: ...
  * Can be implemented later, to dynamically change destination 
  * address
  * Set Address
  ********************************************************/


}






void IPSystemSetIRQTimeout( int nTimeoutMs )
{
  g_nTimeoutMsConst = nTimeoutMs;
}


void IPSSysTimeout1msTimer( void )
{
  if( 0 != g_nTimeoutMs )
  {
    g_nTimeoutMs--;
  }
}




  
IPS_STS IpsTimer( void )
{
  IPS_STS     res              = IPS_SUCCESS;
  UWB_TX_MSG  *txmsg           = 0U;
  UWB_RX_MSG  *respmsg         = 0U;
  uint32_t    stsReg           = 0U;
  uint32      framelen;        
  uint32      poll_tx_ts       = 0U;
  uint32      resp_rx_ts       = 0U;
  uint32      poll_rx_ts       = 0U;
  uint32      resp_tx_ts       = 0U;
  int32_t     rtd_init         = 0;
  int32_t     rtd_resp         = 0;
  float       clockOffsetRatio = 0.0;
  double      tof;
  int         timeout;
  uint8_t     cnt              = 0;
  int         ret;
  uint32_t    status           = 0;
  double      dist;
  int         retry            = 0;
  BOOL        btx              = 0;


  /********************************************************
  * To do: ...
  * Prepare the transmission data, PAN ID, address, etc
  ********************************************************/
  g_TxMsg.b.PANID = ;
  g_TxMsg.b.DestAddr = ;
  g_TxMsg.b.nSequenceNum = ;


  DWT_SetAddr16( g_TxMsg.b.DestAddr );
  DWT_WriteTxData( 12, g_TxMsg.Data, 0 );
  DWT_WriteTxFrameCtrl( &g_UWBHandle, 12, 0, 1 );


  /********************************************************
  * To do: ...
  * Check the receiving status by reading SYS_STATUS_ID 
  * register.
  * Call the provided DWT_StartTx() function, and check its
  * return status: if DWT_SUCCESS: wait the receiving by 
  * checking g_bSts
  * Collect the received info
  ********************************************************/





  return res;
}



decaIrqStatus_t decamutexon( void )
{
  /* "Mutex" functions */
  /* Disable the DW1000 interrupt if it is on */
  return 0;
}


void decamutexoff ( decaIrqStatus_t s )
{
  /* "Mutex" functions */
  UNUSE( s );
}



int
readfromspi(
  uint16       headerLength,
  const uint8   *headerBuffer,
  uint32       readlength,
  uint8      *readBuffer
  )
{
  ASSERT( 0 != g_pSpimHandle );

  /********************************************************
  * To do: ...
  * UWB SPI READ by calling SpimTransfer()
  ********************************************************/


  
  return 0;
}

int
writetospi(
  uint16      headerLength,
  const uint8 *headerBuffer,
  uint32      bodylength,
  const uint8 *bodyBuffer
  )
{
  ASSERT( 0 != headerLength );
  ASSERT( 0 != headerBuffer );
  ASSERT( 0 != bodylength );
  ASSERT( 0 != bodyBuffer );
  ASSERT( 0 != g_pSpimHandle );

  /********************************************************
  * To do: ...
  * UWB SPI Write by calling SpimTransfer()
  ********************************************************/


  
  return 0;
}


/*****************************************************************************
 Callback functions
******************************************************************************/
static void ips_cbOnSpiDone( void )
{
  g_bSpiDone = TRUE;
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void EXTI3_UWB_INT_IRQHandler( uint32_t Status )
{
  g_bSts = TRUE;

  UNUSE( Status );
}
