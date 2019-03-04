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
asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	".L1: B .L1\n"				/* never return */
	) ;
}

#include "graphics.h"
#include "keyboard.h"

void app_init()
{
    keyb_init();
    graphic_init();
    //graphic_clear_screen();
    //ascii_init();
}

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 16
#define FIELD_BLOCK_SIZE (64 / FIELD_WIDTH)
void render_block(int x, int y)
{
    for (unsigned int i = 0; i < FIELD_BLOCK_SIZE; ++i)
    {
        for (unsigned int j = 0; j < FIELD_BLOCK_SIZE; ++j)
        {
            graphic_pixel(y * FIELD_BLOCK_SIZE + i, (FIELD_BLOCK_SIZE - 1 - x) * FIELD_BLOCK_SIZE + j, 1);
        }
    }
}

char field[8 * 16];

void field_set_block(int x, int y)
{
    field[y * FIELD_WIDTH + x] = 1;
}

void field_unset_block(int x, int y)
{
    field[y * FIELD_WIDTH + x] = 0;
}

char field_get_block(int x, int y)
{
    return field[y * FIELD_WIDTH + x];
}

void field_render()
{
    for (unsigned int x = 0; x < FIELD_WIDTH; ++x)
    {
        for (unsigned int y = 0; y < FIELD_HEIGHT; ++y)
        {
            if (field_get_block(x, y))
            {
                render_block(x, y);
            }
        }
    }
}


int main()
{
    app_init();
    field_set_block(0, 0);    
    field_set_block(5, 0);

    while (1)
    {
        field_render();
        graphic_swap();
    }
}

