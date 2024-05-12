#include "./Control.h"

uint8 g_sec = 0;

//global variable to store the confirmation of received passwords
uint8 match_NotMatch = FAILED;

//Function to increase the global seconds variable
void CountSeconds(void) {
	g_sec++;
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

//Checking if the two passwords are the same and return TRUE | FALSE
uint8 CheckMatchingPass(uint8 *EnteredPass1, uint8 *RenteredPass2) {
	for (uint8 i = 0; i < 5; i++) {
		if (EnteredPass1[i] != RenteredPass2[i])
			return FAILED;
	}
	return MATCH;
}

void RecievePass(void) {
	for (uint8 i = 0; i < 5; i++) {
		Pass1[i] = UART_recieveByte();
	}
}

void RecievePass2(void) {
	for (uint8 i = 0; i < 5; i++) {
		RePass2[i] = UART_recieveByte();
	}
}

void savePass(uint8 *pass) {
	for (uint8 i = 0; i < 5; i++) {
		EEPROM_writeByte((0x0311 + i), pass[i]);
		_delay_ms(10);
	}
}

void readPass(void) {
	for (uint8 i = 0; i < 5; i++) {
		EEPROM_readByte((0x0311 + i), Pass_saved + i);
		_delay_ms(10);
	}
}

// Pass receiving , checking & Saving
//Note: msh hano5rog mn al function 8er lama al etnen passwords yeb2o nafs al haga
void EnterPass(void) {
	do {
		RecievePass();
		RecievePass2();
		match_NotMatch = CheckMatchingPass(Pass1, RePass2);
		UART_sendByte(match_NotMatch);
	} while (match_NotMatch == FAILED);
	savePass(Pass1);
}


// Apply the logic of the motor
//		• rotates motor for 15-seconds CW and display a message on the screen “Door is Unlocking”
//		• hold the motor for 3-seconds.
//		• rotates motor for 15-seconds A-CW and display a message on the screen “Door is Locking”
void Door_Sequence(void){
	DcMotor_Rotate(CW, 100);
	DelaySeconds(15);
	DcMotor_Rotate(STOP, 0);
	DelaySeconds(3);
	DcMotor_Rotate(A_CW, 100);
	DelaySeconds(15);
	DcMotor_Rotate(STOP, 0);
}


//Function perform as the password is matched or not matched
//function parameters -> another function
//							as to :
//								1)call the Door_Squence function
//								2)call the EnterPass function
void PassWrong_case(void(*func)(void)){
	if (match_NotMatch == MATCH) {
		(*func)();
	} else {
		RecievePass();
		readPass();

		match_NotMatch = CheckMatchingPass(Pass1, Pass_saved);
		UART_sendByte(match_NotMatch);
		if (match_NotMatch == MATCH) {
			(*func)();
		} else {
			RecievePass();
			readPass();

			match_NotMatch = CheckMatchingPass(Pass1, Pass_saved);
			UART_sendByte(match_NotMatch);
			if (match_NotMatch == MATCH) {
				(*func)();
			} else {
				Buzzer_on();
				DelaySeconds(60);
				Buzzer_off();
			}
		}
	}
}


void UART_Configurations(void){
	UART_ConfigType ptr_uart_init = { Bits_Data_8, disabled, Bits_Stop_1,
			RATE_9600 };
	UART_init(&ptr_uart_init);
}



