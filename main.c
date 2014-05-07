#include "main.h"

int main(){
  SystemInit();
  UB_LCD_Init();
  UB_Led_Init();
  UB_LCD_LayerInit_Fullscreen();
  UB_LCD_SetLayer_1();
  UB_LCD_FillLayer(RGB_COL_WHITE);
  UB_LCD_SetLayer_2();
  UB_LCD_FillLayer(RGB_COL_BLACK);
  UB_LCD_Rotate_0();
  UB_Font_DrawString(20,10,"STM32F429-RDA5807M",&Arial_11x18,RGB_COL_BLUE,RGB_COL_BLACK);
  UB_I2C3_Init();
  int8_t rda = RDA5807_WriteAll();
  if(rda >= 0){
	  return 0;
  }
  else{
	  sprintf(buf,"Error = %d    ",rda);
	  UB_Font_DrawString(10,40,buf,&Arial_11x18,RGB_COL_RED,RGB_COL_BLACK);
	  return 0;
  }
  return 0;
}
void Delay(volatile uint32_t nCount){
  while(nCount--) {
  }
}
