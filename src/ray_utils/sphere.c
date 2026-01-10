#include "ray.h"

t_sphere	sphere(void)
{
	static 		int	id;
	t_sphere	s;

	s.id = id++;
	s.center = point_constructor(0, 0, 0);
	s.radius = 1.0;
	return (s);
}

t_intersect	sphere_intersect(t_ray ray, t_sphere sphere)
{
	t_intersect			i;
	t_vec3				sphere_to_ray;
	struct s_quadratic	q;

	sphere_to_ray = vector_sub(ray.origin, sphere.center);
	q.a = vector_dot_product(ray.direction, ray.direction);
	q.b = 2 * vector_dot_product(ray.direction, sphere_to_ray);
	q.c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	if (q.discriminant < 0)
		i.count = 0;
	else
	{
		i.count = 2;
		i.t[0] = (-q.b - sqrt(q.discriminant)) / (2 * q.a);
		i.t[1] = (-q.b + sqrt(q.discriminant)) / (2 * q.a);
	}
	return (i);
}
