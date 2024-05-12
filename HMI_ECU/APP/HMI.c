#include "./HMI.h"
#include "../MCAL/TIMER1.h"
#include "../MCAL/uart.h"


//key pressed
uint8 key;

boolean checkPassValue;
uint8 numCheckpass = 1;

uint8 PassChecking = 1;

uint8 g_sec = 0;

//Function to increase the global seconds variable
void CountSeconds(void) {
	g_sec++;
}

//saving the password in an array
//displaying * as it is an pass
//adjusting the enter value(=) & the numbers pressed in the keypad
void Password_adjust(uint8 *pass_temp) {
	uint8 key_num = 0;
	while (1) {
		/* Get the pressed key number, if any switch pressed for more than 500 ms it will considered more than one press */
		key = KEYPAD_getPressedKey();
		if (key_num < 5) {
			if ((key <= 9) && (key >= 0)) {
				LCD_intgerToString(key); /* display the pressed keypad switch */
				//store the password in an array
				pass_temp[key_num] = key;
				key_num++;
			}
			_delay_ms(500); /* Press time */
		}
		//after entering the pass of 5 numbers
		//wait for pressing "=" as enter to continue execution
		if (key == '=') {
			break;
		}
	}

}

//Entering pass sequence "Display"
void EnterPass_Sequence(void) {
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "PLZ enter pass:");
	LCD_moveCursor(1, 0); /* Move the cursor to the second row */
	Password_adjust(pass);
	LCD_displayStringRowColumn(0, 0, "PLZ re-enter the");
	LCD_displayStringRowColumn(1, 0, "same pass:");
	LCD_moveCursor(1, 11);
	Password_adjust(pass2);
}

//Function perform as the password is matched or not matched
//function parameters -> another function
//							as to :
//								1)call the Door_Squence function
//								2)call the EnterPass function
void PassWrong_case(void(*func)(void)){
	if (PassChecking == MATCH) {
		(*func)();
	} else {
		LCD_displayStringRowColumn(0, 0,"1 -> Wrong Pass");
		LCD_displayStringRowColumn(1, 0, "pass: ");
		LCD_moveCursor(1, 6); /* Move the cursor to the second row & column 6*/
		Password_adjust(pass);
		SendPass(pass);
		PassChecking = UART_recieveByte();
		LCD_clearScreen();
		if (PassChecking == MATCH) {
			(*func)();
		} else {
			LCD_displayStringRowColumn(0, 0,"2 -> Wrong Pass");
			LCD_displayStringRowColumn(1, 0, "pass: ");
			LCD_moveCursor(1, 6); /* Move the cursor to the second row & column 6*/
			Password_adjust(pass);
			SendPass(pass);
			PassChecking = UART_recieveByte();
			LCD_clearScreen();
			if (PassChecking == MATCH) {
				(*func)();
			} else {
				LCD_displayStringRowColumn(0, 0,"ERROR!!");
				LCD_displayStringRowColumn(1, 0, "3 wrong passes");
				Polling_one_minute();
			}
		}
	}
}

//Send pass to control_ecu through UART
void SendPass(uint8 *pass) {
	for (uint8 i = 0; i < 5; i++) {
		UART_sendByte(pass[i]);
	}
}

//Send pass2 to control_ecu through UART
void SendPass2(uint8 *pass2) {
	for (uint8 i = 0; i < 5; i++) {
		UART_sendByte(pass2[i]);
	}
}


//function that counts the sec by :
//causing an interrupt every second
void DelaySeconds(uint8 sec) {

	/* setting the callBack function to count seconds */
	Timer1_setCallBack(CountSeconds);

	/* timer1 configurations -> count 1 second per interrupt */
	Timer1_ConfigType timer1Config = { 0, 31250, F_CPU_256, CompareMode };

	TIMER1_Init(&timer1Config);

	//stay in the loop until finishing count of seconds
	while (g_sec < sec)
		;

	//safarna al global variable 3lshan al mara aly gya
	g_sec = 0;

	Timer1_deInit();
}

//Pass Entering
//if the two passes are not the same -> then stay in the loop
//until the user enters the same two passes
void EnterPass(void) {
	do {
		LCD_clearScreen();
		EnterPass_Sequence();
		SendPass(pass);
		SendPass2(pass2);
		PassChecking = UART_recieveByte();
	} while (PassChecking == FAILED);
}

//Send the key entered by the user through UART
void SendKey(void) {
	UART_sendByte(key);
}

//Door Sequence "Display"
void Door_Sequence(void){
	LCD_clearScreen();
	LCD_displayString("DoorIsUnlocking");
	_delay_ms(6000);
	_delay_ms(6000);
	_delay_ms(2000);
	LCD_clearScreen();
	LCD_displayString("Stop motor");
	_delay_ms(3000);
	LCD_clearScreen();
	LCD_displayString("Door is locking");
	_delay_ms(6000);
	_delay_ms(6000);
	_delay_ms(2000);
}


void UART_Configurations(void){
	UART_ConfigType ptr_uart_init = { Bits_Data_8, disabled, Bits_Stop_1,
			RATE_9600 };
	UART_init(&ptr_uart_init);
}

//fy approach tany andaf mn al polling al t3ban da
//momken ne3melo be timer0 aw timer2
// bas msh mestahla bsra7a :D
void Polling_one_minute(void){
	for (uint8 i = 0; i < 10; i++) {
		_delay_ms(6000);
	}
}



