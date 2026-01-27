#ifndef SCENE_H
# define SCENE_H

# include "shades.h"
# include "librt.h"
# include "ray.h"
# include "vector.h"

typedef struct s_world
{
    t_point_light   light;
    t_objects       objects[MAX_OBJECTS];
    int             object_count;
}   t_world;

typedef struct s_computation
{
    float       t;
    t_object    object;
    t_vec3      point;
    t_vec3      normalv;
}   t_computation;

t_world     	default_world(void);
t_intersect 	intersect_world(t_world *world, t_ray ray);
t_computation   prepare_computations(t_intersection i, t_ray ray);

#endif