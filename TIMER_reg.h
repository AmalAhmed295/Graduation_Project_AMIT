#ifndef TIMER_REG_H_
#define TIMER_REG_H_

#define TCCR0           *((volatile u8*)0x53)
#define TCCR0_WGM00        6
#define TCCR0_WGM01        3

#define TCNT0           *((volatile u8*)0x52)

#define OCR0             *((volatile u8*)0x5C)

#define TIMSK           *((volatile u8*)0x59)
#define TIMSK_TOIE0        0
#define TIMSK_OCIE0        1

#define TCCR1A          *((volatile u8*)0x4F)
#define TCCR1A_COM1A1      7
#define TCCR1A_COM1A0      6
#define TCCR1A_WGM11       1
#define TCCR1A_WGM10       0

#define TCCR1B          *((volatile u8*)0x4E)
#define TCCR1B_WGM13       4
#define TCCR1B_WGM12       3
#define TCCR1B_CS12        2
#define TCCR1B_CS11        1
#define TCCR1B_CS10        0


#define OCR1A            *((volatile u8*)0x4A)

#define ICR1             *((volatile u8*)0x46)

#endif
