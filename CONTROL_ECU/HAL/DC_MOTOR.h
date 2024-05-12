#include "../CommonHeader-UsedFiles/std_types.h"

#ifndef HAL_DC_MOTOR_H_
#define HAL_DC_MOTOR_H_


typedef enum{
	 STOP , CW , A_CW
}DcMotor_State;

//setup direction for the two motor pins
//stop the DC_Motor at the beginning
void DcMotor_init(void);

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* HAL_DC_MOTOR_H_ */
