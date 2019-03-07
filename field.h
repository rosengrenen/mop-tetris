#ifndef FIELD_H
#define FIELD_H

#include "shape.h"
#include "types.h"

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 16
#define FIELD_BLOCK_SIZE (64 / FIELD_WIDTH)

typedef struct tField
{
	int32_t tiles[FIELD_WIDTH * FIELD_HEIGHT];
	void (* set_tile) (struct tField *, int32_t, int32_t);
	void (* unset_tile) (struct tField *, int32_t, int32_t);
	int32_t (* get_tile) (struct tField *, int32_t, int32_t);
	void (* draw) (struct tField *);
	void (* add_shape) (struct tField *, PSHAPE);
	int32_t (* can_move_shape) (struct tField *, PSHAPE, int32_t, int32_t);
	int32_t (* full_rows) (struct tField *);
	void (* remove_full_rows) (struct tField *);
	void (* clear) (struct tField * );
} FIELD, *PFIELD;

void field_set_tile(PFIELD field, int32_t x, int32_t y);
void field_unset_tile(PFIELD field, int32_t x, int32_t y);
int32_t field_get_tile(PFIELD field, int32_t x, int32_t y);
void field_draw(PFIELD field);
void field_add_shape(PFIELD field, PSHAPE shape);
int32_t field_can_move_shape(PFIELD field, PSHAPE shape, int32_t dx, int32_t dy);
int32_t field_full_rows(PFIELD field);
void field_remove_full_rows(PFIELD field);
void field_clear(PFIELD field);

#endif // FIELD_H