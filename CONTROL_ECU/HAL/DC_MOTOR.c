#include "../HAL/DC_MOTOR.h"
#include "../MCAL/GPIO.h"
#include "avr/io.h"
#include "../MCAL/PWM.h"

void DcMotor_init(void){
	//PIN0:1 --> outpus in PORTB
	GPIO_setupPinDirection(PORTB_ID , PIN0_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID , PIN1_ID , PIN_OUTPUT);

	//Stop the DC-Motor at the beginning
	PORTB = (PORTB_ID & 0XFC) | (STOP);
}


void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	PORTB = (PORTB_ID & 0XFC) | (state);
	Timer0_PWM_Init(speed);
}
