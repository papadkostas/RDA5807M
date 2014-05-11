#include "main.h"
void dump(void);
int main(){
  SystemInit();
  UB_LCD_Init();
  UB_LCD_LayerInit_Fullscreen();
  UB_LCD_SetLayer_1();
  UB_LCD_FillLayer(RGB_COL_WHITE);
  UB_LCD_SetLayer_2();
  UB_LCD_FillLayer(RGB_COL_BLACK);
  UB_LCD_Rotate_0();
  UB_Font_DrawString(20,10,"STM32F429-RDA5807M",&Arial_11x18,RGB_COL_BLUE,RGB_COL_BLACK);
  UB_I2C3_Init();
  RDAstatus = RDA5807_Init();
  if(RDAstatus >= 0){
	  RDAstatus = RDA5807_PowerOn();
  }
  else{
	  sprintf(buf,"Error = %d    ",RDAstatus);
	  UB_Font_DrawString(10,40,buf,&Arial_11x18,RGB_COL_RED,RGB_COL_BLACK);
  }
  while(1){
	  Delay(10000000);
	  RDAstatus = RDA5807_Read();
	  dump();
  }
  return 0;
}
void Delay(volatile uint32_t nCount){
  while(nCount--) {
  }
}

void dump(){
	uint8_t i;
	UB_Font_DrawString(10,40,"RDA REGISTERS DUMP",&Arial_11x18,RGB_COL_BLUE,RGB_COL_BLACK);
	for(i=0;i<7; i++){
		sprintf(buf,"Reg%d = 0x%04x",i,RDA5807M_ReadReg[i]);
		UB_Font_DrawString(10,60+(i*20),buf,&Arial_11x18,RGB_COL_BLUE,RGB_COL_BLACK);
	}
}
