#include "delay.h"

void delay_500ns(void)
{
    *STK_CTRL = 0;
    uint32_t count_value = (168 / 2) - 1;
    *STK_LOAD = count_value;
    *STK_VAL = 0;
    *STK_CTRL = 5;
    while (1)
    {
        if (*STK_CTRL & 0x10000)
        {
            *STK_CTRL = 0;
            break;
        }
    }
}

void delay_micro(uint32_t us)
{
    for (uint32_t i = 0; i < us; ++i)
    {
        delay_500ns();
        delay_500ns();
    }
}

void delay_milli(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; ++i)
    {
#ifdef SIMULATOR
        delay_micro(1);
#else
        delay_micro(1000);
#endif
    }
}
