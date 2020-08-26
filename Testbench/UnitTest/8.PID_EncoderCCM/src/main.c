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
#include "BSP.h"
#include "IRQ.h"
#include "Timer.h"
#include "Pwm.h"
#include "Ccm.h"
#include "motors.h"
#include "Encoder.h"
#include "PID.h"


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS					500
#define TIMER5_TICK_HZ				2000U		/* 2KHz */
#define ENCODER_SMPL_INTRVL_MS		100U		/* 100ms */

#define DEFAULT_DUTY				18
#define PID_TARGET_DEFAULT_RPM		40
#define DUTY_CYCLE_MIN				18U
#define DUTY_CYCLE_MAX				40U
#define OUTPUT_FACTOR				0.072f


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Const Local Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int 		g_nSysTick 			= SYS_TICK_MS;
static volatile BOOL 		g_bLEDToggle		= FALSE;

static TIMER_HANDLE			g_Timer5Handle;

static SHAFT_ENC_HANDLE		g_ShaftEncHandles[TOTAL_MOTOR];
static volatile BOOL		g_bEncoderData = FALSE;

static CCM_HANDLE			g_CcmHandles[TOTAL_MOTOR];


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_EncodersInit( void );


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbEncoderRdy( void );
static void main_CtrlUpdateWheelSpeed( void );


/*****************************************************************************
 Implementation 
******************************************************************************/
/* NOTE: 
 This example is to use PWM to turn motors in 8 directions.
 This program is prepared based on Pin Assignment Table and its wheel direction
*/

int main( void )
{
	/* Board Support Package initialization */
    BSPInit();
	
	TRACE( "System Boot up\r\n" );
    TRACE( "SystemCoreClock %dHz", SystemCoreClock );

	/* WARNING:
	 System tick is called direct from ARM Core. Do not use for heavy processing.
	 System tick normally use for increase or decrease a counter or set/reset a flag.
	 Heavy processing in System Tick will caused MCU not responsive!
	*/
	/* Generate interrupt each 1 ms as system tick */
	SysTick_Config( SystemCoreClock/1000 );

	TimerInit( &g_Timer5Handle, 5, TIMER5_TICK_HZ );

	main_EncodersInit();

    MotorsInit();

	MotorsPIDConfig(
		DEFAULT_DUTY,
		PID_TARGET_DEFAULT_RPM,
		ENCODER_SMPL_INTRVL_MS,
		DUTY_CYCLE_MIN,
		DUTY_CYCLE_MAX,
		OUTPUT_FACTOR );

	/* NOTE: At start, Motors shall stops for Safety issue */
    MotorsStop();

	/* Move front */
	
    MotorsMoveFront( DEFAULT_DUTY );
	/* Kick timer to run */
    TimerStart( &g_Timer5Handle );

    IRQInit();

	/* TODO: */
	/* Students can test for the rest of the direction */


	/* Runtime for loop */
    for(;;)
    {

        if( TRUE == g_bEncoderData )
		{
			/* Only Encoder data count is ready only will execute */
			g_bEncoderData = FALSE;
			main_CtrlUpdateWheelSpeed();
		}
	}
}


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbEncoderRdy( void )
{
	g_bEncoderData = TRUE;
}


/*****************************************************************************
 Local functions
******************************************************************************/
static void main_EncodersInit( void )
{
	int res;
	res = CCMInit( &g_CcmHandles[0], 1U );
	ASSERT( CCM_OK == res );

	res = CCMInit( &g_CcmHandles[1], 3U );
	ASSERT( CCM_OK == res );

	res = CCMInit( &g_CcmHandles[2], 2U );
	ASSERT( CCM_OK == res );

	res = CCMInit( &g_CcmHandles[3], 4U );
	ASSERT( CCM_OK == res );

	CCMEncoderMode( &g_CcmHandles[0], CCM_ENC_INPUT_AB );
	CCMEncoderMode( &g_CcmHandles[1], CCM_ENC_INPUT_AB );
        CCMEncoderMode( &g_CcmHandles[2], CCM_ENC_INPUT_AB );
	CCMEncoderMode( &g_CcmHandles[3], CCM_ENC_INPUT_AB );

	ShaftEncoderInit(
		&g_Timer5Handle,
		TIMER5_TICK_HZ,
		main_cbEncoderRdy,
		ENCODER_SMPL_INTRVL_MS );

	ShaftEncoderCfg(
		64,
		70,
		ENCODER_SMPL_INTRVL_MS );

	/* Add 4 available encoders */
	ShaftEncoderAdd( &g_ShaftEncHandles[0], 0, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[1], 1, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[2], 2, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[3], 3, 0 );

	/* Link to CCM for high performance */
    ShaftEncoderLinkCCM( &g_ShaftEncHandles[0], &g_CcmHandles[0] );
    ShaftEncoderLinkCCM( &g_ShaftEncHandles[1], &g_CcmHandles[1] );
    ShaftEncoderLinkCCM( &g_ShaftEncHandles[2], &g_CcmHandles[2] );
	ShaftEncoderLinkCCM( &g_ShaftEncHandles[3], &g_CcmHandles[3] );
}


static void main_CtrlUpdateWheelSpeed( void )
{
	int			rpm;
	uint32_t	cnt;

	TRACE("Encoder : ");
	for( cnt=0; cnt<TOTAL_MOTOR; cnt++ )
	{
		rpm = ShaftEncoderReadRPM( &g_ShaftEncHandles[cnt] );
		TRACE( "%d ", rpm );
		if( rpm<0 )
		{
			rpm = -rpm;
		}
	
		if( (0 != rpm)&&(-1 != rpm) )
		{
			if( rpm<0 )
			{
				rpm = -rpm;
			}

			/* PID running */
			MotorsRunPID( cnt, rpm );
		}
	}
	TRACE("\r\n");
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void SysTick_Handler( void )
{
	/* Provide system tick with a specified period 
	decided by macro SYS_TICK_MS */
	if( 0 != g_nSysTick )
	{
		g_nSysTick--;
		
		if( 0 == g_nSysTick )
		{
			g_nSysTick = SYS_TICK_MS;

			g_bLEDToggle = !g_bLEDToggle;
            LED_RED_SET( g_bLEDToggle );
		}
	}
}

