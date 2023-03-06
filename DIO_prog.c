#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"Error_Types.h"

#include"DIO_interface.h"
#include"DIO_private.h"
#include"DIO_reg.h"
#include"DIO_config.h"

/*
u8 DIO_U8SetPinDirection(u8 Copy_U8Port,u8 Copy_U8PinNumber,u8 Copy_U8Direction){
	u8 Local_U8_ErrorState=OK;

	if(Copy_U8PinNumber<=DIO_U8_PIN7){

   if(Copy_U8Direction==DIO_U8_PIN_INPUT){

	   switch(Copy_U8Port){
	   case DIO_U8_PORTA: CLR_BIT(DDRA,Copy_U8PinNumber);  break;
	   case DIO_U8_PORTB: CLR_BIT(DDRB,Copy_U8PinNumber);  break;
	   case DIO_U8_PORTC: CLR_BIT(DDRC,Copy_U8PinNumber);  break;
	   case DIO_U8_PORTD: CLR_BIT(DDRD,Copy_U8PinNumber);  break;
	   default:Local_U8_ErrorState=NOK;                    break;
	   }
   }
   else if(Copy_U8Direction==DIO_U8_PIN_OUTPUT){

	   switch(Copy_U8Port){
	   	   case DIO_U8_PORTA: SET_BIT(DDRA,Copy_U8PinNumber);   break;
	   	   case DIO_U8_PORTB: SET_BIT(DDRB,Copy_U8PinNumber);   break;
	   	   case DIO_U8_PORTC: SET_BIT(DDRC,Copy_U8PinNumber);   break;
	   	   case DIO_U8_PORTD: SET_BIT(DDRD,Copy_U8PinNumber);   break;
	   	   default:Local_U8_ErrorState=NOK;                     break;
	   }

   }


   else{

	   Local_U8_ErrorState=NOK;  // Error Direction//

       }

	}
   else{

		Local_U8_ErrorState=NOK;   //Error Pin Number//

	}

	return Local_U8_ErrorState;
}
u8 DIO_U8SetPortDirection(u8 Copy_U8Port,u8 Copy_U8Direction){
	
	u8 Local_U8_ErrorState=OK;

	switch(Copy_U8Port){

	case DIO_U8_PORTA: DDRA=Copy_U8Direction;  break;
	case DIO_U8_PORTB: DDRB=Copy_U8Direction;  break;
	case DIO_U8_PORTC: DDRC=Copy_U8Direction;  break;
	case DIO_U8_PORTD: DDRD=Copy_U8Direction;  break;
	default: Local_U8_ErrorState=NOK;          break;
	}

	return Local_U8_ErrorState;
}

*/
u8 DIO_U8SetPinValue(u8 Copy_U8Port,u8 Copy_U8PinNumber,u8 Copy_U8Value){
	u8 Local_U8_ErrorState=OK;

		if(Copy_U8PinNumber<=DIO_U8_PIN7){

	   if(Copy_U8Value==DIO_U8_PIN_LOW){

		   switch(Copy_U8Port){
		   case DIO_U8_PORTA:  CLR_BIT(PORTA,Copy_U8PinNumber);  break;
		   case DIO_U8_PORTB:  CLR_BIT(PORTB,Copy_U8PinNumber);  break;
		   case DIO_U8_PORTC:  CLR_BIT(PORTC,Copy_U8PinNumber);  break;
		   case DIO_U8_PORTD:  CLR_BIT(PORTD,Copy_U8PinNumber);  break;
		   default:Local_U8_ErrorState=NOK;                     break;
		   }
	   }
	   else if(Copy_U8Value==DIO_U8_PIN_HIGH){

		   switch(Copy_U8Port){
		   	   case DIO_U8_PORTA: SET_BIT(PORTA,Copy_U8PinNumber);   break;
		   	   case DIO_U8_PORTB: SET_BIT(PORTB,Copy_U8PinNumber);   break;
		   	   case DIO_U8_PORTC: SET_BIT(PORTC,Copy_U8PinNumber);   break;
		   	   case DIO_U8_PORTD: SET_BIT(PORTD,Copy_U8PinNumber);   break;
		   	   default:Local_U8_ErrorState=NOK;                      break;
		   }

	   }


	   else{

		   Local_U8_ErrorState=NOK;  // Error Value//

	       }

		}
	   else{

			Local_U8_ErrorState=NOK;   //Error Pin Number//

		}

		return Local_U8_ErrorState;
}
u8 DIO_U8SetPortValue(u8 Copy_U8Port,u8 Copy_U8Value){
	
	u8 Local_U8_ErrorState=OK;

		switch(Copy_U8Port){

		case DIO_U8_PORTA : PORTA = Copy_U8Value;      break;
		case DIO_U8_PORTB : PORTB = Copy_U8Value;      break;
		case DIO_U8_PORTC : PORTC = Copy_U8Value;      break;
		case DIO_U8_PORTD : PORTD = Copy_U8Value;      break;
		default: Local_U8_ErrorState=NOK;           break;
		}

		return Local_U8_ErrorState;
}
u8 DIO_U8GetPinValue(u8 Copy_U8Port,u8 Copy_U8PinNumber,u8* Copy_PU8Value){
  u8 Local_U8_ErrorState=OK;

  if(Copy_U8PinNumber<=DIO_U8_PIN7){

  	   switch(Copy_U8Port){
  	   case DIO_U8_PORTA: *Copy_PU8Value=GET_BIT(DIO_U8_PORTA,Copy_U8PinNumber);  break;
  	   case DIO_U8_PORTB: *Copy_PU8Value=GET_BIT(DIO_U8_PORTB,Copy_U8PinNumber);  break;
  	   case DIO_U8_PORTC: *Copy_PU8Value=GET_BIT(DIO_U8_PORTC,Copy_U8PinNumber);  break;
  	   case DIO_U8_PORTD: *Copy_PU8Value=GET_BIT(DIO_U8_PORTD,Copy_U8PinNumber);  break;
  	   default:Local_U8_ErrorState=NOK;                    break;
  	   }
  }
  	   else{

  		 Local_U8_ErrorState=NOK;
  	   }

  return Local_U8_ErrorState;
}
