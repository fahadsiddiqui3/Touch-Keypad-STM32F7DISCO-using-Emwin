# Virtual-Keyboard-STM32F7DISCO
This is a touch based virtual keyboard, ios style for STM32DISCO using STEMWIN library. This keyboard can be ported to any controller which uses StemWin GUI library.

How to use : 

1) Include keypad.h in the parent window file. Add Virtual_Keyboard.c file in the project.
2) Create a Parent window of the screen resolution of the LCD display.
3) Pass the handle of the parent window to the API CreateKeypad() and you're done. Call this only after the parent window is created.
4) The handle of the keyboard is _hKeyboard and can be used as showing or hiding the keypad. Use WM_ShowWindow(_hKeyboard) to display the keyboard. 
5) Keyboard can be configured as numeric as well as alphanumeric by api Config_Keyboard(). Pass the maximum length of data, and editbox ID wherever the pressed key character needs to be displayed.
