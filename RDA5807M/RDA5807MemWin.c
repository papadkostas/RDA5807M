/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.22                          *
*        Compiled Jul  4 2013, 15:16:01                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "stm32_ub_i2c3.h"
#include "RDA5807MemWin.h"
// USER END
#include <string.h>
#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_SPINBOX_0 (GUI_ID_USER + 0x02)
#define ID_TEXT_1 (GUI_ID_USER + 0x03)
#define ID_SPINBOX_1 (GUI_ID_USER + 0x04)
#define ID_BUTTON_0 (GUI_ID_USER + 0x05)
#define ID_BUTTON_1 (GUI_ID_USER + 0x06)
#define ID_CHECKBOX_0 (GUI_ID_USER + 0x07)
#define ID_CHECKBOX_1 (GUI_ID_USER + 0x08)
#define ID_CHECKBOX_2 (GUI_ID_USER + 0x09)
#define ID_BUTTON_2 (GUI_ID_USER + 0x0A)
#define ID_BUTTON_3 (GUI_ID_USER + 0x0B)
#define ID_TEXT_2 (GUI_ID_USER + 0x0C)
#define ID_TEXT_3 (GUI_ID_USER + 0x0D)
#define ID_TEXT_4 (GUI_ID_USER + 0x0E)
#define ID_TEXT_5 (GUI_ID_USER + 0x0F)
#define ID_TEXT_6 (GUI_ID_USER + 0x10)
#define ID_TEXT_7 (GUI_ID_USER + 0x11)
#define ID_TEXT_8 (GUI_ID_USER + 0x12)
#define ID_TEXT_9 (GUI_ID_USER + 0x13)
#define ID_TEXT_10 (GUI_ID_USER + 0x14)
#define ID_TEXT_11 (GUI_ID_USER + 0x15)
#define ID_TEXT_12 (GUI_ID_USER + 0x16)
#define ID_TEXT_13 (GUI_ID_USER + 0x17)
#define ID_TEXT_14 (GUI_ID_USER + 0x18)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 240, 320, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "frequency1", ID_TEXT_0, 5, 300, 80, 20, 0, 0x64, 0 },
  { SPINBOX_CreateIndirect, "frequency_spin", ID_SPINBOX_0, 5, 270, 80, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "volume", ID_TEXT_1, 90, 300, 80, 20, 0, 0x64, 0 },
  { SPINBOX_CreateIndirect, "volume_spin", ID_SPINBOX_1, 90, 270, 80, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "seekdown_btn", ID_BUTTON_0, 5, 230, 80, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "seekup_btn", ID_BUTTON_1, 90, 230, 80, 30, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "rds_box", ID_CHECKBOX_0, 175, 235, 80, 20, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "bass_box", ID_CHECKBOX_1, 175, 265, 80, 20, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "mute_box", ID_CHECKBOX_2, 175, 295, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "pwr_btn", ID_BUTTON_2, 155, 5, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "rst_btn", ID_BUTTON_3, 185, 30, 50, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "title", ID_TEXT_2, 5, 5, 120, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "frequency", ID_TEXT_3, 5, 30, 85, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "freq", ID_TEXT_4, 95, 30, 90, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "signal", ID_TEXT_5, 5, 55, 55, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 60, 55, 20, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "signal_strength", ID_TEXT_7, 65, 55, 20, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "stereo", ID_TEXT_8, 5, 75, 60, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "stereo_status", ID_TEXT_9, 70, 75, 30, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "rds", ID_TEXT_10, 5, 95, 45, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "rds_status", ID_TEXT_11, 55, 95, 180, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "STATIONname", ID_TEXT_12, 5, 115, 235, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "RDStext", ID_TEXT_13, 10, 145, 220, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "CTtime", ID_TEXT_14, 5, 175, 235, 20, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  float   frq;
  char bufem[10];
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, 0x00000000);
	//
	// Initialization of channel frequency spinbox
	//
	hItem = WM_GetDialogItem(pMsg->hWin,  ID_SPINBOX_0);
	SPINBOX_SetRange(hItem, 870, 1080);
	SPINBOX_SetFont(hItem, GUI_FONT_COMIC18B_1);
	//
	// Initialization of volume volume spinbox
	//
	hItem = WM_GetDialogItem(pMsg->hWin,  ID_SPINBOX_1);
	SPINBOX_SetRange(hItem, 0, 15);
	SPINBOX_SetValue(hItem, StartingVolume);
	SPINBOX_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'frequency1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetText(hItem, "Frequency");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'volume'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetText(hItem, "Volume");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'seekdown_btn'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_8X17);
    BUTTON_SetText(hItem, "Seek Down");
    //
    // Initialization of 'seekup_btn'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_8X17);
    BUTTON_SetText(hItem, "Seek Up");
    //
    // Initialization of 'rds_box'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "RDS");
    CHECKBOX_SetTextColor(hItem, 0x00FFFFFF);
    CHECKBOX_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'bass_box'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
    CHECKBOX_SetText(hItem, "Bass");
    CHECKBOX_SetFont(hItem, GUI_FONT_COMIC18B_1);
    CHECKBOX_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'mute_box'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);
    CHECKBOX_SetText(hItem, "Mute");
    CHECKBOX_SetTextColor(hItem, 0x00FFFFFF);
    CHECKBOX_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'pwr_btn'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, GUI_FONT_8X17);
    BUTTON_SetText(hItem, "Power On");
    //
    // Initialization of 'rst_btn'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetText(hItem, "Reset");
    BUTTON_SetFont(hItem, GUI_FONT_8X17);
    //
    // Initialization of 'title'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetText(hItem, "RDA5807M FM");
    TEXT_SetTextColor(hItem, 0x00000FFF);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'frequency'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetText(hItem, "Frequency : ");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'freq'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetText(hItem, "");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'signal'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetText(hItem, "RSSI : ");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetText(hItem, "");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'signal_strength'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetText(hItem, "");
    //
    // Initialization of 'stereo'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetText(hItem, "Stereo : ");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'stereo_status'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetText(hItem, "");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'rds'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetText(hItem, "RDS :");
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'rds_status'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetText(hItem, "");
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'STATIONname'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetFont(hItem, GUI_FONT_COMIC24B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetText(hItem, "");
    //
    // Initialization of 'RDStext'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetText(hItem, "");
    //
    // Initialization of 'CTtime'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
    TEXT_SetFont(hItem, GUI_FONT_COMIC24B_1);
    TEXT_SetTextColor(hItem, 0x00FFFFFF);
    TEXT_SetText(hItem, "");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_SPINBOX_0: // Notifications sent by 'frequency_spin'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
    	frq = SPINBOX_GetValue(pMsg->hWinSrc);
    	RDA5807_Frequency(((float)frq/(float)10));
    	GUI_Delay(200);
    	RDA5807_Read();
    	frq = (float)freq / 1001;
    	int d1 = frq;
    	int d2= (frq - d1)*10;
    	sprintf (bufem, "%d.%dMHz", d1, d2);
    	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    	TEXT_SetText(hItem,bufem);
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SPINBOX_1: // Notifications sent by 'volume_spin'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
    	RDA5807_Volume(SPINBOX_GetValue(pMsg->hWinSrc));
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'seekdown_btn'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
		RDA5807_SeekDown();
    	GUI_Delay(200);
    	RDA5807_Read();
    	frq = (float)freq / 1000;
    	int d1 = frq;
    	int d2= (frq - d1)*10.1;
    	sprintf (bufem, "%d.%dMHz", d1, d2);
    	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    	TEXT_SetText(hItem,bufem);
    	frq = (float)freq / 100;
    	hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
    	SPINBOX_SetValue(hItem, frq);
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'seekup_btn'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
		RDA5807_SeekUp();
		GUI_Delay(200);
    	RDA5807_Read();
    	frq = (float)freq / 1000;
    	int d1 = frq;
    	int d2= (frq - d1)*10.1;
    	sprintf (bufem, "%d.%dMHz", d1, d2);
    	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    	TEXT_SetText(hItem,bufem);
    	frq = (float)freq / 100;
    	hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
    	SPINBOX_SetValue(hItem, frq);
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_0: // Notifications sent by 'rds_box'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
    	RDA5807_RDS();
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_1: // Notifications sent by 'bass_box'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        RDA5807_BassBoost();
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_2: // Notifications sent by 'mute_box'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
		RDA5807_Mute();
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'pwr_btn'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
		if((RDA5807M_WriteReg[0] & 1) == 0){
      		RDA5807_PowerOn();
      		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
      		BUTTON_SetText(hItem, "Power Off");
      		GUI_Delay(200);
      		RDA5807_Read();
      		frq = (float)freq / 1000;
      		int d1 = frq;
      		int d2= (frq - d1)*10.1;
      		sprintf (bufem, "%d.%dMHz", d1, d2);
      		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
      		TEXT_SetText(hItem,bufem);
      		frq = (float)freq / 100;
      		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
      		SPINBOX_SetValue(hItem, frq);
      	}
      	else{
  			RDA5807_PowerOff();
      		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
      		BUTTON_SetText(hItem, "Power On");
      		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
      		TEXT_SetText(hItem,"");
      		frq = (float)freq / 100;
      		hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
      		SPINBOX_SetValue(hItem, frq);
      	}
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'rst_btn'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
		RDA5807_Reset();
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN CreateWindow(void);
WM_HWIN CreateWindow(void) {
  WM_HWIN hWin;
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}
// ####################### float f_fmhz=f_fbeg+i_ch*0.10;
// USER START (Optionally insert additional public code)
void MainTask(void);
void MainTask(void){
	int8_t t;
	UB_Led_Init();
  	UB_I2C3_Init();
  	RDA5807_Init();
	WM_HWIN hDlg,hText;
	BUTTON_SetDefaultSkin   (BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin (CHECKBOX_SKIN_FLEX);
	SPINBOX_SetDefaultSkin   (SPINBOX_SKIN_FLEX);
	WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_CURSOR_Show();
	// Call creation function for the dialog
	hDlg = CreateWindow();
	// Keep program alive
	while(1){
		GUI_Delay(200);

		// ********** RDA5807_read() call moved to stm32_ub_touch_stmpe811.c file for faster RDS updates **********

		while ((RDA5807M_WriteReg[0] & 0x1) == 0x1){
			GUI_Delay(200);
			hText = WM_GetDialogItem(hDlg, ID_TEXT_7);
			sprintf (refresh, "%d", signal);
			TEXT_SetText(hText, refresh);
			if(stereo == 0x400){
				TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_9), "Yes");
			}
			else{
				TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_9), "No");
			}

			if(rdssynchro == 0x1000){
					TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_11), "On, Sync'd.");

					sprintf(refresh, "Station: %s",StationName);
					TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_12), refresh);  // Display RDS station name

					if(strlen(RDStext)>26){
						int8_t textlen=strlen(RDStext);
						strcpy (RDSscrolltext, RDStext + t);
						t++;
						if(t>textlen){t=0;}
						sprintf(refresh, "%s",RDSscrolltext); //Scroll RDS text if more than 26 text characters
					}
					else {
						sprintf(refresh, "%s",RDStext);  // Display RDS text static on one line if less than 27 characters
					}
					TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_13), refresh);  // display RDS text message

					TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_14), CTtime);  // Display CT time, updates on the minute
			}
			else{
				TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_11), "Off!"); // Clear RDS info if no rdssynchro
				TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_12), "");
				TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_13), "");
				TEXT_SetText(WM_GetDialogItem(hDlg, ID_TEXT_14), "");
			}
		}
	}
}
// USER END

/*************************** End of file ****************************/
