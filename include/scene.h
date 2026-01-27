#ifndef SCENE_H
# define SCENE_H

# include "shades.h"
# include "librt.h"
# include "ray.h"
# include "canvas.h"
# include "matrix.h"

typedef struct s_world
{
    t_point_light   light;
    t_objects       objects[MAX_OBJECTS];
    int             object_count;
}   t_world;

t_world default_world(void);
t_intersect intersect_world(t_world *world, t_ray ray);

#endif