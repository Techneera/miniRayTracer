#ifndef SHADOWS_H
# define SHADOWS_H

#include "librt.h"
#include "shades.h"

typedef struct s_world
{
	t_point_light	light;
	t_objects		objects[MAX_OBJECTS];
	int				object_count;
}	t_world;

#endif
