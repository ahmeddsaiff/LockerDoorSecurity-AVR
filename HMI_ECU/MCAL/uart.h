 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../CommonHeader-UsedFiles/std_types.h"

typedef enum{
	Bits_Data_5,Bits_Data_6,Bits_Data_7,Bits_Data_8
}UART_BitData;

typedef enum{
	disabled,Even_Parity=2,Odd_Parity=3
}UART_Parity;

typedef enum{
	Bits_Stop_1,Bits_Stop_2
}UART_StopBit;

typedef enum{
	RATE_2400=2400,
	RATE_4800=4800,
	RATE_9600=9600,
	RATE_14_4K=14400,
	RATE_19_2K=19200,
	RATE_28_8K=28800,
	RATE_38_4K=38400,
	RATE_57_6K=57600,
	RATE_76_8K=76800,
	RATE_115_2K=115200,
	RATE_230_4K=230400,
	RATE_250K=250000,
	RATE_500K=500000,
	RATE_1M=1000000,
}UART_BaudRate;


typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
