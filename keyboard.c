#include "keyboard.h"

void keyb_init(void)
{
    *GPIO_D_MODER = 0x55005555;
    *GPIO_D_OTYPER &= 0x00FF;
    *GPIO_D_OTYPER |= 0x0F00;
    *GPIO_D_PUPDR &= 0x0000FFFF;
    *GPIO_D_PUPDR |= 0x00AA0000;
}

unsigned char key_values[16] = {
    1, 2, 3, 10,
    4, 5, 6, 11,
    7, 8, 9, 12,
    14, 0, 15, 13
};

void activate_row(unsigned char row) 
{
    *GPIO_D_ODR_HIGH = (1 << (4 + row));
}

unsigned char read_column()
{
    unsigned char input = *GPIO_D_IDR_HIGH & 0x0F;
    if (input & 0x1) 
    {
        return 1;
    }
    else if (input & 0x2)
    {
        return 2;
    }
    else if (input & 0x4)
    {
        return 3;
    }
    else if (input & 0x8)
    {
        return 4;
    }
    return 0;
}

unsigned char keyb(void)
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        activate_row(i);
        unsigned char column = read_column();
        
        if (column != 0)
        {
            unsigned char key = key_values[i * 4 + (column - 1)];
            return key;
        }
    }
    return 0xFF;
}