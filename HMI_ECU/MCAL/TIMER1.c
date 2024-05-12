#include <avr/io.h>
#include <avr/interrupt.h>
#include "TIMER1.h"

/* Global variable to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

//Initialize Timer1
void TIMER1_Init(const Timer1_ConfigType *Config_Ptr) {
//	TCCR1A:
//	Non PWM mode : set FOC1A & set FOC1B
//	Normal comp mode : clear COM1A0 , COM1A1 , COM1B0 , COM1B1
//	Normal mode : Clear WGM10 & WGM11 & WGM12 & WGM13
//	Compare mode: Clear WGM10 & WGM11 & WGM13
//`					& set WGM12
//we will make WGM10 & WGM11 = 0
	TCCR1A |= (1 << FOC1A) | (1<<FOC1B);

//	TCCR1B:
//	Normal mode : Clear WGM10 & WGM11 & WGM12 & WGM13
//	Compare mode: Clear WGM10 & WGM11 & WGM13
//`					& set WGM12
//	PRESCALAR = change CS10 , CS12 & CS11 "First three bits"
	TCCR1B |= (Config_Ptr -> prescaler) | ((Config_Ptr -> mode) << WGM12);

	//if normal mode
	if(Config_Ptr -> mode == NormalMode){
		//initial value
		TCNT1 = Config_Ptr -> initial_value;
		//Overflow Interrupt Enable
		TIMSK |= (1 << TOIE1);
	}

	//if compare mode
	if(Config_Ptr -> mode == CompareMode){
		//COMPARE VALUE
		OCR1A = Config_Ptr -> compare_value;
		//Output Compare A Match Interrupt Enable
		TIMSK |= (1 << OCIE1A);
	}
}


/*
 * Description: Function to disable the Timer1
 */
void Timer1_deInit(void) {
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	TIMSK = 0;
}

//Function to set CallBack function
void Timer1_setCallBack(void (*a_ptr)(void)) {
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application
		 * after compare is reached */
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application
		 * after overflow  */
		(*g_callBackPtr)();
	}
}
