
#include "main.h"
#include "stm32f4xx_hal.h"
#include "UL/ulLedCtrl.h"
#include "UL/ulButton.h"
#include "UL/ulUart.h"
#include "DL/SysTickDrv.h"
#include "DL/UartDrv.h"


void Periphery_Init(void);


int main(void)
{
	uint16_t period;

	Periphery_Init();
	ulUart_SendMessage("\nProgram run\n\r", 14);


  while (1)
  {
	  period = 0;

	  ulLedCtrl_Run();
	  ulButton_Run();
	  ulUart_Run();

	  if(ulButton_NewPeriodDetected())
	  {
		  period = ulButton_ReadPeriod();
		  ulLedCtrl_SetPeriod(period);
	  }
	  if(ulUart_NewPeriodDetected())
	  {
		  period = ulUart_ReadPeriod();
  		  ulLedCtrl_SetPeriod(period);
	  }
  }
}

void Periphery_Init(void){
		HAL_Init();
		SysTickDrv_Init();
		ulLedCtrl_Init();
		ulButton_Init();
		ulUart_Init();
}

void _Error_Handler(char * file, int line)
{
  while(1) 
  {
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif

