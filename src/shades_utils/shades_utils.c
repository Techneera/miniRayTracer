#include "shades.h"

t_vec3	normal_at(t_sphere s, t_vec3 world_point)
{
	t_vec3	obj_point;
	t_vec3	obj_normal;
	t_vec3	world_normal;
	t_mat4	transpose_inverse;

	obj_point = matrix_vector_multiply(s.transform_inv, world_point);
	// If sphere is not unit sphere obj_normal is vector_sub(obj_point, p(0, 0, 0))
	obj_normal = vector_constructor(obj_point.x, obj_point.y, obj_point.z);
	transpose_inverse = matrix_transpose(s.transform_inv);
	world_normal = matrix_vector_multiply(transpose_inverse, obj_normal);
	world_normal.w = 0.0f;
	return (vector_normalization(world_normal));
}

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	float	dot;

	dot = vector_dot_product(in, normal);
	return (vector_sub(in, vector_scale(normal, 2.0f * dot)));
}
