#include "ray.h"

int get_shape_id(void)
{
    static int id;

    return (id++);
}

t_shape	test_shape(void)
{
	t_shape	s;

	s.type = SHAPE_TEST;
	s.id = get_shape_id();
	matrix_identity(&s.transform);
	matrix_identity(&s.transform_inv);
	s.material = new_material(0.1f, 0.9f, 0.9f, 200.0f);
	return (s);
}

void	set_transform(t_shape *s, t_mat4 t)
{
	s->transform = t;
	s->transform_inv = matrix_inverse(t);
}

t_intersect	intersect(t_ray ray, t_shape *shape)
{
	t_ray		local_ray;
	t_intersect	result;

	local_ray = ray_transform(ray, shape->transform_inv);
	if (shape->type == SHAPE_SPHERE)
	{
		result = local_intersect_sphere((t_sphere *)shape, local_ray);
	}
	else
	{
		result.count = 0;
	}
	return (result);
}

t_vec3	normal_at(t_shape *s, t_vec3 world_point)
{
	t_vec3	local_point;
	t_vec3	local_normal;
	t_vec3	world_normal;
	t_mat4	transpose_inverse;

	local_point = matrix_vector_multiply(s->transform_inv, world_point);
	if (s->type == SHAPE_SPHERE)
	{
		local_normal = local_normal_at_sphere((t_sphere *)s, local_point);
	}
	else
	{
		local_normal = vector_constructor(0, 1, 0);
	}
	transpose_inverse = matrix_transpose(s->transform_inv);
	world_normal = matrix_vector_multiply(transpose_inverse, local_normal);
	world_normal.w = 0.0f;
	return (vector_normalization(world_normal));
}
