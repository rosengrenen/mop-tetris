/*
 * 	startup.c
 *
 */
void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );

/**
 * Grafik
 * Ascii
 * Keyboard
 * Delay
 */
 
void startup ( void )
{
__asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	".L1: B .L1\n"				/* never return */
	) ;
}

#include "tetris.h"

int main()
{
#ifdef USBDM
	*((unsigned long *)0x40023830) = 0x18;
	__asm volatile(" LDR R0,=0x08000209\n BLX R0\n");
#endif
    tetris_init();
	tetris_start();
}

