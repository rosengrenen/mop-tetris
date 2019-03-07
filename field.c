#include "field.h"

#include "tile.h"

void field_set_tile(PFIELD field, int32_t x, int32_t y)
{
	if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT)
	{
		return;
	}
    field->tiles[y * FIELD_WIDTH + x] = 1;
}

void field_unset_tile(PFIELD field, int32_t x, int32_t y)
{
	if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT)
	{
		return;
	}
    field->tiles[y * FIELD_WIDTH + x] = 0;
}

int32_t field_get_tile(PFIELD field, int32_t x, int32_t y)
{
	if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT)
	{
		return 0;
	}
    return field->tiles[y * FIELD_WIDTH + x];
}

void field_draw(PFIELD field)
{
    for (int32_t x = 0; x < FIELD_WIDTH; ++x)
    {
        for (int32_t y = 0; y < FIELD_HEIGHT; ++y)
        {
            if (field->get_tile(field, x, y))
            {
                tile_draw(x, y);
            }
        }
    }
}

void field_add_shape(PFIELD field, PSHAPE shape)
{
	for (int32_t i = 0; i < 4; ++i)
    {
		field->set_tile(field, shape->position.x + shape->geometry.points[i].x, shape->position.y + shape->geometry.points[i].y);
    }
}

int32_t field_can_move_shape(PFIELD field, PSHAPE shape, int32_t dx, int32_t dy)
{
	for (int32_t i = 0; i < 4; ++i)
	{
		int32_t x = shape->position.x + shape->geometry.points[i].x + dx;
		int32_t y = shape->position.y + shape->geometry.points[i].y + dy;
		if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT || field->get_tile(field, x, y))
		{
			return 0;
		}
	}
	return 1;
}

int32_t field_is_row_full(PFIELD field, int32_t row)
{
	int32_t empty_tiles = 0;
	for (int32_t x = 0; x < FIELD_WIDTH; ++x)
	{
		if (!field->get_tile(field, x, row))
		{
			empty_tiles++;
		}
	}
	return empty_tiles == 0;
}

int32_t field_full_rows(PFIELD field)
{
	int32_t full_rows = 0;
	for (int32_t y = 0; y < FIELD_HEIGHT; ++y)
	{
		if (field_is_row_full(field, y))
		{
			full_rows++;
		}
	}
	return full_rows;
}

void field_remove_full_rows(PFIELD field)
{
	for (int32_t y = 0; y < FIELD_HEIGHT; ++y)
	{
		if (field_is_row_full(field, y))
		{
			for (int32_t row = y; row > 0; --row)
			{
				for (int32_t x = 0; x < FIELD_WIDTH; ++x)
				{
					if (field->get_tile(field, x, row - 1))
					{
						field->set_tile(field, x, row);
					}
					else
					{
						field->unset_tile(field, x, row);
					}
				}
			}
			for (int32_t x = 0; x < FIELD_WIDTH; ++x)
			{
				field->unset_tile(field, x, 0);
			}
		}
	}
}

void field_clear(PFIELD field)
{
	for (int32_t x = 0; x < FIELD_WIDTH; ++x)
	{
		for (int32_t y = 0; y < FIELD_HEIGHT; ++y)
		{
			field->unset_tile(field, x, y);
		}
	}
}
