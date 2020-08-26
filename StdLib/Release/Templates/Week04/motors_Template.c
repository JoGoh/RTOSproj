/*****************************************************************************
 @Project	: 
 @File 		: motors.c
 @Details  	: 
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
#include "pwm.h"
#include "Motors.h"

#ifdef _PID_EN
	#include "PID.h"
#endif

/*****************************************************************************
 Define
******************************************************************************/
#define DEFAULT_DUTY			10


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static PWM_HANDLE 		g_PwmHandle;

#ifdef _PID_EN
	static PID_HANDLE		g_PIDHandles[TOTAL_MOTOR];
#endif


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Implementation 
******************************************************************************/
void MotorsInit( void )
{
	/* NOTE:
	 PWM for Motor speed control Initialization.
	 20kHz so it will not generate a human hear able sound */

	/* WARNING:
	 Make sure and check what is the maximum frequency can feed into Motor driver board.
	 It may vary from different type of motor driver board */
	PWMInit( &g_PwmHandle, 8U, 20000U );
}




void MotorsAllEnable( int nDutyClyce )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void Motors1Enable( int nDutyClyce )
{
	/* Start all motor speed control PWM */
	PWMEnable( &g_PwmHandle, 1, nDutyClyce, FALSE );
    M1_PWM_OUT_EN();
}


void Motors2Enable( int nDutyClyce )
{
	/* Start all motor speed control PWM */
  /********************************************************
  * To do: ...
  ********************************************************/


}

void Motors3Enable( int nDutyClyce )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}

void Motors4Enable( int nDutyClyce )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsMoveFront( int nDutyClyce  )
{
	MOTORS_MOVE_FORWARD(); /* Set direction */

	/* Start all motor speed control PWM */
	PWMEnable( &g_PwmHandle, 1, nDutyClyce, FALSE );
	PWMEnable( &g_PwmHandle, 2, nDutyClyce, FALSE );
	PWMEnable( &g_PwmHandle, 3, nDutyClyce, FALSE );
	PWMEnable( &g_PwmHandle, 4, nDutyClyce, FALSE );
	MOTORS_RUN();
}

void MotorsMoveBack( int nDutyClyce  )
{
	MOTORS_MOVE_BACKWARD(); /* Set direction */

  /********************************************************
  * To do: ...
  ********************************************************/



}


void MotorsMoveLeft( int nDutyClyce  )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsMoveRight( int nDutyClyce  )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsMoveFrontLeft( int nDutyClyce  )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsMoveBackLeft( int nDutyClyce  )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsMoveBackRight( int nDutyClyce  )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsMoveFrontRight( int nDutyClyce  )
{
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsRotateRight( int nDutyClyce )
{
	MOTORS_ROTATE_RIGHT(); /* Set direction */

	/* Start all motor speed control PWM */
  /********************************************************
  * To do: ...
  ********************************************************/


}


void MotorsRotateLeft( int nDutyClyce )
{
	MOTORS_ROTATE_LEFT(); /* Set direction */

	/* Start all motor speed control PWM */
  /********************************************************
  * To do: ...
  ********************************************************/


}




void MotorsStop( void )
{
	MOTORS_STOP(); /* Set direction */

	/* Start all motor speed control PWM */
  /********************************************************
  * To do: ...
  ********************************************************/


}

/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Interrupt functions
******************************************************************************/


















