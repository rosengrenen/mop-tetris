#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "delay.h"
#include "types.h"

#define GPIO_E 0x40021000
#define GPIO_MODER ((volatile unsigned int *) (GPIO_E))
#define GPIO_OTYPER ((volatile unsigned short *) (GPIO_E+0x4))
#define GPIO_PUPDR ((volatile unsigned int *) (GPIO_E+0xC))
#define GPIO_IDR_LOW ((volatile unsigned char *) (GPIO_E+0x10))
#define GPIO_IDR_HIGH ((volatile unsigned char *) (GPIO_E+0x11))
#define GPIO_ODR_LOW ((volatile unsigned char *) (GPIO_E+0x14))
#define GPIO_ODR_HIGH ((volatile unsigned char *) (GPIO_E+0x15))

#define B_RS        0x1
#define B_RW        0x2
#define B_SELECT    0x4
#define B_CS1       0x8
#define B_CS2       0x10
#define B_RST       0x20
#define B_E         0x40

#define LCD_ON          0x3F
#define LCD_OFF         0x3E
#define LCD_SET_ADD     0x40
#define LCD_SET_PAGE    0xB8
#define LCD_DISP_START  0xC0
#define LCD_BUSY        0x80

void graphic_init();
void graphic_clear_screen();
void graphic_pixel(uint8_t x, uint8_t y, uint8_t set);
void graphic_swap();

#endif // GRAPHICS_H
