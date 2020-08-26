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


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS					500
#define DEFAULT_DUTY				25
#define TOTAL_MOTOR					4
#define TIMER1_TICK_HZ				10000U		/* 10KHz */
#define ENCODER_SMPL_INTRVL_MS		100U		/* 100ms */


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

 Output RPM = ((Pulses Recieved in 1 sec * 60) / PPR) / Gear Ratio
 PPR = CPR/4 = 16 (Pololu motor is 64CPR) 
 Divide by 4 is due to we only use encoder A rising edge. We lost resolution but
 reduce interrupt overhead. This is disadvantage using this method. CCM will be 
 ideal
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

	/* Add 4 available encoders */
	ShaftEncoderAdd( &g_ShaftEncHandles[0], 0, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[1], 1, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[2], 2, 0 );
	ShaftEncoderAdd( &g_ShaftEncHandles[3], 3, 0 );
}


static void main_CtrlUpdateWheelSpeed( void )
{
	int raw;
	int cnt;

	TRACE("Encoder : ");
	for( cnt=0; cnt<TOTAL_MOTOR; cnt++ )
	{
		/* It is possible to read in term of RPM if ShaftEncoderCfg() is called and configured.
		ShaftEncoderReadRPM() will give you the RPM */
		raw = ShaftEncoderReadCount( &g_ShaftEncHandles[cnt] );
		TRACE( "%d ", raw );
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


/* All these functions called from IRQ.c */
void EXTI9_M1_ENC_IN1_IRQHandler( uint32_t Status )
{
	ShaftEncoderISR( &g_ShaftEncHandles[0], IN_M1_ENC_IN2() );
}


void EXTI4_M2_ENC_IN1_IRQHandler( uint32_t Status )
{
	ShaftEncoderISR( &g_ShaftEncHandles[1], IN_M2_ENC_IN2() );
}


void EXTI0_M3_ENC_IN1_IRQHandler( uint32_t Status )
{
	ShaftEncoderISR( &g_ShaftEncHandles[2], IN_M3_ENC_IN2() );
}


void EXTI12_M4_ENC_IN1_IRQHandler( uint32_t Status )
{
	ShaftEncoderISR( &g_ShaftEncHandles[3], IN_M4_ENC_IN2() );
}


/* End of file */