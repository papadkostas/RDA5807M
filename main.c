#include "main.h"

WM_HWIN CreateWindow(void) {
  WM_HWIN hWin;
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

void MainTask(void){
	WM_HWIN hDlg;
	BUTTON_SetDefaultSkin   (BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin (CHECKBOX_SKIN_FLEX);
	SPINBOX_SetDefaultSkin   (SPINBOX_SKIN_FLEX);
	WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_CURSOR_Show();
	// Call creation function for the dialog
	hDlg = CreateWindow();
	// Keep program alive
	while (1) {
		GUI_Delay(1000);
    	RDA5807_Read();
    	GUI_DispDec(signal,2);
        //sprintf(buf,"kopro",freq);
        //TEXT_SetText(ID_TEXT_2,"kopro");
	}
}

int main(void){
	SystemInit();
  	UB_STemWIN_init();
  	UB_I2C3_Init();
  	RDA5807_Init();
  	MainTask();
 	while(1){
 	}
}
