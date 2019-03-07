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

int32_t running = 0;

int32_t score = 0;
int32_t difficulty = 1;

#define MENU_STATE 0
#define DIFFICULTY_STATE 1
#define PLAYING_STATE 2
#define GAME_OVER_STATE 3
int32_t state = MENU_STATE;

FIELD field = {
	{},
	field_set_tile,
	field_unset_tile,
	field_get_tile,
	field_draw,
	field_add_shape,
	field_can_move_shape,
	field_full_rows,
	field_remove_full_rows,
	field_clear,
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

void int_to_string(int32_t value, char* buffer, int32_t buffer_size)
{
	if (value == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
	}
	else
	{
		int32_t index = 0;
		while (index < buffer_size - 1 && value != 0)
		{
			buffer[index] = '0' + value % 10;
			value /= 10;
			index++;
		}
		char buff[32];
		for (int32_t i = 0; i < index; ++i)
		{
			buff[index - i - 1] = buffer[i];
		}
		for (int32_t i = 0; i < index; ++i)
		{
			buffer[i] = buff[i];
		}
		buffer[index] = '\0';
	}
}

void tetris_run()
{
	running = 1;

    int32_t first = 1;

	while (running)
	{
        if (state == MENU_STATE)
        {
            ascii_clear();
            ascii_print_at("(1) Start game", 1, 1);
            ascii_print_at("(2) Set difficulty", 1, 2);
            while (1)
            {
                int32_t key = keyb();
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
			delay_milli(100);
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
			delay_milli(100);
        }
        else if (state == PLAYING_STATE)
        {
			graphic_clear();
			if (first)
			{
				graphic_clear_screen();
				graphic_swap();
				graphic_clear();
				field.clear(&field);
				new_shape();
			}
			
			// Check keyboard input and move/rotate/drop shape accordingly
            int32_t rows_dropped = 0;
			int32_t full_rows = 0;
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
            
				if (rows_dropped > 0)
				{
					score += rows_dropped * difficulty;
				}
				
				if (!field.can_move_shape(&field, &shape, 0, 1))
				{
					field.add_shape(&field, &shape);
					full_rows = field.full_rows(&field);
					
					int32_t multiplier = 1;
					
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
				
					new_shape();
					
					if (!field.can_move_shape(&field, &shape, 0, 0))
					{
						state = GAME_OVER_STATE;
					}
				}
				else
				{
					shape.position.y++;
				}
			}
                
			if (full_rows || rows_dropped || first)
			{
				ascii_clear();
				ascii_print_at("Score: ", 1, 1);
				char score_buffer[16];
				int_to_string(score, score_buffer, 16);
				ascii_print_at(score_buffer, 8, 1);
				ascii_print_at("Level: ", 1, 2);
				char difficulty_buffer[10];
				int_to_string(difficulty, difficulty_buffer, 10);
				ascii_print_at(difficulty_buffer, 8, 2);
			}
			
            first = 0;
            
            field.draw(&field);
            shape.draw(&shape);
            graphic_swap();
            
            //TODO: difficulty speed
			switch (difficulty)
			{
				case 1:
					delay_milli(300);
					break;
				case 2:
					delay_milli(240);
					break;
				case 3:
					delay_milli(170);
					break;
				case 4:
					delay_milli(100);
					break;
			}
        }
        else if (state == GAME_OVER_STATE)
        {
            ascii_clear();
            ascii_print_at("Game over!", 1, 1);
            ascii_print_at("Score: ", 1, 2);
			char score_buffer[16];
			int_to_string(score, score_buffer, 16);
            ascii_print_at(score_buffer, 8, 2);
            delay_milli(2500);
            state = MENU_STATE;
        }
	}
}