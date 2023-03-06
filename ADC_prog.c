#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Error_Types.h"

#include"ADC_interface.h"
#include"ADC_private.h"
#include"ADC_config.h"
#include"ADC_reg.h"

/* global variable to hold ADC asynchronous digital result */
static u16 ADC_pu16Result = NULL;
/* global variable to hold the ADC asynchronous function */
static void(*ADC_pvNotificationFunc)(void) = NULL;

static u8 ADC_U8BusyFlag = IDLE;


void ADC_voidInit(void){
	/*Set AREF as ref Volt*/
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);


#if ADC_U8_RESOLUTION == EIGHT_BIT
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_U8_RESOLUTION == TEN_BIT
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "Wrong ADC_U8_RESOLUTION option"
#endif
	/*Activate left adjust result for 8 bit resolution*/
	SET_BIT(ADMUX,ADMUX_ADLAR);

	/* setting prescaler */
	ADCSRA &= 0b1111000;
	ADCSRA |= ADC_U8_PRESCALER;

	/*ADC enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

u8 ADC_U8StartConversionSynch(u8 Copy_U8Channel, u16* Copy_pu16Result){

	u8 Local_U8ErrorState = OK;
	u32 Local_U32Counter=0;

	if(Copy_pu16Result != NULL){
		/* check ADC is idle */
		if (ADC_U8BusyFlag == IDLE)
		{
			/* ADC is now busy*/
			ADC_U8BusyFlag == BUSY;

			/* set channel */
			ADMUX &= 0b11100000;
			ADMUX |= Copy_U8Channel;

			/* start conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/* busy waiting on (polling) on the conversion complete flag as long as timeout has not passed*/
			while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0) && (Local_U32Counter != ADC_U32_TIMEOUT)){

				Local_U32Counter++;

			}

			/* check about the reason why the loop has finished */
			if(Local_U32Counter == ADC_U32_TIMEOUT){
				Local_U8ErrorState = TIMEOUT_Err ;
			}
			else
			{
				/* the loop is finished because conversion complete flag is raised */
				/* clear the flag */
				SET_BIT(ADCSRA,ADCSRA_ADIF);

				/* return the data */
#if ADC_U8_RESOLUTION == EIGHT_BIT
				*Copy_pu16Result = ADCH;
#elif ADC_U8_RESOLUTION == TEN_BIT
				*Copy_pu16Result = ADC;
#endif
			}
			/* ADC is now IDLE */
			ADC_U8BusyFlag == IDLE;
		}
		else
		{
			Local_U8ErrorState = BUSY_Err;
		}
	}
	else{
		Local_U8ErrorState = NULL_PONTER;
	}

	return Local_U8ErrorState;
}
u8 ADC_U8StartConversionAsynch(u8 Copy_U8Channel, u16* Copy_pu16Result,void(*Copy_pvNotificationFunc)(void)){

	u8 Local_U8ErrorState = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if (ADC_U8BusyFlag == IDLE)
		{
			/* ADC is now BUSY */
			ADC_U8BusyFlag = BUSY;

			/* initialize the ADC result pointer globally */
			ADC_pu16Result = *Copy_pu16Result;

			/*initialize the ADC notification function pointer globally*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/* set channel */
			ADMUX &= 0b11100000;
			ADMUX |= Copy_U8Channel;

			/* start conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/* ADC conversion complete interrupt enable */
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_U8ErrorState = BUSY_Err;
		}
	}
	else
	{

		Local_U8ErrorState = NULL_PONTER;

	}



	return Local_U8ErrorState;
}

/* ADC ASR*/
void __vector_16 (void)            __attribute__((signal));
void __vector_16 (void)
{
#if ADC_U8_RESOLUTION == EIGHT_BIT
	ADC_pu16Result = ADCH;
#elif ADC_U8_RESOLUTION == TEN_BIT
	*ADC_pu16Result = ADC;
#endif

	/* ADC conversion complete interrupt disable */
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

	/* ADC is now IDLE */
	ADC_U8BusyFlag = IDLE;

	/* invoke the call back notification function */
	if (ADC_pvNotificationFunc != NULL)
	{
		ADC_pvNotificationFunc();
	}
	else{
		/* do nothing */
	}

}


