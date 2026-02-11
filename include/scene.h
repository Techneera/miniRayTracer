#ifndef SCENE_H
# define SCENE_H

# include "shades.h"
# include "librt.h"
# include "ray.h"
# include "vector.h"
# include "canvas.h"

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
	t_vec3		eyev;
    t_vec3      normalv;
	t_vec3		over_point;
	bool		inside;
}   t_computation;

t_world     	default_world(void);
t_intersect 	intersect_world(t_world *world, t_ray ray);
t_computation   prepare_computations(t_intersection i, t_ray ray);
t_vec3			shade_hit(t_world world, t_computation computations);
t_vec3	        color_at(t_world world, t_ray ray);
t_mat4	        view_transform(t_vec3 from, t_vec3 to, t_vec3 up);

t_camera		camera_constructor(int hsize, int vsize, float field_of_view);
t_ray			ray_for_pixel(t_camera c, int px, int py);
t_canvas		render(t_camera c, t_world w);

#endif