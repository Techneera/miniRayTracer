#ifndef SCENE_H
# define SCENE_H

# include "librt.h"
# include "ray.h"
# include "canvas.h"

# define MAX_BOUNCE 5

typedef struct s_computation
{
	float			t;
	const t_object	*object;
	t_vec3			point;
	t_vec3			eyev;
	t_vec3			normalv;
	t_vec3			over_point;
	t_vec3			reflectv;
	bool			inside;
}	t_computation;

t_world     	default_world(void);
t_intersect 	intersect_world(t_world *world, t_ray *ray);
t_computation   prepare_computations(t_intersection i, t_ray *ray);
t_vec3			shade_hit(t_world *world, t_computation *computations, int depth);
t_vec3	        color_at(t_world *world, t_ray *ray, int depth);
t_mat4	        view_transform(t_vec3 from, t_vec3 to, t_vec3 up);

t_camera		camera_constructor(int hsize, int vsize, float field_of_view);
t_ray			ray_for_pixel(t_camera *c, int px, int py);
t_canvas		render(void *mlx, t_camera *c, t_world *w);

t_vec3			reflected_color(t_world *world, t_computation *comps, int depth);
#endif
