/*****************************************************************************
 @Project  : 
 @File     : main.c
 @Details  : Main entry for UART unit test
 @Author   : Liang
 @Hardware : STM32F722
 
 --------------------------------------------------------------------------
 @Revision  :
  Ver    Author      Date          Changes
 --------------------------------------------------------------------------
   1.0   lcgan      2018-09-01     Initial Release
   1.1   Liang      2018-10-03     Add the UART transmission, and remove 
                                   other non-UART features.

******************************************************************************/
#include <Common.h>
#include "Hal.h"
#include "BSP.h"
#include "IRQ.h"
#include "Timer.h"
#include "Pwm.h"
#include "Ccm.h"
#include "Serial.h"
#include "motors.h"
#include "Encoder.h"
#include "term.h"
#include "Move.h"


/*****************************************************************************
 Define
******************************************************************************/
#define SYS_TICK_MS               1
#define TIMER5_TICK_HZ            10000U   /* 10KHz */
#define ENCODER_SMPL_INTRVL_MS    20U      /* 100ms */

#define MOTOR_STOP_DELAY_MS       500 / SYS_TICK_MS

#define DEFAULT_DUTY              18
#define PID_TARGET_DEFAULT_RPM    50
#define DUTY_CYCLE_MIN            18U
#define DUTY_CYCLE_MAX            100U
#define OUTPUT_FACTOR             0.072f

#define UART_APP_BUF_SIZE_TX      64U
#define UART_APP_BUF_SIZE_RX      64U

/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 Const Local Variables
******************************************************************************/
extern UART_DRIVER const   STM32F722X_USART_DRV;


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile int      g_nSysTick       = SYS_TICK_MS;
static volatile BOOL     g_bSystemTick    = FALSE;
static volatile BOOL     g_bLEDToggle     = FALSE;

static TIMER_HANDLE      g_Timer5Handle;

static UART_HANDLE       g_BtUartHandle;
static char              g_aBtUartTxBuf[UART_APP_BUF_SIZE_TX];
static char              g_aBtUartRxBuf[UART_APP_BUF_SIZE_RX];
static volatile BOOL     g_bBtUartRxDone = FALSE;


/*****************************************************************************
 Local functions
******************************************************************************/
static void UartInit( void );

/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Implementation 
******************************************************************************/
/* NOTE: 
 This example is to use PWM to turn motors in 8 directions.
 This program is prepared based on Pin Assignment Table and its wheel direction
*/

int main( void )
{
  char *cmd;

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

  UartInit();

  TimerInit( &g_Timer5Handle, 9, TIMER5_TICK_HZ );

  TimerStart( &g_Timer5Handle );

  IRQInit();


  strncpy(g_aBtUartTxBuf, "Test", UART_APP_BUF_SIZE_TX);
  for(;;)
  {
    SerialWriteEx(
    &g_BtUartHandle,
    g_aBtUartTxBuf,
    strlen(g_aBtUartTxBuf) );

    if( FALSE != g_bBtUartRxDone )
    {
      g_bBtUartRxDone = FALSE;

      cmd = TerminalParse( &g_BtUartHandle );
      if( 0 != cmd )
      {
        TRACE("==> Received string:%s\n ", cmd );
      }
    }
    else
    {
      TRACE("==> No receiving!\n");/* Add delay here!*/
    }
  }

}


/*****************************************************************************
 Callback functions
******************************************************************************/
static void main_cbBtUartOnRx( void )
{
  g_bBtUartRxDone = TRUE;
}


/*****************************************************************************
 Local functions
******************************************************************************/
static void UartInit( void )
{
  /* This USART2 is assigned for Command interpreter(shell) use */
  int res;

  NVIC_SetPriority( USART2_IRQn, 0x09 );

  res = SerialInit(
      &g_BtUartHandle,
      &STM32F722X_USART_DRV,
      2U,        /* BT USART */
      921600 );
  ASSERT( res == UART_STS_OK );

  SerialBuffer(
      &g_BtUartHandle,
      g_aBtUartTxBuf,
      sizeof(g_aBtUartTxBuf),
      g_aBtUartRxBuf,
      sizeof(g_aBtUartRxBuf) );

  res = SerialConfig(
      &g_BtUartHandle, 
      UART_BITS_8, 
      UART_NONE,
      UART_ONE );
  ASSERT( res == UART_STS_OK );

  SerialAddCallback( &g_BtUartHandle, 0, main_cbBtUartOnRx );
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
      g_bSystemTick = TRUE;

      g_bLEDToggle = !g_bLEDToggle;
      LED_RED_SET( g_bLEDToggle );
    }
  }
}

