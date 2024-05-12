#include "./Control.h"

//global variable to store the confirmation of received passwords
extern uint8 match_NotMatch ;


int main(void) {

	UART_Configurations();

	Buzzer_init();
	DcMotor_init();
	SREG |= (1 << 7);

	TWI_ConfigType *ptr_twi_init;
	ptr_twi_init->address = 0x01;
	ptr_twi_init->bit_rate = 2;
	TWI_init(&ptr_twi_init);

	EnterPass();

	while (1) {
		key_received = UART_recieveByte();

		if (key_received == '+') {
			RecievePass();
			readPass();

			match_NotMatch = CheckMatchingPass(Pass1, Pass_saved);
			UART_sendByte(match_NotMatch);

			PassWrong_case(Door_Sequence);

		} else if (key_received == '-') {
			RecievePass();
			readPass();

			match_NotMatch = CheckMatchingPass(Pass1, Pass_saved);
			UART_sendByte(match_NotMatch);

			PassWrong_case(EnterPass);

		}
	}

}

