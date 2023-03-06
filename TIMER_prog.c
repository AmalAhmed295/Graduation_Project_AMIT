#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Error_types.h"

#include"TIMER_interface.h"
#include"TIMER_private.h"
#include"TIMER_config.h"
#include"TIMER_reg.h"

static void (*TIMER0_pvOVFCallBackFunc)(void)= NULL;
static void (*TIMER0_pvCTCCallBackFunc)(void)= NULL;

void TIMER0_voidInit(void){

	/* set CTC mode */
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/* Set prescaler : division by 64 */
	TCCR0 &= 0b11111000;
	TCCR0 |= 3;

	/* set compare value =250 */
	OCR0=250;

	/* compare match interrupt enable */
	SET_BIT(TIMSK,TIMSK_OCIE0);

}

u8 TIMER0_U8SetCallBack(u8 Copy_U8IntType, void(*Copy_pvCallBackFunc)(void)){

	u8 Local_U8ErrorState = OK;

	if(Copy_pvCallBackFunc != NULL ){

		if(Copy_U8IntType == TIMER_U8_OVF_INT )
		{
			TIMER0_pvOVFCallBackFunc = Copy_pvCallBackFunc;
		}
		else if(Copy_U8IntType == TIMER_U8_CTC_INT)
		{
			TIMER0_pvCTCCallBackFunc = Copy_pvCallBackFunc;
		}
		else
		{
			Local_U8ErrorState = NOK;
		}
	}

	else
	{
		Local_U8ErrorState = NULL_PONTER;
	}

	return Local_U8ErrorState;
}

    /* Timer0 CTC ISR*/

void __vector_10 (void)  __attribute__((signal));
void __vector_10 (void){

	if(TIMER0_pvCTCCallBackFunc != NULL)
	{
		TIMER0_pvCTCCallBackFunc();
	}
	else
	{
		/* do nothing */
	}

}




