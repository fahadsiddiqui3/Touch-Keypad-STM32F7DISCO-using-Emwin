#include "main.h"
#include "DIALOG.h"
#include "string.h"
#include "keypad.h"
#include "stdint.h"
/*
* File : Keypad.c
* Created by : Fahad Siddiqui
* Date : 23-Sep-2017
*/

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
WM_HWIN _hKeyboard;	
keyboard_Data_t KeyData;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0            (GUI_ID_USER + 0x20)
#define ID_BUTTON_0            (GUI_ID_USER + 0x21)  // a
#define ID_BUTTON_1            (GUI_ID_USER + 0x22)  // b
#define ID_BUTTON_2            (GUI_ID_USER + 0x23)  // c
#define ID_BUTTON_3            (GUI_ID_USER + 0x24)  // etc..
#define ID_BUTTON_4            (GUI_ID_USER + 0x25)
#define ID_BUTTON_5            (GUI_ID_USER + 0x26)
#define ID_BUTTON_6            (GUI_ID_USER + 0x27)
#define ID_BUTTON_7            (GUI_ID_USER + 0x28)
#define ID_BUTTON_8            (GUI_ID_USER + 0x29)
#define ID_BUTTON_9            (GUI_ID_USER + 0x2A)
#define ID_BUTTON_10           (GUI_ID_USER + 0x2B)
#define ID_BUTTON_11           (GUI_ID_USER + 0x2C)
#define ID_BUTTON_12           (GUI_ID_USER + 0x2D)
#define ID_BUTTON_13           (GUI_ID_USER + 0x2E)
#define ID_BUTTON_14           (GUI_ID_USER + 0x2F)
#define ID_BUTTON_15           (GUI_ID_USER + 0x30)
#define ID_BUTTON_16           (GUI_ID_USER + 0x31)
#define ID_BUTTON_17           (GUI_ID_USER + 0x32)
#define ID_BUTTON_18           (GUI_ID_USER + 0x33)
#define ID_BUTTON_19           (GUI_ID_USER + 0x34)
#define ID_BUTTON_20           (GUI_ID_USER + 0x35)
#define ID_BUTTON_21           (GUI_ID_USER + 0x36)
#define ID_BUTTON_22           (GUI_ID_USER + 0x37)
#define ID_BUTTON_23           (GUI_ID_USER + 0x38)
#define ID_BUTTON_24           (GUI_ID_USER + 0x39)
#define ID_BUTTON_25           (GUI_ID_USER + 0x3A)  // z
#define ID_BUTTON_26           (GUI_ID_USER + 0x3B)  // Back
#define ID_BUTTON_27           (GUI_ID_USER + 0x3C)  // Clr
#define ID_BUTTON_28           (GUI_ID_USER + 0x3D)  // Caps
#define ID_BUTTON_29           (GUI_ID_USER + 0x3E)  // Space
#define ID_BUTTON_30           (GUI_ID_USER + 0x3F)  // 123
#define ID_BUTTON_31           (GUI_ID_USER + 0x40)  // Enter



#define ID_EDIT_0 (GUI_ID_USER + 0x07)
#define ID_EDIT_1 (GUI_ID_USER + 0x09)

#define BUTTON_X_SIZE           75
#define BUTTON_Y_SIZE           55

#define FOURTH_ROW_BUTTON_Y_SIZE  40

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

#define MAX_EDIT_LEN		16
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
static uint16_t Num_Row[] = 
{
	ID_BUTTON_16, ID_BUTTON_22, ID_BUTTON_4 , ID_BUTTON_17, ID_BUTTON_19,
	ID_BUTTON_24, ID_BUTTON_20, ID_BUTTON_8 , ID_BUTTON_14, ID_BUTTON_15,
	ID_BUTTON_0 , ID_BUTTON_18, ID_BUTTON_3 , ID_BUTTON_5 , ID_BUTTON_6 ,
	ID_BUTTON_7 , ID_BUTTON_9 , ID_BUTTON_10, ID_BUTTON_11, ID_BUTTON_25,
	ID_BUTTON_23, ID_BUTTON_2 , ID_BUTTON_21, ID_BUTTON_1 , ID_BUTTON_13,
	ID_BUTTON_12
};

static char Num_Special_Char[] = 
{
	'1' , '2' , '3' ,'4' , '5' , '6' , '7' , '8' , '9','0', 
	'@', '#' , '%' , '&' ,'-' , '+' , '(' , ')' , '*' , '"',
	'|', '<' , '>' , '!' ,'?' , '_'
};
static char Alphabets_Char[] = 
{
	'q', 'w' , 'e' , 'r' ,'t' , 'y' , 'u' , 'i' , 'o' , 'p',
	'a', 's' , 'd' , 'f' ,'g' , 'h' , 'j' , 'k' , 'l' , 'z',
	'x', 'c' , 'v' , 'b' ,'n' , 'm'
};



/*********************************************************************
*
*       _aKeyboardDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aKeyboardDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, (BUTTON_X_SIZE + BUTTON_SPACING) * 10 + BUTTON_SPACING, ( (BUTTON_Y_SIZE + BUTTON_SPACING) *4) + BUTTON_SPACING, 0, 0x64, 0 },
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
*       _hKeyboard
*/
#define ID_OK				1
#define ID_NOT_OK  	0

uint32_t Is_ID_Numeric(uint16_t Id)
{
	int i;
	
	for(i = 0; i<10;i++)
	{
		if(Id == Num_Row[i])
			return ID_OK;
	}
	
	return ID_NOT_OK;
}


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

  char     acText[2]={0,0};
	char     acTextSrc[100 + 1];
  int      Len;

  switch (pMsg->MsgId)
	{
		case WM_INIT_DIALOG:
					// Set a custom callback for each button
					hItem = pMsg->hWin;
					WINDOW_SetBkColor(hItem, GUI_LIGHTGRAY);
					for (i = 0; i <= ID_BUTTON_31 - ID_BUTTON_0; i++) 
					{
						hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0 + i);
						WM_SetCallback(hItem, _cbButton);
					}			
					__Caps = 0;
					__Num  = 0;
					break;
		 
		case WM_PAINT:
					// Fill background with black and draw a frame around the keyboard window
					GUI_SetBkColor(GUI_LIGHTGRAY);
					WM_GetClientRect(&Rect);
					GUI_SetColor(COLOR_BUTTON_FRAME_0);
					GUI_DrawRoundedRect(0, 0, Rect.x1, Rect.y1 + 5, 5);
					break;
		 
		case WM_NOTIFY_PARENT:
		
				// The important part
				Id    = WM_GetId(pMsg->hWinSrc);
				NCode = pMsg->Data.v;
				switch(NCode)
				{
				case WM_NOTIFICATION_RELEASED:

					// Get the parent window of the keyboard (it's the main dialog with the edit widget)
					hParent = WM_GetParent(pMsg->hWin);

					// With the handle of the parent window we can get the edit handle by its ID
					hItem   = WM_GetDialogItem(hParent, KeyData.Current_Editbox);

					// Set Focus on the edit widget to make sure it gets the key input
					 WM_SetFocus(hItem);

					 EDIT_SetFont(hItem,&GUI_Font32_1);
					 EDIT_GetText(hItem, acTextSrc,sizeof(acTextSrc));

					if (Id < ID_BUTTON_26) 
					{

						// With the ID of the pressed button calculate the character which should be displayed
						hItem = WM_GetDialogItem(pMsg->hWin, Id);

						BUTTON_GetText(hItem, acText, sizeof(acText)); 
						c = acText[0];

						// Store key messages, important that we generate two since every key needs to be released, too
						if(strlen(acTextSrc) < KeyData.Max_Len)
						{
							switch (KeyData.Start_Mode)
							{
								case Alpha :  GUI_StoreKeyMsg(c, 1);
									GUI_StoreKeyMsg(c, 0);
									break;
								case Numeric: 
									if(__Num != 0)
									{
										if(Is_ID_Numeric(Id) == ID_OK)
										{
											GUI_StoreKeyMsg(c, 1);
											GUI_StoreKeyMsg(c, 0);
										}
									}
									break;

								default : 	GUI_StoreKeyMsg(c, 1);
								GUI_StoreKeyMsg(c, 0);
								break;
							}
						}
					} 
					else 
					{
						switch(Id)
						{
							case  ID_BUTTON_26:
										/* Back Button, Get The text from edit and manipulate*/
										EDIT_GetText(hItem, acTextSrc, sizeof(acTextSrc));  // Get
										Len = strlen(acTextSrc);
										if (Len > 0) 
										{
										 acTextSrc[Len - 1] = '\0';                        // Adapt
										 EDIT_SetText(hItem, acTextSrc);                   // Write back
										}	
										break;			

							case  ID_BUTTON_27: /* Clear Button*/
										EDIT_SetText(hItem, "");  
										break;

							case  ID_BUTTON_28: /* Caps Lock*/
										if(__Num == 0)
										{
											for (i = 0; i <= ID_BUTTON_25 - ID_BUTTON_0; i++)
											{

												hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0 + i);

												BUTTON_GetText(hItem, acText, sizeof(acText)); 

												acText[0] = __Caps==0? acText[0] - 32: acText[0] + 32;				

												BUTTON_SetText(hItem,(const char*)acText);

												}
												__Caps = ~__Caps;// Complemenet caps
											}										
										break;

							case  ID_BUTTON_29: /*Space button*/
										c = ' ';      															// Same as other characters
										if(acTextSrc[0]!= '\0')
										{
											if(acTextSrc[strlen(acTextSrc)-1]!= ' ')
											{
												GUI_StoreKeyMsg(c, 1);                   //For Pressed 
												GUI_StoreKeyMsg(c, 0);		      				 //For Released
											}
										}
										break;

							case  ID_BUTTON_30: /* 123*/

										if(__Num != 0)
											acText[0] = 'a';	

										for (i = 0; i <26; i++) 
										{			

												hItem = WM_GetDialogItem(pMsg->hWin, Num_Row[i]);  //Get Dialog item

												if(__Num == 0) //If user wanted to display num characters
												{		

													acText[0] = Num_Special_Char[i];																	
													BUTTON_SetText(hItem,(const char *)acText);

												} 
												else // If user wanted to show alphabets
												{			

													//if previously upper case was visible or lower case 
													acText[0]= __Caps == 0 ? Alphabets_Char[i] /*lower case */: Alphabets_Char[i]-32/*Upper Case*/ ;	
													BUTTON_SetText(hItem,(const char*)acText);						
											}								
										}
										hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_30);

										if(__Num == 0 )
											BUTTON_SetText(hItem,"ABC");
										else 
											BUTTON_SetText(hItem,"123");

										__Num = ~ __Num;    // Complement Num for next selection
										break;

							case  ID_BUTTON_31: 
										WM_HideWindow(_hKeyboard);																								
										break; /* Enter*/		

							default:  break;

					 }

				 }

					break;

				}//Switch case 2

				break;
				
			default:
							WM_DefaultProc(pMsg);
							break;
	 
   }//Switch case 1
	
}

void Config_Keyboard(uint16_t Max_Len, uint32_t Editbox_Id, Keymode Mode)
{

					KeyData.Start_Mode = Mode;
					KeyData.Max_Len = Max_Len; // Max Len 		
					KeyData.Current_Editbox = Editbox_Id;

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
void CreateKeypad(WM_HWIN hWin) 
{
	
  int xSize, ySize;
  int xPos,  yPos;

  WIDGET_SetDefaultEffect(&WIDGET_Effect_3D);

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

   WM_HideWindow(_hKeyboard);  // It's hidden.......
	

}
