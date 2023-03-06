#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_U8_PORTA        1
#define DIO_U8_PORTB        2
#define DIO_U8_PORTC        3
#define DIO_U8_PORTD        4

#define DIO_U8_PIN0         0
#define DIO_U8_PIN1         1
#define DIO_U8_PIN2         2
#define DIO_U8_PIN3         3
#define DIO_U8_PIN4         4
#define DIO_U8_PIN5         5
#define DIO_U8_PIN6         6
#define DIO_U8_PIN7         7

#define DIO_U8_PIN_INPUT       0
#define DIO_U8_PIN_OUTPUT      1

#define DIO_U8_PIN_LOW       0
#define DIO_U8_PIN_HIGH      1

//u8 DIO_U8SetPinDirection(u8 Copy_U8Port,u8 Copy_U8PinNumber,u8 Copy_U8Direction);
//u8 DIO_U8SetPortDirection(u8 Copy_U8Port,u8 Copy_U8Direction);
u8 DIO_U8SetPinValue(u8 Copy_U8Port,u8 Copy_U8PinNumber,u8 Copy_U8Value);
u8 DIO_U8SetPortValue(u8 Copy_U8Port,u8 Copy_U8Value);
u8 DIO_U8GetPinValue(u8 Copy_U8Port,u8 Copy_U8PinNumber,u8* Copy_PU8Value);

#endif
