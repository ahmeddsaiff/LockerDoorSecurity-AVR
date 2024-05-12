#ifndef MCAL_TIMER1_H_
#define MCAL_TIMER1_H_

#include "../CommonHeader-UsedFiles/std_types.h"

typedef  enum {
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,External_clk_PinT1_FallingEdge,External_clk_PinT1_RisingEdge
}Timer1_Prescaler;

typedef  enum {
	NormalMode,CompareMode
}Timer1_Mode;

typedef struct {
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

//Initialize Timer1
void TIMER1_Init(const Timer1_ConfigType * Config_Ptr);

//Disable Timer1
void Timer1_deInit(void);

//Function to set CallBack function
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* MCAL_TIMER1_H_ */
