#ifndef DELAY_H
#define DELAY_H

#include "types.h"

#define SYSTEM_TIMER 0xE000E010
#define STK_CTRL ((volatile unsigned long *) (SYSTEM_TIMER))
#define STK_LOAD ((volatile unsigned long *) (SYSTEM_TIMER+0x4))
#define STK_VAL ((volatile unsigned long *) (SYSTEM_TIMER+0x8))

void delay_500ns(void);
void delay_micro(unsigned int us);
void delay_milli(unsigned int ms);

#endif // DELAY_H
