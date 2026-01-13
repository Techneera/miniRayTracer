#include "ray.h"
#include "vector.h"

t_ray	ray_constructor(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vec3	ray_position(t_ray ray, double t)
{
	return (vector_add(
			ray.origin,
			vector_scale(ray.direction, t)
		)
	);	
}
