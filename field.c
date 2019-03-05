#include "field.h"

#include "tile.h"

void field_set_tile(PFIELD field, uint32_t x, uint32_t y)
{
    field->tiles[y * FIELD_WIDTH + x] = 1;
}

void field_unset_tile(PFIELD field, uint32_t x, uint32_t y)
{
    field->tiles[y * FIELD_WIDTH + x] = 0;
}

uint8_t field_get_tile(PFIELD field, uint32_t x, uint32_t y)
{
    return field->tiles[y * FIELD_WIDTH + x];
}

void field_draw(PFIELD field)
{
    for (uint32_t x = 0; x < FIELD_WIDTH; ++x)
    {
        for (uint32_t y = 0; y < FIELD_HEIGHT; ++y)
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
	for (uint8_t i = 0; i < 4; ++i)
    {
		field->set_tile(field, shape->geometry.points[i].x, shape->geometry.points[i].y);
    }
}
