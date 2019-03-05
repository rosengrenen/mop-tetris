#include "tile.h"

#include "field.h"
#include "graphics.h"

void tile_draw(uint32_t x, uint32_t y)
{
    for (uint32_t i = 0; i < FIELD_BLOCK_SIZE; ++i)
    {
        for (uint32_t j = 0; j < FIELD_BLOCK_SIZE; ++j)
        {
            graphic_pixel(y * FIELD_BLOCK_SIZE + i, (FIELD_BLOCK_SIZE - 1 - x) * FIELD_BLOCK_SIZE + j, 1);
        }
    }
}
