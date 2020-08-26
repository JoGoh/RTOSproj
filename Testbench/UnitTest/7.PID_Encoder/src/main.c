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
#include "motors.h"
#include "Encoder.h"
#include "PID.h"


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS					500
#define TIMER1_TICK_HZ				10000U		/* 10KHz */
#define ENCODER_SMPL_INTRVL_MS		100U		/* 100ms */

#define DEFAULT_DUTY				18
#define PID_TARGET_DEFAULT_RPM		30
#define DUTY_CYCLE_MIN				18U
#define DUTY_CYCLE_MAX				100U
#define OUTPUT_FACTOR				0.44f


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

static TIMER_HANDLE			g_Timer1Handle;

static SHAFT_ENC_HANDLE		g_ShaftEncHandles[TOTAL_MOTOR];
static volatile BOOL		g_bEncoderData = FALSE;


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

	TimerInit( &g_Timer1Handle, 1, TIMER1_TICK_HZ );

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

    TimerStart( &g_Timer1Handle );

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
	ShaftEncoderInit(
		&g_Timer1Handle,
		TIMER1_TICK_HZ,
		main_cbEncoderRdy,
		ENCODER_SMPL_INTRVL_MS );

	/* Configure Motor Encoder and gear parameters */
	ShaftEncoderCfg(
		16,   /* encoder by interrupt only using 1 encoder, not quadrature */
		70,
		ENCODER_SMPL_INTRVL_MS );

	/* Add 4 available encoders */
	ShaftEncoderAdd( &g_ShaftEncHandles[0], 0, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[1], 1, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[2], 2, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[3], 3, 0 );
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


void EXTI9_M1_ENC_IN1_IRQHandler( uint32_t Status )
{
	UNUSE( Status );
	ShaftEncoderISR( &g_ShaftEncHandles[0], IN_M1_ENC_IN2() );
}


void EXTI4_M2_ENC_IN1_IRQHandler( uint32_t Status )
{
	UNUSE( Status );
	ShaftEncoderISR( &g_ShaftEncHandles[1], IN_M2_ENC_IN2() );
}


void EXTI0_M3_ENC_IN1_IRQHandler( uint32_t Status )
{
	UNUSE( Status );
	ShaftEncoderISR( &g_ShaftEncHandles[2], IN_M3_ENC_IN2() );
}


void EXTI12_M4_ENC_IN1_IRQHandler( uint32_t Status )
{
	UNUSE( Status );
	ShaftEncoderISR( &g_ShaftEncHandles[3], IN_M4_ENC_IN2() );
}
