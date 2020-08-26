/*****************************************************************************
 @Project  : 
 @File     : PID_Template.c
 @Details  :              
 @Author   : LiangT
 @Hardware : Independent
 
 --------------------------------------------------------------------------
 @Revision  :
  Ver    Author      Date          Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX      Initial Release
   
******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "pwm.h"
#include "Timer.h"
#include "PID.h"


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


/*****************************************************************************
 Callback functions prototypes
******************************************************************************/


/*****************************************************************************
 Local functions prototypes
******************************************************************************/


/*****************************************************************************
 Implementation
******************************************************************************/
void 
PIDCtrlInit(
  PPID_HANDLE pHandle,
  PPWM_HANDLE pPwmHandle,
  uint32_t    nChannel,
  double      dDutyCyclePercent,
  uint32_t    nInterval,
  BOOL        bInverse
  )
{
  ASSERT( 0 != pHandle );
  ASSERT( 0 != pPwmHandle );
  ASSERT( 0 != nInterval );
  
  pHandle->pPwmHandle        = pPwmHandle;
  pHandle->nChannel          = nChannel;
  pHandle->dDutyCyclePercent = dDutyCyclePercent;
  pHandle->dPWM              = dDutyCyclePercent;
  pHandle->dStopRate         = 0.9;
  pHandle->dKp               = 0.0;
  pHandle->dKi               = 0.0;
  pHandle->dKd               = 0.0;
  pHandle->bInverse          = bInverse;
}


void
PIDCtrlSetParam(
  PPID_HANDLE pHandle,
  double      Kp,
  double      Ki,
  double      Kd
  )
{
  ASSERT( 0 != pHandle );
  
  pHandle->dKp = Kp;
  /********************************************************
  * To do: store the remaining ki and kd parameters.
  ********************************************************/
  
}


void PIDRestart( PPID_HANDLE pHandle, BOOL bInverse )
{
  ASSERT( 0 != pHandle );

  /********************************************************
  * To do: reset some pHandle's elements.
  ********************************************************/
  

}


void
PIDCtrlSetTargetValue(
  PPID_HANDLE pHandle,
  int32_t     nValue
  )
{
  ASSERT( 0 != pHandle );
  
  pHandle->nTargetValue = nValue;
}


void
PIDCtrlSetDecreaseRateAtSpeed0(
  PPID_HANDLE pHandle,
  int         nDecPercent
  )
{
  ASSERT( 0 != pHandle );

  pHandle->dStopRate = (double)(100 - nDecPercent) / 100.0;
}


void
PIDCtrlOutputConfig(
  PPID_HANDLE pHandle,
  int32_t     nMin,
  int32_t     nMax,
  double      dFactor
  )
{
  ASSERT( 0 != pHandle );
  
  /********************************************************
  * To do: config pHandle's nMin, nMax and dFactor.
  ********************************************************/





}


PID_STS
PIDOnTimer(
  PPID_HANDLE pHandle,
  int         nFeedbackValue
  )
{
  double output;
  PID_STS res = PID_STS_OK;

  ASSERT( 0 != pHandle );
  
  /* Kp cannot be 0, otherwise PID will not work */
  if( 0.0 == pHandle->dKp )
  {
    return PID_ERR_INVALID_KP;
  }
  
  /* NOTE:
   If target value is 0, PID will take control to slow down the system before 
   stop but this might be too slow.Here we implement a linear brake system such
   that every interval we reduce to a specified percentage. 
   This percentage can be decided base on mechanical behaviour */
  if( 0 == pHandle->nTargetValue )
  {
    /********************************************************
    * To do: processing when the target speed is 0.
    *        You should not stop immediately!
    *        The PWM output should be keep reducing, until 
    *        it is zero, then disable PWM.
    ********************************************************/
    
    
    
    
    
    

    return res;
  }


  /********************************************************
  * To do: PID algorithm implementation.
  * Note1: dFactor is the constant that encoder count 
  *        relates to PWM;
  * Note2: the final output should be in a suitable range;
  ********************************************************/













  pHandle->dPWM = output;
  
  PWMEnable(
    pHandle->pPwmHandle,
    pHandle->nChannel,
    pHandle->dPWM,
    pHandle->bInverse );
    


  return res;
}
















