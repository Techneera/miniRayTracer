#include "canvas.h"
#include "scene.h"

t_vec3	reflected_color(t_world *world, t_computation *comps, int depth)
{
	t_ray	reflect_ray;
	t_vec3	color;

	if (depth <= 0)
		return (color_constructor(0.0f, 0.0f, 0.0f));
	if (comps->object->material.reflective < EPSILON)
		return (color_constructor(0.0f, 0.0f, 0.0f));
	reflect_ray = ray_constructor(comps->over_point, comps->reflectv);
	color = color_at(world, &reflect_ray, depth - 1);
	return (color_scalar(color, comps->object->material.reflective));
}
