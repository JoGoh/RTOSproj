/*****************************************************************************
 @Project	: 
 @File 		: i2c.c
 @Details  	: 
 @Author		: lcgan
 @Hardware	: 
 
 --------------------------------------------------------------------------
 @Revision	:
  Ver  	Author    	Date        	Changes
 --------------------------------------------------------------------------
   1.0  Name     XXXX-XX-XX  		Initial Release
   
******************************************************************************/

#include <Common.h>
#include "Hal.h"
#include "i2c.h"


/*****************************************************************************
 Define
******************************************************************************/
#define TOTAL_I2C			3U


/*****************************************************************************
 Type definition
******************************************************************************/


/*****************************************************************************
 Global Variables
******************************************************************************/


/*****************************************************************************
 constant Variables
******************************************************************************/


/*****************************************************************************
 Local Variables
******************************************************************************/
static volatile PI2C_HANDLE	g_pI2cIrqHandles[TOTAL_I2C];


/*****************************************************************************
 Local functions
******************************************************************************/


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Implementation 
******************************************************************************/
int
I2cInit(
	PI2C_HANDLE 	pHandle,
	uint8_t 		nPort,
	uint32_t 		nBusSpeed 
	)
{
	I2C_TypeDef 	*i2c;
	IRQn_Type 		irq;
	uint32_t 		temp = 0;
	
	ASSERT( 0 != pHandle );
	ASSERT( 0 != nPort );

	/* To do ... */
	
	return I2C_STS_OK;
}


void I2cSetRiseTimeMax( PI2C_HANDLE pHandle, int nRiseNanoSec )
{
	I2C_TypeDef *i2c;
	ASSERT( 0 != pHandle );
}


void
I2cWrite(
	PI2C_HANDLE pHandle,
	uint8_t 	nSlaveAddr,
	uint8_t 	Register,
	void const 	*pData,
	uint8_t 	nByte
	)
{
	I2C_TypeDef *i2c;
	int32_t reg;
	
	ASSERT( 0 != pHandle );
	
	/*To do ...*/
}


void
I2cRead( 
	PI2C_HANDLE pHandle,
	uint8_t 	nSlaveAddr,
	uint8_t 	Register,
	void 		*pData,
	uint8_t 	nByte
	)
{
	I2C_TypeDef *i2c;
	ASSERT( 0 != pHandle );
	
	/*To do ...*/
}


void 
I2cAddHook(
	PI2C_HANDLE 		pHandle,
	PI2C_HOOK 			pHook,
	I2C_CB_DONE 		*pfDone
	)
{
	ASSERT( 0 != pHandle );
	ASSERT( 0 != pHook );
	ASSERT( 0 != pfDone );
	
	pHook->pfDone 		= pfDone;
	pHook->pNext 		= pHandle->pHeadHook;
	pHandle->pHeadHook 	= pHook;
}


/*****************************************************************************
 Callback functions
******************************************************************************/


/*****************************************************************************
 Local functions
******************************************************************************/
static void i2c_Handler( PI2C_HANDLE pHandle, I2C_TypeDef *pI2C )
{
	PI2C_HOOK	cur;
	uint32_t	status = pI2C->ISR;

	ASSERT( 0 != pHandle );
	
	if( 0 != (status & I2C_ISR_STOPF) )
	{
		/*To do ...*/
	}
	else
	{
		if( 0 != (status & I2C_ISR_TXIS) )
		{
		  /*To do: the current byte transmission is done ...*/
		}
		
		if( 0 != (status & I2C_ISR_TC) )
		{
      /*To do: the whole packet transmission is done ...*/
		}
		
		if( 0 != (status & I2C_ISR_RXNE) )
		{
			/*To do ...*/
		}
	}
}


/*****************************************************************************
 Interrupt functions
******************************************************************************/
void I2C1_EV_IRQHandler( void )
{
	i2c_Handler( g_pI2cIrqHandles[0], I2C1 );
}


void I2C2_EV_IRQHandler( void )
{
	i2c_Handler( g_pI2cIrqHandles[1], I2C2 );	
}


void I2C3_EV_IRQHandler( void )
{
	i2c_Handler( g_pI2cIrqHandles[2], I2C3 );	
}












