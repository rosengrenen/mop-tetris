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
#include "types.h"

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
    for (uint32_t i = 0; i < FIELD_BLOCK_SIZE; ++i)
    {
        for (uint32_t j = 0; j < FIELD_BLOCK_SIZE; ++j)
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

typedef struct tPoint
{
    uint8_t x, y;
} POINT;

typedef struct tShape
{
    int32_t size;
    POINT points[4];
} SHAPE, *PSHAPE;

typedef struct tMoveableShape
{
    SHAPE shape;
    uint8_t pos_x, pos_y;
} MOVABLESHAPE;

void render_shape(MOVABLESHAPE* shape)
{
    for (uint8_t i = 0; i < 4; ++i)
    {
        render_block(shape->pos_x + shape->shape.points[i].x,
                     shape->pos_y + shape->shape.points[i].y);
    }
}

SHAPE o_shape = {
    2,
    {
        { 0, 0 }, { 1, 0 },
        { 0, 1 }, { 1, 1 }
    }
};

SHAPE i_shape = {
    4,
    {
        { 1, 0 },
        { 1, 1 }, 
        { 1, 2 },
        { 1, 3 }
    }
};

SHAPE s_shape = {
    3,
    {
                  { 1, 0 }, { 2, 0 },
        { 0, 1 }, { 1, 1 }, 
    }
};

SHAPE z_shape = {
    3,
    {
        { 0, 0 }, { 1, 0 },
                  { 1, 1 }, { 2, 1 }
    }
};

SHAPE l_shape = {
    3,
    {
        { 0, 0 },
        { 0, 1 }, 
        { 0, 2 }, { 1, 2 }
    }
};

SHAPE j_shape = {
    3,
    {
                  { 1, 0 },
                  { 1, 1 }, 
        { 0, 2 }, { 1, 2 }
    }
};

SHAPE t_shape = {
    3,
    {
        { 0, 1 }, { 1, 1 }, { 2, 1 },
                  { 1, 2 }
    }
};

int main()
{
    app_init();

    PSHAPE shapes[7] = {
        &o_shape,
        &i_shape,
        &s_shape,
        &z_shape,
        &l_shape,
        &j_shape,
        &t_shape
    };

    MOVABLESHAPE sh = {
        *shapes[3],
        0, 0
    };

    while (1)
    {
        switch (keyb()) {
            case 8:
                sh.pos_y++;
                break;
            case 2:
                sh.pos_y--;
                break;
            case 4:
                sh.pos_x--;
                break;
            case 6:
                sh.pos_x++;
                break;
        }
        field_render();
        render_shape(&sh);
        graphic_swap();
    }
}

