#include "main.h"
#include "DIALOG.h"
#include "string.h"

/*
* File : Keypad.c
* Created by : Fahad Siddiqui
* Date : 23-Sep-2017
*/

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0            (GUI_ID_USER + 0x00)
#define ID_BUTTON_0            (GUI_ID_USER + 0x01)  // a
#define ID_BUTTON_1            (GUI_ID_USER + 0x02)  // b
#define ID_BUTTON_2            (GUI_ID_USER + 0x03)  // c
#define ID_BUTTON_3            (GUI_ID_USER + 0x04)  // etc..
#define ID_BUTTON_4            (GUI_ID_USER + 0x05)
#define ID_BUTTON_5            (GUI_ID_USER + 0x06)
#define ID_BUTTON_6            (GUI_ID_USER + 0x07)
#define ID_BUTTON_7            (GUI_ID_USER + 0x08)
#define ID_BUTTON_8            (GUI_ID_USER + 0x09)
#define ID_BUTTON_9            (GUI_ID_USER + 0x0A)
#define ID_BUTTON_10           (GUI_ID_USER + 0x0B)
#define ID_BUTTON_11           (GUI_ID_USER + 0x0C)
#define ID_BUTTON_12           (GUI_ID_USER + 0x0D)
#define ID_BUTTON_13           (GUI_ID_USER + 0x0E)
#define ID_BUTTON_14           (GUI_ID_USER + 0x0F)
#define ID_BUTTON_15           (GUI_ID_USER + 0x10)
#define ID_BUTTON_16           (GUI_ID_USER + 0x11)
#define ID_BUTTON_17           (GUI_ID_USER + 0x12)
#define ID_BUTTON_18           (GUI_ID_USER + 0x13)
#define ID_BUTTON_19           (GUI_ID_USER + 0x14)
#define ID_BUTTON_20           (GUI_ID_USER + 0x15)
#define ID_BUTTON_21           (GUI_ID_USER + 0x16)
#define ID_BUTTON_22           (GUI_ID_USER + 0x17)
#define ID_BUTTON_23           (GUI_ID_USER + 0x18)
#define ID_BUTTON_24           (GUI_ID_USER + 0x19)
#define ID_BUTTON_25           (GUI_ID_USER + 0x1A)  // z
#define ID_BUTTON_26           (GUI_ID_USER + 0x1B)  // Back
#define ID_BUTTON_27           (GUI_ID_USER + 0x1C)  // Clr
#define ID_BUTTON_28           (GUI_ID_USER + 0x20)  // Caps
#define ID_BUTTON_29           (GUI_ID_USER + 0x1D)  // Space
#define ID_BUTTON_30           (GUI_ID_USER + 0x21)  // 123
#define ID_BUTTON_31           (GUI_ID_USER + 0x22)  // Enter


#define ID_WINDOW_1            (GUI_ID_USER + 0x23)
#define ID_EDIT_0              (GUI_ID_USER + 0x24)

#define BUTTON_X_SIZE           75
#define BUTTON_Y_SIZE           50

#define FOURTH_ROW_BUTTON_Y_SIZE  35

#define BUTTON_SPACING          5

#define BUTTON_X_POS(x)         BUTTON_SPACING + (x * (BUTTON_X_SIZE + BUTTON_SPACING))

#define OFFSET_SECOND_ROW_X     BUTTON_X_SIZE / 2 + BUTTON_SPACING
#define OFFSET_SECOND_ROW_Y     BUTTON_Y_SIZE + (BUTTON_SPACING * 2)

#define OFFSET_THIRD_ROW_X      BUTTON_X_SIZE + BUTTON_SPACING * 2
#define OFFSET_THIRD_ROW_Y     (BUTTON_Y_SIZE * 2) + (BUTTON_SPACING * 3)

#define OFFSET_FOURTH_ROW_X      BUTTON_X_SIZE + BUTTON_SPACING * 3
#define OFFSET_FOURTH_ROW_Y     (BUTTON_Y_SIZE * 3) + (BUTTON_SPACING * 4)

#define COLOR_BUTTON_FRAME_0    GUI_BLACK
#define COLOR_BUTTON_FRAME_1    GUI_BLACK

#define COLOR_BUTTON_BK_0       GUI_WHITE
#define COLOR_BUTTON_BK_1       GUI_GRAY

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
typedef struct {
  GUI_COLOR aColorFrame[2];
  GUI_COLOR aColorBK[2];
} COLORS;

static COLORS _Colors = {
  { COLOR_BUTTON_FRAME_0, COLOR_BUTTON_FRAME_1},
  { COLOR_BUTTON_BK_0,    COLOR_BUTTON_BK_1   }
};

/* First row button ids are not in order, if we need to display numerics then lots of conditions has to be check,
so create the button id for row0 in order and the row0 characters also.
*/
static const uint32_t Num_Row[] = {
	ID_BUTTON_16,ID_BUTTON_22,ID_BUTTON_4,ID_BUTTON_17,ID_BUTTON_19,
	ID_BUTTON_24,ID_BUTTON_20,ID_BUTTON_8,ID_BUTTON_14,ID_BUTTON_15
};
static const char Row_0_ASCII_U[] = "QWERTYUIOP"; 
static const char Row_0_ASCII_L[] = "qwertyuiop"; 
/*********************************************************************
*
*       _aKeyboardDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aKeyboardDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, (BUTTON_X_SIZE + BUTTON_SPACING) * 10 + BUTTON_SPACING, ( (BUTTON_Y_SIZE + BUTTON_SPACING) *4) + BUTTON_SPACING, 0, 0x0, 0 },
  //
  // First row
  //
  { BUTTON_CreateIndirect, "q", ID_BUTTON_16, BUTTON_X_POS(0), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "w", ID_BUTTON_22, BUTTON_X_POS(1), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "e", ID_BUTTON_4,  BUTTON_X_POS(2), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "r", ID_BUTTON_17, BUTTON_X_POS(3), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "t", ID_BUTTON_19, BUTTON_X_POS(4), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "y", ID_BUTTON_24, BUTTON_X_POS(5), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "u", ID_BUTTON_20, BUTTON_X_POS(6), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "i", ID_BUTTON_8,  BUTTON_X_POS(7), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "o", ID_BUTTON_14, BUTTON_X_POS(8), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "p", ID_BUTTON_15, BUTTON_X_POS(9), BUTTON_SPACING, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  //
  // Second row
  //
  { BUTTON_CreateIndirect, "a", ID_BUTTON_0,  OFFSET_SECOND_ROW_X + BUTTON_X_POS(0), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "s", ID_BUTTON_18, OFFSET_SECOND_ROW_X + BUTTON_X_POS(1), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "d", ID_BUTTON_3,  OFFSET_SECOND_ROW_X + BUTTON_X_POS(2), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "f", ID_BUTTON_5,  OFFSET_SECOND_ROW_X + BUTTON_X_POS(3), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "g", ID_BUTTON_6,  OFFSET_SECOND_ROW_X + BUTTON_X_POS(4), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "h", ID_BUTTON_7,  OFFSET_SECOND_ROW_X + BUTTON_X_POS(5), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "j", ID_BUTTON_9,  OFFSET_SECOND_ROW_X + BUTTON_X_POS(6), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "k", ID_BUTTON_10, OFFSET_SECOND_ROW_X + BUTTON_X_POS(7), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "l", ID_BUTTON_11, OFFSET_SECOND_ROW_X + BUTTON_X_POS(8), OFFSET_SECOND_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  //
  // Third row
  //
  { BUTTON_CreateIndirect, "123",  ID_BUTTON_30, BUTTON_X_POS(0), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE + 2, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "z",     ID_BUTTON_25, BUTTON_X_POS(1), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "x",     ID_BUTTON_23, BUTTON_X_POS(2), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "c",     ID_BUTTON_2,  BUTTON_X_POS(3), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "v",     ID_BUTTON_21, BUTTON_X_POS(4), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "b",     ID_BUTTON_1,  BUTTON_X_POS(5), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "n",     ID_BUTTON_13, BUTTON_X_POS(6), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "m",     ID_BUTTON_12, BUTTON_X_POS(7), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  //
  // Some special commands
  //
  { BUTTON_CreateIndirect, "Bck",    ID_BUTTON_26, BUTTON_X_POS(8), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Clr",   ID_BUTTON_27, BUTTON_X_POS(9), OFFSET_THIRD_ROW_Y, BUTTON_X_SIZE, BUTTON_Y_SIZE, 0, 0x0, 0 },
  
  //
  //Fourth Row
  //
  { BUTTON_CreateIndirect, "Caps",  ID_BUTTON_28,  BUTTON_X_POS(0) + 20 ,  OFFSET_FOURTH_ROW_Y, BUTTON_X_SIZE * 2 , FOURTH_ROW_BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Space", ID_BUTTON_29,  BUTTON_X_POS(2) + 20 , OFFSET_FOURTH_ROW_Y, BUTTON_X_SIZE * 6 , FOURTH_ROW_BUTTON_Y_SIZE, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Enter", ID_BUTTON_31,  BUTTON_X_POS(8) , OFFSET_FOURTH_ROW_Y, BUTTON_X_SIZE * 2 , FOURTH_ROW_BUTTON_Y_SIZE, 0, 0x0, 0 },
};

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_1,  0,  0, 800, 480, 0, 0x0, 0 },
  { EDIT_CreateIndirect,   "Edit",   ID_EDIT_0,   10, 10, 790,  60, 0, 0x64, 0 },
};

/*********************************************************************
*
*       _hKeyboard
*/
static WM_HWIN _hKeyboard;  // If it is know module wide itis easier to handle, in this case

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
 /*********************************************************************
*
*       _cbButton
*/
static void _cbButton(WM_MESSAGE * pMsg) {
  GUI_RECT Rect;
  int      State;
  char     acText[8];

  switch (pMsg->MsgId) {
  case WM_PAINT:
    //
    // Handle the look of the buttons
    //
    WM_GetClientRect(&Rect);
    State = BUTTON_IsPressed(pMsg->hWin);                                       // Get the state of the button and use it
    GUI_SetColor(_Colors.aColorBK[State]);                                      // as an index to choose a proper color (in this case the BK colors set are identical)
    GUI_FillRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, 5);                 // Fill a rounded rectangle with the color
    GUI_SetColor(_Colors.aColorFrame[State]);                                   // Choose a color for the button frame and the txt to be displayed
    GUI_DrawRoundedRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1, 5);                 // Draw a rounded rectangle around the button
    GUI_DrawRoundedRect(Rect.x0 -1, Rect.y0 - 1, Rect.x1 - 1, Rect.y1 - 1, 5); // And another one
    BUTTON_GetText(pMsg->hWin, acText, sizeof(acText));                         // Get Button text
    GUI_SetTextMode(GUI_TM_TRANS);
    Rect.x0 += 2;
	 GUI_SetFont(&GUI_Font32B_1);
	 WIDGET_SetDefaultEffect(&WIDGET_Effect_3D);
    GUI_DispStringInRect(acText, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);       // Display the button text inside the button rectangle
    break;
  default:
    BUTTON_Callback(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbKeybord
*/
static void _cbKeybord(WM_MESSAGE * pMsg) {
  GUI_RECT Rect;
  static char __Caps=0;
  static char __Num=0;
  WM_HWIN  hItem;
  WM_HWIN  hParent;
  int      NCode;
  int      Id;
  int      i;
  char     c;
  char     acTextSrc[100 + 1];
  char     acText[2]={0,0};
 // char     acTextDest[100 + 1];
  int      Len;

  switch (pMsg->MsgId)
  {
  case WM_INIT_DIALOG:
    //
    // Set a custom callback for each button
    //
	 hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_LIGHTGRAY);
    for (i = 0; i <= ID_BUTTON_31 - ID_BUTTON_0; i++) {
      hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0 + i);
      WM_SetCallback(hItem, _cbButton);
    }
    break;
	 
  case WM_PAINT:
    //
    // Fill background with black and draw a frame around the keyboard window
    //
	 GUI_Clear();
    GUI_SetBkColor(GUI_BLACK);
    WM_GetClientRect(&Rect);
    GUI_SetColor(COLOR_BUTTON_FRAME_0);
    GUI_DrawRoundedRect(0, 0, Rect.x1, Rect.y1 + 5, 5);
    break;
	 
  case WM_NOTIFY_PARENT:
    //
    // The important part
    //
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(NCode)
	 {
		case WM_NOTIFICATION_RELEASED:
      //
      // Get the parent window of the keyboard (it's the main dialog with the edit widget)
      //
      hParent = WM_GetParent(pMsg->hWin);
      //
      // With the handle of the parent window we can get the edit handle by its ID
      //
      hItem   = WM_GetDialogItem(hParent, ID_EDIT_0);
      //
      // Set Focus on the edit widget to make sure it gets the key input
      //
      WM_SetFocus(hItem);
		EDIT_SetFont(hItem,&GUI_Font32B_1);
      if (Id < ID_BUTTON_26) {
        //
        // With the ID of the pressed button calculate the character which should be displayed
        //
		  hItem = WM_GetDialogItem(pMsg->hWin, Id);
		  BUTTON_GetText(hItem, acText, sizeof(acText)); 
        c = acText[0];
        //
        // Store key messages, important that we generate two since every key needs to be released, too
        //
        GUI_StoreKeyMsg(c, 1);
        GUI_StoreKeyMsg(c, 0);
      } 
      else 
      {
	switch(Id)
	{
		case ID_BUTTON_26:/* Back Button, Get The text from edit and manipulate*/
				  EDIT_GetText(hItem, acTextSrc, sizeof(acTextSrc));  // Get
				  Len = strlen(acTextSrc);
				  if (Len > 0) {
					 acTextSrc[Len - 1] = '\0';                        // Adapt
					 EDIT_SetText(hItem, acTextSrc);                   // Write back
				  }	
				  break;			

		case ID_BUTTON_27: /* Clear Button*/
					EDIT_SetText(hItem, "");  
					break;

		case ID_BUTTON_28: /* Caps Lock*/
					if(__Num == 0){
						for (i = 0; i <= ID_BUTTON_25 - ID_BUTTON_0; i++) {
							hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0 + i);
							BUTTON_GetText(hItem, acText, sizeof(acText)); 
							acText[0] = __Caps==0? acText[0] - 32: acText[0] + 32;																			
							BUTTON_SetText(hItem,(const char*)acText);
							}
							__Caps = ~__Caps;   /// Complemenet caps
						}										
					break;

		case ID_BUTTON_29: /*Space button*/
					c = ' ';                                            // Same as other characters
					GUI_StoreKeyMsg(c, 1);                   //For Pressed 
					GUI_StoreKeyMsg(c, 0);						//For Released
					break;

		case ID_BUTTON_30: /* 123*/
					if(__Num == 0)acText[0] = '0';	
					for (i = 0; i <10; i++) {			
						hItem = WM_GetDialogItem(pMsg->hWin, Num_Row[i]);  //Get Dialog item

						if(__Num == 0){											//If user wanted to display num characters
						BUTTON_SetText(hItem,acText);
						acText[0]++;
						} else {																		// If user wanted to show alphabets
						acText[0]=__Caps == 0? Row_0_ASCII_L[i]:Row_0_ASCII_U[i];	//if previously upper case was visible or lower case 
						BUTTON_SetText(hItem,(const char*)acText);						
						}								
					}
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_30);
					if(__Num == 0 )BUTTON_SetText(hItem,"ABC");
					else BUTTON_SetText(hItem,"123");
					__Num = ~ __Num;    // Complement Num for next selection
					break;

		case ID_BUTTON_31: /* Enter*/
			
		default:  break;

	   }


	}
		
      break;
		
    }
	 
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
	 
  }
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  char     acTextSrc[100 + 1];
  
  switch (pMsg->MsgId) {
		  
  case WM_INIT_DIALOG:
		  
  case WM_PAINT:
    //
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_MAKE_COLOR(0x00000000));
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
	 GUI_SetFont(&GUI_FontD32);
	 EDIT_GetText(hItem, acTextSrc, sizeof(acTextSrc)); 
    EDIT_SetText(hItem, acTextSrc);
    break;
		  
  case WM_TOUCH:
    //
    // If we touch somewhere on the screnn the keyboard gets hidden
    //
    WM_HideWindow(_hKeyboard);
    break;
		  
  case WM_NOTIFY_PARENT:
		  
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
		  
    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_RELEASED:
        //
        // After a click inside the edit widget, we show the keyboard
        //
        WM_ShowWindow(_hKeyboard);
        break;
      }
      break;
    }
    break;
		  
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
*       MainTask
*/
void MainTask(void) {
  static WM_HWIN hWin;
  int xSize, ySize;
  int xPos,  yPos;
    GUI_Clear();
 // GUI_Init();
  //
  WIDGET_SetDefaultEffect(&WIDGET_Effect_3D);
  // Create te main dialog containing an edit widget and a keyboard dialog

  hWin       = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  //
  // Get some properties and calculate the x and y position for the keaboard
  //
  xSize      = WM_GetWindowSizeX(hWin);
  ySize      = WM_GetWindowSizeY(hWin);
  xPos       = (xSize - ((BUTTON_X_SIZE + BUTTON_SPACING) * 10 + BUTTON_SPACING)) / 2;
  yPos       = ySize  - ((BUTTON_Y_SIZE + BUTTON_SPACING) *  3 + FOURTH_ROW_BUTTON_Y_SIZE + (BUTTON_SPACING *2));
  //
  // Create the keyboard dialog as a child of the main dialog, but hide it for the beginning
  //
  _hKeyboard = GUI_CreateDialogBox(_aKeyboardDialogCreate, GUI_COUNTOF(_aKeyboardDialogCreate), _cbKeybord, hWin, xPos, yPos);
 // WM_HideWindow(_hKeyboard);  // It's hidden


}
