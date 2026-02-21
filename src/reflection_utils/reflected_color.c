#include "scene.h"
#include "canvas.h"

t_vec3	reflected_color(t_world world, t_computation comps, int depth)
{
	t_shape	shape;
	t_ray	reflect_ray;
	t_vec3	color;

	if (depth <= 0)
		return (color_constructor(0, 0, 0));
	if (!get_shape(comps.object, &shape))
		return (color_constructor(0, 0, 0));
	if (shape.material.reflective < EPSILON)
		return (color_constructor(0, 0, 0));
	reflect_ray = ray_constructor(comps.over_point, comps.reflectv);
	color = color_at(world, reflect_ray, depth - 1);
	return (color_scalar(color, shape.material.reflective));
}
