#include "shadows.h"
#include "ray.h"
#include "scene.h"
#include "vector.h"
#include <stdbool.h>

bool    is_shadowed(t_world world, t_vec3 point)
{
	t_vec3  vector;
	float  distance;
	t_ray	ray;
	t_intersect xs;
	t_intersection h;

	vector = vector_sub(world.light.position, point);
	distance = vector_length(vector);
	ray = ray_constructor(
		point,
		vector_normalization(vector)
	);
	xs = intersect_world(&world, &ray);
	if (hit(&xs, &h, xs.count) && h.t < distance)
		return (true);
	return (false);
}
