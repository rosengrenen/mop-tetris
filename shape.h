#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"

typedef struct tPoint
{
    int32_t x, y;
} POINT;

typedef struct tGeometry
{
    int32_t size;
    POINT points[4];
} GEOMETRY, *PGEOMETRY;

typedef struct tShape
{
    GEOMETRY geometry;
    POINT position;
	void (* draw) (struct tShape *);
	void (* rotate_clockwise) (struct tShape *);
	void (* rotate_anticlockwise) (struct tShape *);
} SHAPE, *PSHAPE;

void shape_draw(PSHAPE geometry);
void shape_rotate_clockwise(PSHAPE shape);
void shape_rotate_anticlockwise(PSHAPE shape);
GEOMETRY random_geometry();

#endif // SHAPE_H