#include "./HMI.h"

extern uint8 key;
extern uint8 PassChecking;


int main(void) {

	UART_Configurations();

	LCD_init();

	EnterPass();

	while (1) {

		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");
		key = KEYPAD_getPressedKey();
		LCD_clearScreen();
		SendKey();

		if (key == '+') {
			LCD_displayStringRowColumn(0, 0, "pass to cont:");
			LCD_moveCursor(1, 0);
			Password_adjust(pass);
			SendPass(pass);
			PassChecking = UART_recieveByte();
			LCD_clearScreen();
			PassWrong_case(Door_Sequence);

		} else if (key == '-') {
			LCD_displayStringRowColumn(0, 0, "pass to cont:");
			LCD_moveCursor(1, 0);
			Password_adjust(pass);
			SendPass(pass);
			PassChecking = UART_recieveByte();
			LCD_clearScreen();
			PassWrong_case(EnterPass);

		}
	}
}

