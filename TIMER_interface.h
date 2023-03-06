#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TIMER_U8_OVF_INT         0
#define TIMER_U8_CTC_INT         1


void TIMER0_voidInit(void);

u8 TIMER0_U8SetCallBack(u8 Copy_U8IntType, void(*Copy_pvCallBackFunc)(void));

#endif
