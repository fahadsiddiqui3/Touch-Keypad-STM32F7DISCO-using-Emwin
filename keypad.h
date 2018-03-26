#ifndef __KEYPAD_H__
	#define __KEYPAD_H__
	
	
	typedef enum {
		
	Numeric = 0,
	Alpha
	}Keymode;
	
	
	typedef struct {
		
		uint16_t Current_Editbox;
		uint16_t Max_Len;
		Keymode Start_Mode;
	}keyboard_Data_t;
	
	void CreateKeypad(WM_HWIN hWin);
	void Config_Keyboard(uint16_t Max_Len, uint32_t Editbox_Id, Keymode Mode);
#endif

/************* EOF *****/
