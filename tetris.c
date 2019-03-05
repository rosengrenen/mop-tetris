#include "tetris.h"

#include "field.h"
#include "graphics.h"
#include "keyboard.h"
#include "shape.h"
#include "types.h"

#include "random.h"

void tetris_run();

uint8_t running = 0;

FIELD field = {
	{},
	field_set_tile,
	field_unset_tile,
	field_get_tile,
	field_draw
};

SHAPE shape;

void tetris_init()
{
    keyb_init();
    graphic_init();
    //graphic_clear_screen();
    //ascii_init();
}

void tetris_start()
{
	if (running)
	{
		return;
	}
	
	tetris_run();
}

void tetris_stop()
{
	if (running)
	{
		running = 0;
	}
}

void tetris_run()
{
	running = 1;
	
	shape.geometry = random_geometry();
	shape.position.x = 0;
	shape.position.y = 0;
	
	for (uint32_t i = 0; i < 8; ++i)
	{
		field.set_tile(&field, i, 15);
	}
	
	field.set_tile(&field, 3, 14);	
	field.set_tile(&field, 7, 14);

	while (running)
	{
		field.draw(&field);
		shape.draw(&shape);
		graphic_swap();
	}
}