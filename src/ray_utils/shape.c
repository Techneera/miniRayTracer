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
	s.material = new_material(0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
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
		result = local_intersect_sphere((t_sphere *)shape, local_ray);
	else if (shape->type == SHAPE_PLANE)
		result = local_intersect_plane((t_plane *)shape, local_ray);
	else
		result.count = 0;
	return (result);
}

static int	is_identity_transform(t_shape *s)
{
	return (s->transform.m[0] == 1.0f && s->transform.m[5] == 1.0f && s->transform.m[10] == 1.0f &&
		s->transform.m[1] == 0.0f && s->transform.m[2] == 0.0f && s->transform.m[4] == 0.0f &&
		s->transform.m[6] == 0.0f && s->transform.m[8] == 0.0f && s->transform.m[9] == 0.0f);
}

static t_vec3	compute_default_normal(t_shape *s, t_vec3 local_point)
{
	t_vec3	local_normal;
	t_mat4	transpose_inverse;
	t_vec3	world_normal;

	local_normal = vector_constructor(local_point.x, local_point.y, local_point.z);
	local_normal.w = 0.0f;
	local_normal = vector_normalization(local_normal);
	transpose_inverse = matrix_transpose(s->transform_inv);
	world_normal = matrix_vector_multiply(transpose_inverse, local_normal);
	world_normal.w = 0.0f;
	if (is_identity_transform(s))
		return (local_normal);
	return (vector_normalization(world_normal));
}

t_vec3	normal_at(t_shape *s, t_vec3 world_point)
{
	t_vec3	local_point;
	t_vec3	local_normal;
	t_vec3	world_normal;
	t_mat4	transpose_inverse;

	local_point = matrix_vector_multiply(s->transform_inv, world_point);
	if (s->type == SHAPE_SPHERE)
		local_normal = local_normal_at_sphere((t_sphere *)s, local_point);
	else if (s->type == SHAPE_PLANE)
		local_normal = local_normal_at_plane();
	else
		return (compute_default_normal(s, local_point));
	transpose_inverse = matrix_transpose(s->transform_inv);
	world_normal = matrix_vector_multiply(transpose_inverse, local_normal);
	world_normal.w = 0.0f;
	return (vector_normalization(world_normal));
}
