#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Error_Types.h"

#include"UART_interface.h"
#include"UART_private.h"
#include"UART_reg.h"
#include"UART_config.h"


void UART_VoidInit(void)
{

	u8 Local_U8UCSRCVal=0;

	/* set bit 7 for UCSRC register select  */
	SET_BIT(Local_U8UCSRCVal,UCSRC_URSEL);

	/* 8 data bits character size */
	SET_BIT(Local_U8UCSRCVal,UCSRC_UCSZ0);
	SET_BIT(Local_U8UCSRCVal,UCSRC_UCSZ1);

	/* send the value to the register*/
	UCSRC= Local_U8UCSRCVal;

	/* 9600 bps on system freq 16MHZ*/
	UBRRL= 103;

	    /* Receiver Enable */
	SET_BIT(UCSRB,UCSRB_RXEN);
	
	   /* Transmitter Enable */
	SET_BIT(UCSRB,UCSRB_TXEN);

}
void UART_VoidSendChar(u8 Copy_U8Char)
{
	
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR= Copy_U8Char;

}
u8 UART_U8ReceiveChar(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
	
}
