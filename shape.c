#include "shape.h"

#include "random.h"
#include "tile.h"

GEOMETRY o_geometry = {
    2,
    {
        { 0, 0 }, { 1, 0 },
        { 0, 1 }, { 1, 1 }
    }
};

GEOMETRY i_geometry = {
    4,
    {
        { 1, 0 },
        { 1, 1 }, 
        { 1, 2 },
        { 1, 3 }
    }
};

GEOMETRY s_geometry = {
    3,
    {
                  { 1, 0 }, { 2, 0 },
        { 0, 1 }, { 1, 1 }, 
    }
};

GEOMETRY z_geometry = {
    3,
    {
        { 0, 0 }, { 1, 0 },
                  { 1, 1 }, { 2, 1 }
    }
};

GEOMETRY l_geometry = {
    3,
    {
        { 1, 0 },
        { 1, 1 }, 
        { 1, 2 }, { 2, 2 }
    }
};

GEOMETRY j_geometry = {
    3,
    {
                  { 1, 0 },
                  { 1, 1 }, 
        { 0, 2 }, { 1, 2 }
    }
};

GEOMETRY t_geometry = {
    3,
    {
        { 0, 1 }, { 1, 1 }, { 2, 1 },
                  { 1, 2 }
    }
};

PGEOMETRY geometries[7] = {
	&o_geometry,
	&i_geometry,
	&s_geometry,
	&z_geometry,
	&l_geometry,
	&j_geometry,
	&t_geometry
};

void shape_draw(PSHAPE shape)
{
    for (int32_t i = 0; i < 4; ++i)
    {
        tile_draw(shape->position.x + shape->geometry.points[i].x,
                     shape->position.y + shape->geometry.points[i].y);
    }
}

void shape_rotate_clockwise(PSHAPE shape)
{
	for (int32_t i = 0; i < 4; ++i)
	{
		int32_t tmp = shape->geometry.points[i].x;
		shape->geometry.points[i].x = shape->geometry.size - shape->geometry.points[i].y - 1;
		shape->geometry.points[i].y = tmp;
	}
}

void shape_rotate_anticlockwise(PSHAPE shape)
{
	for (int32_t i = 0; i < 4; ++i)
	{
		int32_t tmp = shape->geometry.size - shape->geometry.points[i].x - 1;
		shape->geometry.points[i].x = shape->geometry.points[i].y;
		shape->geometry.points[i].y = tmp;
	}
}

GEOMETRY random_geometry()
{
	return *geometries[rand() % 7];
}