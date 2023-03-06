/*
 * main.c
 *
 *  Created on: Feb 22, 2023
 *      Author: Administrator
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"UART_interface.h"
#include"PORT_interface.h"
#include"DIO_interface.h"

void main(void)
{

	u8 Local_U8SendedChar;

	UART_VoidInit();

	while(1){
		Local_U8SendedChar = DIO_U8GetPinValue(DIO_U8_PORTD,DIO_U8_PIN2,DIO_U8_PIN_HIGH);
		UART_VoidSendChar(Local_U8SendedChar);

	}
}


