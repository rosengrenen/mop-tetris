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

uint32_t score = 0;

FIELD field = {
	{},
	field_set_tile,
	field_unset_tile,
	field_get_tile,
	field_draw,
	field_add_shape,
	field_can_move_shape,
	field_full_rows,
	field_remove_full_rows
};

SHAPE shape = {
	{},
	{ 0, 0 },
	shape_draw,
	shape_rotate_clockwise,
	shape_rotate_anticlockwise
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
		uint8_t rows_dropped = 0;
		switch (keyb())
		{
			case MOVE_LEFT:
				if (field.can_move_shape(&field, &shape, -1, 0))
				{
					shape.position.x--;
				}
				break;
			case MOVE_RIGHT:
				if (field.can_move_shape(&field, &shape, 1, 0))
				{
					shape.position.x++;
				}
				break;
			case ROTATE_CLOCKWISE:
				shape.rotate_clockwise(&shape);
				if (!field.can_move_shape(&field, &shape, 0, 0))
				{
					shape.rotate_anticlockwise(&shape);
				}
				break;
			case ROTATE_ANTICLOCKWISE:
				shape.rotate_anticlockwise(&shape);
				if (!field.can_move_shape(&field, &shape, 0, 0))
				{
					shape.rotate_clockwise(&shape);
				}
				break;
			case DROP:
				while (field.can_move_shape(&field, &shape, 0, 1))
				{
					shape.position.y++;
					rows_dropped++;
				}
				break;
		}
		
		if (rows_dropped > 0)
		{
			score += rows_dropped + 1;
		}
		
		if (!field.can_move_shape(&field, &shape, 0, 1))
		{
			field.add_shape(&field, &shape);
			uint8_t full_rows = field.full_rows(&field);
			switch (full_rows)
			{
				case 1:
					score += 100;
					break;
				case 2:
					score += 400;
					break;
				case 3:
					score += 900;
					break;
				case 4:
					score += 2000;
					break;
			}
			
			if (full_rows > 0)
			{
				field.remove_full_rows(&field);
			}
		
			new_shape();
			
			if (!field.can_move_shape(&field, &shape, 0, 0))
			{
				tetris_stop();
			}
		}
		else
		{
			shape.position.y++;
		}
		
		
		field.draw(&field);
		shape.draw(&shape);
		graphic_swap();
	}
}