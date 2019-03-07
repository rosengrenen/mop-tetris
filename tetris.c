#include "tetris.h"

#include "ascii.h"
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
uint8_t difficulty = 1;

#define MENU_STATE 0
#define DIFFICULTY_STATE 1
#define PLAYING_STATE 2
#define GAME_OVER_STATE 3
uint8_t state = MENU_STATE;

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
    ascii_init();
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

void int_to_string(int32_t value, char* buffer, uint32_t buffer_size)
{
    int32_t index = 0;
    while (index < buffer_size - 1 && value != 0)
    {
        buffer[index] = '0' + value % 10;
        value /= 10;
        index++;
    }
    buffer[index] = '\0';
}

void tetris_run()
{
	running = 1;
	
	new_shape();

    uint8_t first = 1;

	while (running)
	{
        if (state == MENU_STATE)
        {
            ascii_clear();
            ascii_print_at("(1) Start game", 1, 1);
            ascii_print_at("(2) Set difficulty", 1, 2);
            while (1)
            {
                unsigned char key = keyb();
                if (key == 1)
                {
                    state = PLAYING_STATE;
                    score = 0;
                    first = 1;
                    break;
                }
                else if (key == 2)
                {
                    state = DIFFICULTY_STATE;
                    break;
                }
            }
        }
        else if (state == DIFFICULTY_STATE)
        {
            ascii_clear();
            ascii_print_at("(1) Easy", 1, 1);
            ascii_print_at("(2) Medium", 11, 1);
            ascii_print_at("(3) Hard", 1, 2);
            ascii_print_at("(4) Insane", 11, 2);
            while (1)
            {
                unsigned char key = keyb();
                if (key >= 1 && key <= 4)
                {
                    difficulty = key;
                    break;
                }
            }
            state = MENU_STATE;
        }
        else if (state == PLAYING_STATE)
        {
            // Check keyboard input and move/rotate/drop shape accordingly
            uint8_t rows_dropped = 0;
            if (!first)
            {
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
                        if (field.can_move_shape(&field, &shape, 0, 0))
                        {
                            //
                        }
                        else if (field.can_move_shape(&field, &shape, 1, 0))
                        {
                            shape.position.x++;
                        }
                        else if (field.can_move_shape(&field, &shape, -1, 0))
                        {
                            shape.position.x--;
                        }
                        else if (field.can_move_shape(&field, &shape, 2, 0))
                        {
                            shape.position.x += 2;
                        }
                        else if (field.can_move_shape(&field, &shape, -2, 0))
                        {
                            shape.position.x -= 2;
                        }
                        else
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
            }
            
            if (rows_dropped > 0)
            {
                score += rows_dropped * difficulty;
            }
            
            if (!field.can_move_shape(&field, &shape, 0, 1))
            {
                field.add_shape(&field, &shape);
                uint8_t full_rows = field.full_rows(&field);
                
                uint8_t multiplier = 1;
                
                if (full_rows > 0)
                {
                    // TODO: check for perfect clear
                    // if perfect clear, multiplier = 10
                    field.remove_full_rows(&field);
                }
                
                switch (full_rows)
                {
                    case 1:
                        score += (100 * difficulty * multiplier);
                        break;
                    case 2:
                        score += (400 * difficulty * multiplier);
                        break;
                    case 3:
                        score += (900 * difficulty * multiplier);
                        break;
                    case 4:
                        score += (2000 * difficulty * multiplier);
                        break;
                }                
                
                if (full_rows || rows_dropped || first)
                {
                    ascii_clear();
                    ascii_print_at("Score: ", 1, 1);
                    ascii_print_at("", 7, 1);
                    ascii_print_at("Level: ", 1, 2);
                    ascii_print_at("", 7, 2);
                }
            
                new_shape();
                
                if (!field.can_move_shape(&field, &shape, 0, 0))
                {
                    state = GAME_OVER_STATE;
                }
            }
            else
            {
                if (!first)
                {
                    shape.position.y++;
                }
            }
            
            first = 0;
            
            field.draw(&field);
            shape.draw(&shape);
            graphic_swap();
            
            //TODO: difficulty speed
            delay_milli(50);
        }
        else if (state == GAME_OVER_STATE)
        {
            ascii_clear();
            ascii_print_at("Game over!", 1, 1);
            ascii_print_at("Score: ", 1, 2);
            ascii_print_at("", 7, 2);
            delay_milli(5000);
            state = MENU_STATE;
        }
	}
}