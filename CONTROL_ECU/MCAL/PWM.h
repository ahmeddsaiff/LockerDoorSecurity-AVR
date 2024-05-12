/*
 * PWM.h
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */

#ifndef MCAL_PWM_H_
#define MCAL_PWM_H_

#include "../CommonHeader-UsedFiles/std_types.h"
/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Duty Cycle can be changed by updating the value
 * in The Compare Register
 */
void Timer0_PWM_Init(uint8 set_duty_cycle);



#endif /* MCAL_PWM_H_ */
