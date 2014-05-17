#include "main.h"

int main(void){
	SystemInit();
  	UB_STemWIN_init();
  	UB_I2C3_Init();
  	RDA5807_Init();
  	MainTask();
 	while(1){
 	}
}
