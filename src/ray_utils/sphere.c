#include "ray.h"

t_sphere	sphere(void)
{
	static 		int	id;
	t_sphere	s;

	s.id = id++;
	s.center = point_constructor(0, 0, 0);
	s.radius = 1.0f;
	matrix_identity(&s.transform);
	matrix_identity(&s.transform_inv);
	s.material = new_material();
	return (s);
}

t_intersect	sphere_intersect(t_ray ray, t_sphere sphere)
{
	t_intersect			this;
	t_vec3				sphere_to_ray;
	t_ray				obj_ray;
	float				sqrt_disc;
	struct s_quadratic	q;

	obj_ray = ray_transform(ray, sphere.transform_inv);
	sphere_to_ray = vector_sub(obj_ray.origin, sphere.center);
	q.a = vector_dot_product(obj_ray.direction, obj_ray.direction);
	q.b = 2 * vector_dot_product(obj_ray.direction, sphere_to_ray);
	q.c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	this.count = 0;
	if (q.discriminant < 0)
		return (this);
	this.i[0].object.sp = sphere;
	this.i[1].object.sp = sphere;
	sqrt_disc = sqrt(q.discriminant);
	this.count = 2;
	this.i[0].t = (-q.b - sqrt_disc) / (2 * q.a);
	this.i[1].t = (-q.b + sqrt_disc) / (2 * q.a);
	return (this);
}

void	sphere_set_transform(t_sphere *s, t_mat4 t)
{
	s->transform = t;
	s->transform_inv = matrix_inverse(t);
}
