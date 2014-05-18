#include "main.h"

int main(void){
	SystemInit();
  	UB_STemWIN_init();
  	UB_I2C3_Init();
  	RDA5807_Init();
  	//RDA5807_PowerOn();
  	//RDA5807_SeekUp();
  	//RDA5807_Read();
  	MainTask();
 	while(1){
 		/* #To Do#
 		 * Power handler to properly complete power of device
 		 * with NVIC using user pushbutton on STM32F429-Discovery board
 		*/
 	}
}
