#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Error_Types.h"
#include<util/delay.h>

#include"DIO_interface.h"
#include"PORT_interface.h"
#include"TIMER_interface.h"
#include"GIE_interface.h"

#include"GLCD_interface.h"
#include"GLCD_private.h"
#include"GLCD_config.h"

static void SendEnablePulse(void){
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_E_PIN,DIO_U8_PIN_HIGH);
	_delay_ms(2);
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_E_PIN,DIO_U8_PIN_LOW);
}


void GLCD_voidInit(void){

	/* display on off instruction */
	GLCD_VoidSendCommand(0b00111111);

	/* to activate display on both halves */
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS1_PIN,DIO_U8_PIN_HIGH);
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS2_PIN,DIO_U8_PIN_HIGH);

	/* to select the instruction mode */
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RS_PIN,DIO_U8_PIN_LOW);
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RW_PIN,DIO_U8_PIN_LOW);

	/* Enable */
	SendEnablePulse();

}
void GLCD_VoidSendCommand(u8 Copy_U8Command){


	/********** send the command to the lcd on data port*********/
	DIO_U8SetPortValue(GLCD_U8_DATA_PORT,Copy_U8Command);

	/**** set RS pin to low for command******/
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RS_PIN,DIO_U8_PIN_LOW);

	/**** set RW pin to low to write******/
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RW_PIN,DIO_U8_PIN_LOW);

	/*********send enable pulse***********************/
	SendEnablePulse();

}
void GLCD_VoidSendData(u8 Copy_U8Data){

	/********** send the data to the lcd on data port*********/
	DIO_U8SetPortValue(GLCD_U8_DATA_PORT,Copy_U8Data);

	/**** set RS pin to low for data******/
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RS_PIN,DIO_U8_PIN_HIGH);

	/**** set RW pin to low to write******/
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RW_PIN,DIO_U8_PIN_LOW);

	/*********send enable pulse***********************/
	SendEnablePulse();

}

u8 GLCD_U8SendString(const s8* Copy_pchString){
	u8 Local_U8ErrorState = OK;
	u8 Local_U8Counter=0;

	if(Copy_pchString != NULL){

		while(Copy_pchString[Local_U8Counter]!= '\0')
		{
			GLCD_VoidSendData(Copy_pchString[Local_U8Counter]);
			Local_U8Counter++;
		}
	}
	else{
		Local_U8ErrorState = NULL_PONTER;
	}
	return Local_U8ErrorState;
}

u8 GLCD_U8PageSelection(u8 Copy_U8Page){

	u8 Local_U8ErrorState= OK;

	/* to activate display on both halves */
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS1_PIN,DIO_U8_PIN_HIGH);
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS2_PIN,DIO_U8_PIN_HIGH);

	/* to select the instruction mode */
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RS_PIN,DIO_U8_PIN_LOW);
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RW_PIN,DIO_U8_PIN_LOW);

	if(Copy_U8Page < 8){
		/* set page */
		switch(Copy_U8Page)
		{
		case GLCD_U8_PAGE_0 : GLCD_VoidSendCommand(0b10111000); break;
		case GLCD_U8_PAGE_1 : GLCD_VoidSendCommand(0b10111001); break;
		case GLCD_U8_PAGE_2 : GLCD_VoidSendCommand(0b10111010); break;
		case GLCD_U8_PAGE_3 : GLCD_VoidSendCommand(0b10111011); break;
		case GLCD_U8_PAGE_4 : GLCD_VoidSendCommand(0b10111100); break;
		case GLCD_U8_PAGE_5 : GLCD_VoidSendCommand(0b10111101); break;
		case GLCD_U8_PAGE_6 : GLCD_VoidSendCommand(0b10111110); break;
		case GLCD_U8_PAGE_7 : GLCD_VoidSendCommand(0b10111111); break;
		default: Local_U8ErrorState = NOK;                      break;
		}

		SendEnablePulse();
	}
	else
	{
		Local_U8ErrorState = NOK;
	}

	return Local_U8ErrorState;
}

u8 GLCD_U8ColumnSelection(u8 Copy_U8Column){

	u8 Local_U8ErrorState= OK;

	if(Copy_U8Column < 128)
	{
		if(Copy_U8Column < 64)
		{
			DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS1_PIN,DIO_U8_PIN_HIGH);
			DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS2_PIN,DIO_U8_PIN_LOW);
		}
		else if(Copy_U8Column > 63)
		{
			DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS1_PIN,DIO_U8_PIN_LOW);
			DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS2_PIN,DIO_U8_PIN_HIGH);
		}
		else
		{
			Local_U8ErrorState = NOK;
		}
	}
	else
	{
		Local_U8ErrorState = NOK;
	}
	/* to select the instruction mode */
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RS_PIN,DIO_U8_PIN_LOW);
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_RW_PIN,DIO_U8_PIN_LOW);

	SendEnablePulse();

	return Local_U8ErrorState;
}
void GLCD_voidSendNumber(u32 Copy_U32Number)
{

	u32 Local_U32Reserved = 1;
	if(Copy_U32Number == 0)
	{
		GLCD_VoidSendData('0');
		return;
	}
	/* reverse the number */
	while(Copy_U32Number != 0)
	{
		/* get the right most digit */
		Local_U32Reserved = Local_U32Reserved*10 + Copy_U32Number % 10 ;

		/* get rid of the right most digit */
		Copy_U32Number = 10;
	}
	do
	{
		/* display the right most digit with converting its value to ASCII */
		GLCD_VoidSendData((Local_U32Reserved%10)+'0');
		/* get rid of the right most digit */
		Local_U32Reserved/=10;

	}
	while (Local_U32Reserved != 1);

}
void GLCD_VoidClearAll(void)
{
	u8 i;     /* page number*/
	u8 j;     /*column number*/
	u8 Local_U8TotalPage = 8;
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS1_PIN,DIO_U8_PIN_HIGH);
	DIO_U8SetPinValue(GLCD_U8_CNTRL_PORT,GLCD_U8_CS2_PIN,DIO_U8_PIN_HIGH);

	for(i=0; i<Local_U8TotalPage; i++)
	{
		GLCD_U8PageSelection(i);
		for(j=0; j<128 ; j++)
		{
			GLCD_U8ColumnSelection(j);
			GLCD_VoidSendData(0);
		}
		GLCD_U8PageSelection(0);
		GLCD_U8ColumnSelection(0);
	}

}
u8 GLCD_V_Line(u8 Copy_U8StartPage, u8 Copy_U8EndPage, u8 Copy_U8Col)
{
	u8 Local_U8ErrorState = OK;

	if((Copy_U8Col<128) && (Copy_U8StartPage < 8) && (Copy_U8EndPage < 8))
	{
		GLCD_U8PageSelection(Copy_U8StartPage);
		GLCD_U8ColumnSelection(Copy_U8Col);
		GLCD_U8SendString("........");
		GLCD_U8PageSelection(Copy_U8EndPage);

	}
	else
	{
		Local_U8ErrorState= NOK;
	}


	return Local_U8ErrorState;
}
u8 GLCD_H_Line(u8 Copy_U8StartCol, u8 Copy_U8EndCol, u8 Copy_U8Page)
{
	u8 Local_U8ErrorState = OK;

	if((Copy_U8StartCol<128) && (Copy_U8EndCol<128) && (Copy_U8Page <8))
	{
		GLCD_U8PageSelection(Copy_U8Page);
		GLCD_U8ColumnSelection(Copy_U8StartCol);
        GLCD_U8SendString("........");
		GLCD_U8ColumnSelection(Copy_U8EndCol);

	}

	else
	{
		Local_U8ErrorState= NOK;
	}

	return Local_U8ErrorState;
}
