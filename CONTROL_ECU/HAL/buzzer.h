#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_


#include "../MCAL/GPIO.h"
#include "../CommonHeader-UsedFiles/common_macros.h"
#include "../CommonHeader-UsedFiles/std_types.h"

#define BUZZER_PIN_ID PIN4_ID
#define BUZZER_PORT_ID PORTA_ID
#define BUZZER_PORT PORTA


void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);



#endif /* HAL_BUZZER_H_ */
