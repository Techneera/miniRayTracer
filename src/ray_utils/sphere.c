#include "ray.h"

t_sphere	sphere(void)
{
	t_sphere	s;

	s.shape.type = SHAPE_SPHERE;
	s.shape.id = get_shape_id();
	s.center = point_constructor(0, 0, 0);
	s.radius = 1.0f;
	matrix_identity(&s.shape.transform);
	matrix_identity(&s.shape.transform_inv);
	s.shape.material = material_default();
	return (s);
}

t_intersect	local_intersect_sphere(t_sphere *sphere, t_ray local_ray)
{
	t_intersect			result;
	t_vec3				sphere_to_ray;
	float				sqrt_disc;
	struct s_quadratic	q;

	sphere_to_ray = vector_sub(local_ray.origin, sphere->center);
	q.a = vector_dot_product(local_ray.direction, local_ray.direction);
	q.b = 2 * vector_dot_product(local_ray.direction, sphere_to_ray);
	q.c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	result.count = 0;
	if (q.discriminant < 0)
		return (result);
	result.i[0].object.sp = *sphere;
	result.i[1].object.sp = *sphere;
	sqrt_disc = sqrtf(q.discriminant);
	result.count = 2;
	result.i[0].t = (-q.b - sqrt_disc) / (2 * q.a);
	result.i[1].t = (-q.b + sqrt_disc) / (2 * q.a);
	return (result);
}

t_vec3	local_normal_at_sphere(t_sphere *sphere, t_vec3 local_point)
{
	t_vec3	local_normal;

	(void)sphere;
	local_normal = vector_constructor(local_point.x, local_point.y, local_point.z);
	return (local_normal);
}

// Backward compatibility wrapper
void	sphere_set_transform(t_sphere *s, t_mat4 t)
{
	set_transform(&s->shape, t);
}

// Backward compatibility wrapper
t_intersect	sphere_intersect(t_ray ray, t_sphere sphere)
{
	return (intersect(ray, &sphere.shape));
}
