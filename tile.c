#include "tile.h"

#include "field.h"
#include "graphics.h"

void tile_draw(int32_t x, int32_t y)
{
    for (int32_t i = 0; i < FIELD_BLOCK_SIZE; ++i)
    {
        for (int32_t j = 0; j < FIELD_BLOCK_SIZE; ++j)
        {
            graphic_pixel(y * FIELD_BLOCK_SIZE + i, (FIELD_BLOCK_SIZE - 1 - x) * FIELD_BLOCK_SIZE + j, 1);
        }
    }
}
