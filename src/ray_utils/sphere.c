#include "ray.h"

t_intersect	local_intersect_sphere(const t_object *sphere, const t_ray *ray)
{
	t_intersect			result;
	t_vec3				sphere_to_ray;
	float				sqrt_disc;
	t_quadratic			q;

	result.count = 0;
	sphere_to_ray = vector_sub(ray->origin, vector_constructor(0.0f, 0.0f, 0.0f));
	q.a = vector_dot_product(ray->direction, ray->direction);
	q.b = 2 * vector_dot_product(ray->direction, sphere_to_ray);
	q.c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1.0f;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	if (q.discriminant < EPSILON)
		return (result);
	sqrt_disc = sqrtf(q.discriminant);
	result.count = 2;
	result.i[0].t = (-q.b - sqrt_disc) / (2.0f * q.a);
	result.i[1].t = (-q.b + sqrt_disc) / (2.0f * q.a);
	result.i[0].object = sphere;
	result.i[1].object = sphere;
	return (result);
}

t_vec3	local_normal_at_sphere(t_vec3 local_point)
{
	t_vec3	local_normal;

	local_normal = local_point;
	local_normal.w = 0.0f;
	return (vector_normalization(local_normal));
}
