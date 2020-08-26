/*****************************************************************************
 @Project	: 
 @File 		: main.c
 @Details  	: Main entry               
 @Author	: lcgan
 @Hardware	: STM32
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "IRQ.h"
#include "BSP.h"

#include "spim.h"
#include "deca_device_api.h"
#include "deca_regs.h"



/*****************************************************************************
 Define
******************************************************************************/
#define EVT_UWB_ON_IRQ      0x00000001U


/* Default antenna delay values for 64 MHz PRF. See NOTE 2 below. */
#define TX_ANT_DLY					16436
#define RX_ANT_DLY					16436

/* Length of the common part of the message 
(up to and including the function code, see NOTE 3 below). */
#define ALL_MSG_COMMON_LEN			10

/* UWB microsecond (uus) to device time unit (dtu, around 15.65 ps) conversion factor.
 * 1 uus = 512 / 499.2 ?s and 1 ?s = 499.2 * 128 dtu. */
#define UUS_TO_DWT_TIME				65536

/* Delay between frames, in UWB microseconds. See NOTE 1 below. */
#define POLL_RX_TO_RESP_TX_DLY_UUS	500

#define UWB_TASK_STACK_SIZE     200


/*****************************************************************************
 Type definition
******************************************************************************/
#pragma pack(push,1)
typedef union _tagUWB_RX_MSG
{
	uint8_t Data[12];

	struct
	{
		uint16_t FrameCtrl;
		uint8_t	nSequenceNum;
		uint16_t PANID;
		uint16_t DestAddr;
		uint16_t SrcAddr;
		uint8_t Code;
		uint8_t Resvd[2];
	}b;
}UWB_RX_MSG, *PUWB_RX_MSG;


typedef union _tagUWB_TX_MSG
{
	uint8_t Data[20];

	struct
	{
		uint16_t FrameCtrl;
		uint8_t	nSequenceNum;
		uint16_t PANID;
		uint16_t DestAddr;
		uint16_t SrcAddr;
		uint8_t Code;
        uint32_t RxTimestamp;
		uint32_t TxTimestamp;
        uint16_t nCrc;
	}b;
}UWB_TX_MSG, *PUWB_TX_MSG;
#pragma pack(pop)


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Const Local Variables
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


static uint16_t const BEACON_ADDR[4] =
{
	0x4555,
	0x4556,
	0x4557,
	0x7890
};


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile uint8_t		g_nCount = 0;

static SPIM_HANDLE 			g_SpimHandle;
static uint8_t 				g_aSpiTxBuf[64];
static uint8_t 				g_aSpiRxBuf[64];
static volatile BOOL 		g_bSpiDone = FALSE;

static volatile int			g_nTimeoutMs		= 0;
static volatile  int        g_nStatusTimeout	= 100;

static uint64_t				g_nPollRxTimestamp = 0U;
static uint64_t				g_nRespTxTimestamp = 0U;
static UWB_TX_MSG           g_RespMsg;
static UWB_RX_MSG			g_RxMsg;

static DWT_HANDLE			g_UWBHandle;

static volatile BOOL        g_bUWBReady = FALSE;


/*****************************************************************************
 Local function Prototype
******************************************************************************/
static void main_SpimInit( void );
static uint64_t main_GetRxTimestamp64( void );


/*****************************************************************************
 Callback function Prototype
******************************************************************************/
static void main_cbOnSpiDone( void );
static void main_RunBeacon( void );


/*****************************************************************************
 Implementation 
******************************************************************************/
int main( void )
{
	BSPInit();
	
    TRACE( "System Clock Speed %d Hz\r\n", SystemCoreClock );

	memset( &g_RespMsg, 0, sizeof(g_RespMsg) );


    IRQInit();

    main_RunBeacon();

	return 0;

}


static void main_RunBeacon( void )
{
    uint8_t		cnt = 0;
    BOOL        toggle	= 0;
    int			ret;
    int			speed;
    static uint32_t    status = 0;
	uint32		framelen;
	uint32		resp_tx_time;

	main_SpimInit();

	UWB_RESET_ON();

    DWT_SoftReset( &g_UWBHandle );

	g_RespMsg.b.FrameCtrl = 0x8841;
    g_RespMsg.b.PANID = 0x4342;
    g_RespMsg.b.Code = 0xE1;
    g_RespMsg.b.SrcAddr = 0x3350;
    g_RespMsg.b.DestAddr = BEACON_ADDR[2];
    g_RespMsg.b.nSequenceNum = 0;

#if 1	
	if( DWT_Init( &g_UWBHandle, DWT_LOADUCODE) == DWT_ERROR )
    {
		TRACE( "INIT FAILED\r\n" );
		ASSERT( FALSE );
    }
#endif

	speed = SpimSetSpeed( &g_SpimHandle, 30000000 );
	TRACE( "SPI Speed: %d\r\n", speed );

    DWT_SetLEDs( 3 );
	
	/* Configure DW1000. */
    DWT_Config( &g_UWBHandle, &UWB_CFG );

	
	/* Enable filter so it will not received other groups message */
	DWT_SetPanID( g_RespMsg.b.PANID );
    DWT_SetAddr16( g_RespMsg.b.DestAddr );

    DWT_EnableFrameFilter( &g_UWBHandle, DWT_FF_DATA_EN );

    DWT_EnableInterrupt( SYS_STATUS_RXFCG | SYS_MASK_MTXFRS | SYS_STATUS_ALL_RX_ERR, 1 );

    /* Apply default antenna delay value.*/
    DWT_SetRxAntennaDelay( RX_ANT_DLY );
    DWT_SetTxAntennaDelay( TX_ANT_DLY );

    /* Activate reception immediately. */
    DWT_EnableRx( &g_UWBHandle, DWT_START_RX_IMMEDIATE );

	for(;;)
	{
		if( 0 == g_bUWBReady )
		{
            if( 0 == g_nTimeoutMs )
            {
                g_nTimeoutMs = 1000;

                DWT_ForceTrxOff( &g_UWBHandle );
                DWT_ResetRx();

                DWT_EnableRx( &g_UWBHandle, DWT_START_RX_IMMEDIATE );

                TRACE( "Event Timeout\r\n" );
            }

			continue;
		}
		 
        g_bUWBReady = FALSE;
        status = DWT_Read32BitReg( SYS_STATUS_ID );

		if( 0 == (status&SYS_STATUS_IRQS) )
		{
			continue;
		}

		if( 0 != (status & (SYS_STATUS_RXFCG)) )
		{
			/* Clear good RX frame event in the DW1000 status register. */
			DWT_Write32BitReg( SYS_STATUS_ID, SYS_STATUS_RXFCG );

            /* A frame has been received, read it into the local buffer. */
            framelen = DWT_Read32BitReg(RX_FINFO_ID) & RX_FINFO_RXFL_MASK_1023;
            if( framelen <= RX_BUFFER_LEN )
            {
                DWT_ReadRxData( g_RxMsg.Data, 12, 0 );
                toggle = !toggle;
				LED_SET( toggle );
            }

			if( 12 == framelen )
			{
				/* Assume msg matched */
				/* Retrieve poll reception timestamp. */
				g_nPollRxTimestamp = main_GetRxTimestamp64();

				/* Compute final message transmission time. See NOTE 7 below. */
				resp_tx_time = (g_nPollRxTimestamp + (POLL_RX_TO_RESP_TX_DLY_UUS * UUS_TO_DWT_TIME)) >> 8;
				DWT_SetDelayedTrxTime( resp_tx_time );

				/* Response TX timestamp is the transmission time we programmed plus the antenna delay. */
				g_nRespTxTimestamp = (((uint64_t)(resp_tx_time & 0xFFFFFFFEUL))<<8) + TX_ANT_DLY;
				
				/* Write all timestamps in the final message. */
				g_RespMsg.b.RxTimestamp = (uint32_t)(g_nPollRxTimestamp&0xffffffffU);
				g_RespMsg.b.TxTimestamp = (uint32_t)(g_nRespTxTimestamp&0xffffffffU);

				g_RespMsg.b.nSequenceNum = cnt;

				/* Zero offset in TX buffer. */
				DWT_WriteTxData( 20, g_RespMsg.Data, 0 );

				/* Zero offset in TX buffer, ranging. */
				DWT_WriteTxFrameCtrl( &g_UWBHandle, 20, 0, 1 );

				ret = DWT_StartTx( &g_UWBHandle, DWT_START_TX_DELAYED );

				/* If DWT_StartTx() returns an error, abandon this ranging 
				exchange and proceed to the next one. See NOTE 10 below. */
				if( ret == DWT_SUCCESS )
				{
					g_nTimeoutMs = 100;

                    while( FALSE ==  g_bUWBReady )
                    {
                        if( 0 == g_nTimeoutMs )
                        {
                            TRACE( "Tx Error. Off Trx\r\n" );
                        }
                    }
	
                    g_bUWBReady = FALSE;

					status = DWT_Read32BitReg( SYS_STATUS_ID );
					DWT_Write32BitReg( SYS_STATUS_ID, 0xffffffff );

					if( 0 != (status&SYS_STATUS_TXFRS) )
					{
						cnt++;
					}
				}

			   DWT_ForceTrxOff( &g_UWBHandle );
			}
			else
			{
			
				DWT_ForceTrxOff( &g_UWBHandle );

				/* Reset RX to properly reinitialize LDE operation. */
				DWT_ResetRx();
			}
		}


        DWT_EnableRx( &g_UWBHandle, DWT_START_RX_IMMEDIATE );
	}
}


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbOnSpiDone( void )
{
	g_bSpiDone = TRUE;
}


decaIrqStatus_t decamutexon( void )
{
	/* If interrupt pin is used, make sure it lock here */
    NVIC_DisableIRQ( EXTI9_5_IRQn );
	return 1;
}


void decamutexoff ( decaIrqStatus_t s )
{
	/* If interrupt pin is used, make sure it unlock here */
	if( s )
	{
        NVIC_EnableIRQ( EXTI9_5_IRQn );
	}
}


int
readfromspi(
	uint16 			headerLength,
	const uint8 	*headerBuffer,
	uint32 			readlength,
	uint8			*readBuffer
	)
{
	memset( g_aSpiTxBuf, 0, sizeof(g_aSpiTxBuf) );
	memcpy( g_aSpiTxBuf, headerBuffer, headerLength );
	memset( g_aSpiRxBuf, 0, sizeof(g_aSpiRxBuf) );	
	
	UWB_CS_ASSERT();
	SpimTransfer(
            &g_SpimHandle,
            g_aSpiTxBuf,
            g_aSpiRxBuf,
            (headerLength + readlength));

	while( FALSE == g_bSpiDone );
	g_bSpiDone = FALSE;

	memcpy( readBuffer, &g_aSpiRxBuf[headerLength], readlength );
	UWB_CS_DEASSERT();
  return 0;
}

int
writetospi(
	uint16		headerLength,
	const uint8 *headerBuffer,
	uint32		bodylength,
	const uint8 *bodyBuffer
	)
{
	memset( g_aSpiTxBuf, 0, sizeof(g_aSpiTxBuf) );
	memcpy( g_aSpiTxBuf, headerBuffer, headerLength );
	memcpy( &g_aSpiTxBuf[headerLength], bodyBuffer, bodylength );	

	UWB_CS_ASSERT();
	SpimTransfer(
	&g_SpimHandle,
	g_aSpiTxBuf,
	g_aSpiRxBuf,
	(headerLength + bodylength) );

	while( FALSE == g_bSpiDone );
	g_bSpiDone = FALSE;  

	UWB_CS_DEASSERT();
	return 0;
}


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_SpimInit( void )
{
	SpimInit(
        &g_SpimHandle,
        1,
        1000000U, 
        SPI_CLK_INACT_LOW,
        SPI_CLK_RISING_EDGE,
        SPI_DATA_SIZE_8 );
	
	SpimAddCallbackTransferDone( &g_SpimHandle, main_cbOnSpiDone );
}


static uint64_t main_GetRxTimestamp64( void )
{
	/* Get the RX time-stamp in a 64-bit variable. This function assumes
	 that length of time-stamps is 40 bits, for both TX and RX! */
    uint8 ts_tab[5];
    uint64_t ts = 0;
    int i;

    DWT_ReadRxTimeStamp( ts_tab );

#if 0
    ts = (ts_tab[4]<<32) 
		| (ts_tab[3]<<24) 
		| (ts_tab[2]<<16) 
		| (ts_tab[1]<<8) 
		| ts_tab[0];

#else
	memcpy( &ts, ts_tab, 5 );
//    for( i=4; i>=0; i-- )
//    {
//        ts <<= 8;
//        ts |= ts_tab[i];
//    }
#endif
    return ts;
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void SysTickHandler( void )
{
    if( 0 != g_nTimeoutMs )
    {
        g_nTimeoutMs--;
    }

    if( 0 != g_nStatusTimeout )
    {
        g_nStatusTimeout--;
    }
}


void EXTI9_UWB_INT_IRQHandler( uint32_t Status )
{
    g_bUWBReady = TRUE;
}



/*************************** End of file *************************************/
