#include "tetris.h"

#include "field.h"
#include "graphics.h"
#include "keyboard.h"
#include "shape.h"
#include "types.h"

#include "random.h"

#define MOVE_LEFT 4
#define MOVE_RIGHT 6
#define ROTATE_CLOCKWISE 3
#define ROTATE_ANTICLOCKWISE 1
#define DROP 5

void tetris_run();

uint8_t running = 0;

FIELD field = {
	{},
	field_set_tile,
	field_unset_tile,
	field_get_tile,
	field_draw,
	field_add_shape
};

SHAPE shape = {
	{},
	{ 0, 0 },
	shape_draw
};

void tetris_init()
{
    keyb_init();
    graphic_init();
#ifndef SIMULATOR
    graphic_clear_screen();
#endif
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

static void new_shape()
{
	shape.geometry = random_geometry();
	shape.position.x = 3;
	shape.position.y = 0;
}

void tetris_run()
{
	running = 1;
	
	new_shape();

	while (running)
	{
		// Check keyboard input and move/rotate/drop shape accordingly
		switch (keyb())
		{
			case MOVE_LEFT:
				break;
			case MOVE_RIGHT:
				break;
			case ROTATE_CLOCKWISE:
				break;
			case ROTATE_ANTICLOCKWISE:
				break;
			case DROP:
				break;
		}
		
		// Check if shape can be moved down one step, and do if so, else add shape to field and generate new random shape
		// If shape is added to field, check if there are any full rows
		// Add points: https://tetris.wiki/Scoring
		
		// Check lose condition
		
		field.draw(&field);
		shape.draw(&shape);
		graphic_swap();
	}
}