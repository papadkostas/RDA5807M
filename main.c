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
	SLIDER_SetDefaultSkin   (SLIDER_SKIN_FLEX);
	WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
	GUI_CURSOR_Show();
	// Call creation function for the dialog
	hDlg = CreateWindow();
	// Keep program alive
	while (1) {
		GUI_Delay(10);

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
