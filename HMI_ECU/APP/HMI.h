#ifndef APP_HMI_H_
#define APP_HMI_H_

#define MATCH 2
#define FAILED 1


#include "../HAL/keypad.h"
#include "../HAL/lcd.h"
#include "../MCAL/uart.h"
#include "../CommonHeader-UsedFiles/std_types.h"
#include "../HAL/keypad.h"
#include <util/delay.h> /* For the delay functions */

uint8 pass[5];
uint8 pass2[5];

//Function to increase the global seconds variable
void CountSeconds(void);

//saving the password in an array
//displaying * as it is an pass
//adjusting the enter value(=) & the numbers pressed in the keypad
void Password_adjust(uint8 *pass_temp);

//Entering pass sequence "Display"
void EnterPass_Sequence(void);


//Function perform as the password is matched or not matched
//function parameters -> another function
//							as to :
//								1)call the Door_Squence function
//								2)call the EnterPass function
void PassWrong_case(void(*func)(void));

//Send pass to control_ecu through UART
void SendPass(uint8 *pass);

//Send pass2 to control_ecu through UART
void SendPass2(uint8 *pass2);

//function that counts the sec by :
//causing an interrupt every second
void DelaySeconds(uint8 sec);

//Pass Entering
//if the two passes are not the same -> then stay in the loop
//until the user enters the same two passes
void EnterPass(void);

//Send the key entered by the user through UART
void SendKey(void);

//Door Sequence "Display"
void Door_Sequence(void);

void UART_Configurations(void);

//fy approach tany andaf mn al polling al t3ban da
//momken ne3melo be timer0 aw timer2
// bas msh mestahla bsra7a :D
void Polling_one_minute(void);

#endif /* APP_HMI_H_ */
