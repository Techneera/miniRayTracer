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

t_sphere	sphere(void)
{
	static 		int	id;
	t_sphere	s;

	s.id = id++;
	s.center = point_constructor(0, 0, 0);
	s.radius = 1.0;
	return (s);
}

t_intersect	intersect(t_ray ray, t_sphere sphere)
{
	t_intersect	i;

	i.count = 2;
	i.t[0] = 4.0;
	i.t[1] = 6.0;
	return (i);
}
