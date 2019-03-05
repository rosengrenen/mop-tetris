#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"

typedef struct tPoint
{
    uint8_t x, y;
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
} SHAPE, *PSHAPE;

void draw_shape(PSHAPE geometry);
GEOMETRY random_geometry();

#endif // SHAPE_H