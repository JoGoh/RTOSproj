/*****************************************************************************
 @Project   : 
 @File      : main.c
 @Details   : Main entry               
 @Author    : 
 @Hardware  : 
 
 --------------------------------------------------------------------------
 @Revision  :
  Ver    Author      Date          Changes
 --------------------------------------------------------------------------

   
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "Timer.h"
#include "Encoder.h"


/*****************************************************************************
 Define
******************************************************************************/


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static TIMER_HOOK         g_TimerHook;
static TIMER_HANDLE       *g_pTimerHandle  = 0;
static int                g_TimerHz;
static volatile int       g_nInterval      = 0;
static int                g_nIntervalConst = 0;
static ENC_CB_READY       *g_pfcbEncReady  = 0;
static double             g_RpmConst       = 0.0;

static PSHAFT_ENC_HANDLE  g_pHeadHandle    = 0;

static int                g_CPR            = 0;
static int                g_GearRatio      = 0;


/*****************************************************************************
 Callback functions prototypes
******************************************************************************/
static void enc_cbOnTimer( void );


/*****************************************************************************
 Local functions prototypes
******************************************************************************/


/*****************************************************************************
 Implementation
******************************************************************************/
void
ShaftEncoderInit(
  PTIMER_HANDLE  pTimerHandle,
  uint32_t       nTimerHz,
  ENC_CB_READY   *pfcbEncReady,
  uint32_t       nIntervalMs
  )
{
  ASSERT( 0 != pTimerHandle );

  /********************************************************
  * To do: 
  ********************************************************/




}


void
ShaftEncoderCfg(
  uint32_t    nCPR,
  uint32_t    nGearRatio,
  uint32_t    nIntervalMs
  )
{
  /********************************************************
  * To do: update g_CPR, g_GearRatio and g_RpmConst
  ********************************************************/



}


void ShaftEncoderChangeInterval( uint32_t nIntervalMs )
{
 /* Output RPM = ((Pulses Recieved in 1 sec * 60) / PPR) / Gear Ratio
  PPR = 2*CPR = 2*48 (Pololu motor is 48CPR) x2 because using both encoder A&B
  Gear Ratio is 47:1 */
  
    TimerStop( g_pTimerHandle );

  /********************************************************
  * To do: update g_RpmConst, g_nIntervalConst and g_nInterval
  ********************************************************/





    TimerStart( g_pTimerHandle );
}


BOOL
ShaftEncoderAdd(
  PSHAFT_ENC_HANDLE  pHandle,
  int                nIndex,
  ENC_CB_THRES       *pfcbEncThresHit
  )
{
  ASSERT( 0 != pHandle );

  /* Reset variable to default 0 */
  memset( pHandle, 0, sizeof(SHAFT_ENC_HANDLE) );
  
  /********************************************************
  * To do: 
  ********************************************************/


  
  return TRUE;
}


void ShaftEncoderReset( PSHAFT_ENC_HANDLE pHandle )
{
  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: 
  ********************************************************/


}


BOOL ShaftEncoderLinkCCM( PSHAFT_ENC_HANDLE pHandle, void *pCcmHandle )
{
  ASSERT( 0 != pHandle );
  ASSERT( 0 != pCcmHandle );

  pHandle->pCcm = pCcmHandle;

  return TRUE;
}


void ShaftEncoderSetThresCount( PSHAFT_ENC_HANDLE pHandle,int nCount )
{
  ASSERT( 0 != pHandle );
  
  pHandle->nThresCnt = nCount;
}


int ShaftEncoderReadCount( PSHAFT_ENC_HANDLE pHandle )
{
  return pHandle->nFinalCnt;
}


int ShaftEncoderReadRPM( PSHAFT_ENC_HANDLE pHandle )
{
  int rpm = (int)(pHandle->nFinalCnt*g_RpmConst);
  return rpm;
}


int ShaftEncoderCountToRpm( int nCount )
{
  int rpm = (int)(nCount*g_RpmConst);
  return rpm;
}


int ShaftEncoderRpmToCount( int nRpm )
{
  /********************************************************
  * To do: return count based on nRpm and g_RpmConst
  ********************************************************/


  return count;
}


void ShaftEncoderISR( PSHAFT_ENC_HANDLE pHandle, BOOL bInputEncBSts )
{

  /********************************************************
  * To do: maintain nTmpCnt counter
  ********************************************************/


}


/*****************************************************************************
 Callback functions 
******************************************************************************/
static void enc_cbOnTimer( void )
{
  PSHAFT_ENC_HANDLE cur;


  /********************************************************
  * To do: record the encoder counter to a encoder handler's
  * nFinalCnt element, and clear the encoder counter so that 
  * it can count for another round.
  ********************************************************/

}


/*****************************************************************************
 Local functions 
******************************************************************************/


/*****************************************************************************
 Interrupt
******************************************************************************/








