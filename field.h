#ifndef FIELD_H
#define FIELD_H

#include "shape.h"
#include "types.h"

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 16
#define FIELD_BLOCK_SIZE (64 / FIELD_WIDTH)

typedef struct tField
{
	uint8_t tiles[FIELD_WIDTH * FIELD_HEIGHT];
	void (* set_tile) (struct tField *, uint32_t x, uint32_t y);
	void (* unset_tile) (struct tField *, uint32_t x, uint32_t y);
	uint8_t (* get_tile) (struct tField *, uint32_t x, uint32_t y);
	void (* draw) (struct tField *);
	void (* add_shape) (struct tField *, PSHAPE shape);
} FIELD, *PFIELD;

void field_set_tile(PFIELD field, uint32_t x, uint32_t y);
void field_unset_tile(PFIELD field, uint32_t x, uint32_t y);
uint8_t field_get_tile(PFIELD field, uint32_t x, uint32_t y);
void field_draw(PFIELD field);
void field_add_shape(PFIELD field, PSHAPE shape);

#endif // FIELD_H