/*****************************************************************************
 @Project	: 
 @File 		: UltraSound.c
 @Details  	: Ultrasonic driver               
 @Author	: 
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#include <Common.h>
#include "Hal.h"
#include "Timer.h"
#include "UltraSound.h"


/*****************************************************************************
 Define
******************************************************************************/
#define US_ECHO_TIMEOUT			18U	/* ms, for 300cm->17.46ms, */
#define TOTAL_USONIC			8U
#define US_DEFAULT_DIST_MAX		20000U

#define US_TIMER_FREQ_MIN		10000U	/* 10KHz */


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/

static TIMER_HOOK			g_TimerHook;
static PUSONIC_HANDLE		g_pusonicIrqHandles[TOTAL_USONIC]; /* these handle pointers are used in ISR */
static double				g_dTimerUsConst = 0;	/* Timer period in us */
static int					g_nTriggerConst = 0;	/* trigger timeout at least 10us */


/*****************************************************************************
 Local functions
******************************************************************************/
static void sonic_cbOnTimer( void );


/*****************************************************************************
 Implementation
******************************************************************************/
int
USonicInit(
	PTIMER_HANDLE 	pTimer,
	int				nTimerFreq
	)
{
	int cnt;
	
	ASSERT( 0 != pTimer );
	ASSERT( 0 != nTimerFreq );

	/* Timer run too slow. insufficient to use */
	if( nTimerFreq < US_TIMER_FREQ_MIN )
	{
		/* Return error code */
		return USONIC_TIMER_FREQ_INVALID;
	}
	
	/* Reset handles to 0 */
	for( cnt=0; cnt<TOTAL_USONIC; cnt++ )
	{
		g_pusonicIrqHandles[cnt] = 0;
	}

	g_dTimerUsConst = 1000000.0 / nTimerFreq; /* timer period in us. Time per tick */

	if( g_dTimerUsConst > 10.0 )
	{
		/* It is fine for trigger time more than 10us that required */
		g_nTriggerConst = 1;
	}
	else
	{
		/* If timer run faster to 10us, we need to scale back using incremental delay */
		g_nTriggerConst = 10 / g_dTimerUsConst;
	}
	
	/* Add a timer callback */
	TimerAddHook(
		pTimer,
		&g_TimerHook,
		sonic_cbOnTimer );
}


int 
UsonicAddDevice(
	PUSONIC_HANDLE 			pHandle,
	uint8_t 				nIndex,
	USONIC_CB_ON_TRIGGER	*pfOnTrigger,
	USONIC_CBI_READY 		*pfOnReady
	)
{
	ASSERT( 0 != pHandle );
	ASSERT( 0 != pfOnTrigger );
	ASSERT( 0 != pfOnReady );
	
  /********************************************************
  * To do: 
  * 1) Initialize the pHandle elements;
  * 2) Store the pHandle (address) into the g_pusonicIrqHandles array,
  *    so that when the ultrasonic Echo interrupt is asserted,
  *    the generic ultrasonic ISR function, UsonicISR(), can
  *    fetch each ultrasonic pHandle stored information;
  ********************************************************/



	
	return USONIC_SUCCESS;
}


void USonicTrigger( PUSONIC_HANDLE 	pHandle )
{
	ASSERT( 0 != pHandle );
	
  /********************************************************
  * To do:
  * This function is called if a ultrasonic sensor is triggered,
  * hence, this function needs to assert the Trig signal.
  * 1) Set some of pHandle elements (starting of a ultrasonic
  *    sensing);
  * 2) Call the pHandle's pfOnTrigger function pointer, which
  *    will call the "CallBack" function listed in the second
  *    last argument in the UsonicAddDevice() function;
  ********************************************************/



}


void
USonicSetEchoTimeOut(
	PUSONIC_HANDLE	pHandle,
	int				nTimeoutMs,
	int				nDistMax
	)
{
	ASSERT( 0 != pHandle );
	
  /********************************************************
  * To do:
  * Implementation of this function is low priority.
  * This function sets two elements in :
  * 1) nTimeoutConst: according to the input nTimeoutMs,
  *    sets the timeout value;
  * 2) nDistanceMax: the Max distance (=nDistMax);
  * The Echo Timeout feature serves when the Echo signal 
  * doesn't de-assert to 0.
  * Reason: no echo sound (when you point the ultrasonc
  * sensor speaker to the open sky).
  * Without this feature, your system may hang to wait the
  * Echo signal's falling edge.
  * With this function, if the Echo signal's falling edge
  * doesn't come after a certain timeout, the ultrasonic sensing
  * should be stopped.
  * The Echo Timeout feture is implemented in the Ultrasonic's
  * Timer callBack function: sonic_cbOnTimer.
  ********************************************************/



}


uint32_t USonicRead( PUSONIC_HANDLE pHandle )
{
	ASSERT( 0 != pHandle );

	return pHandle->nDistance;
}


void UsonicISR( PUSONIC_HANDLE 	pHandle, BOOL bEcho )
{
	uint32_t tmp;
	
	ASSERT( 0 != pHandle );

	if( 0 != bEcho )
	{
		pHandle->nTimerTick = 0;
		pHandle->bValidEdge = TRUE;
		return;
	}
	
	if( FALSE != pHandle->bValidEdge )
	{
		pHandle->bValidEdge = FALSE;
			
		/* If counter is 0, use previous value. This is sensor error */
		if( 0 != pHandle->nTimerTick )
		{
      /********************************************************
      * To do: 
      * The Echo signal's falling edge is detected if the
      * software runs here.
      * 1) Read the pHandle's nTimerTick value, and use the 
      *    ultrasonic distance equation, calculate the distance;
      * 2) If the calculated distance makes sense, call the 
      *    pHandle's pfOnReady() function pointer, which points
      *    to the function listed in the last argument of the 
      *    UsonicAddDevice() function.
      ********************************************************/



		}
	}
}


/*****************************************************************************
 Callback functions
******************************************************************************/
static void sonic_cbOnTimer( void )
{
	int				cnt;
    PUSONIC_HANDLE	sensor;
	
  /********************************************************
  * To do:
  * This function is a Timer callBack function for the
  * ultrasonic application.
  * The purpose of this function is to increase a time tick 
  * (pHandle's nTimerTick element), so that when the Echo
  * signal's falling edge is detected, the Echo signal's
  * assertion period can be known.
  * Since there are 8 ultrasonic sensors, for each sensor 
  * (by using the g_pusonicIrqHandles array to fetch each 
  * ultrasonic handler), need to do:
  * 1) Increase nTimerTick by 1;
  * 2) Implement the Echo Timeout feature;
  ********************************************************/



}


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Interrupt functions
******************************************************************************/





















































