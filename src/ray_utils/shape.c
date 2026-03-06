#include "librt.h"
#include "patterns.h"
#include "ray.h"
#include "vector.h"
#include <stdbool.h>
#include <stdlib.h>

int	get_shape_id(void)
{
	static int	id;

	return (id++);
}

void	set_transform(t_object *obj, const t_mat4 *t)
{
	obj->transform = *t;
	obj->transform_inv = matrix_inverse(t);
}

t_intersect	intersect(const t_ray *ray, const t_object *obj)
{
	t_ray		local_ray;
	t_intersect	result;

	result.count = 0;
	local_ray = ray_transform(ray, &obj->transform_inv);
	if (obj->type == SPHERE)
		result = local_intersect_sphere(obj, &local_ray);
	else if (obj->type == PLANE)
		result = local_intersect_plane(obj, &local_ray);
	else if (obj->type == CUBE)
		result = local_intersect_cube(obj, &local_ray);
	else if (obj->type == CYLINDER)
		result = local_intersect_cylinder(obj, &local_ray);
	return (result);
}

static int	is_identity_transform(const t_object *obj)
{
	return (obj->transform.m[0] == 1.0f && obj->transform.m[5] == 1.0f
		&& obj->transform.m[10] == 1.0f && obj->transform.m[1] == 0.0f
		&& obj->transform.m[2] == 0.0f && obj->transform.m[4] == 0.0f
		&& obj->transform.m[6] == 0.0f && obj->transform.m[8] == 0.0f
		&& obj->transform.m[9] == 0.0f);
}

static t_vec3	compute_default_normal(const t_object *obj, t_vec3 local_point)
{
	t_vec3	local_normal;
	t_mat4	transpose_inverse;
	t_vec3	world_normal;

	local_normal = vector_constructor(local_point.x, local_point.y,
			local_point.z);
	local_normal.w = 0.0f;
	local_normal = vector_normalization(local_normal);
	transpose_inverse = matrix_transpose(&obj->transform_inv);
	world_normal = matrix_vector_multiply(&transpose_inverse, &local_normal);
	world_normal.w = 0.0f;
	if (is_identity_transform(obj))
		return (local_normal);
	return (vector_normalization(world_normal));
}

t_vec3	normal_at(const t_object *obj, t_vec3 world_point)
{
	t_vec3	local_point;
	t_vec3	local_normal;
	t_vec3	world_normal;
	t_mat4	transpose_inverse;

	local_point = matrix_vector_multiply(&obj->transform_inv, &world_point);
	if (obj->type == SPHERE)
		local_normal = local_normal_at_sphere(local_point);
	else if (obj->type == PLANE)
		local_normal = local_normal_at_plane();
	else if (obj->type == CUBE)
		local_normal = local_normal_at_cube(local_point);
	else if (obj->type == CYLINDER)
		local_normal = local_normal_at_cylinder(obj, local_point);
	else
		return (compute_default_normal(obj, local_point));
	transpose_inverse = matrix_transpose(&obj->transform_inv);
	world_normal = matrix_vector_multiply(&transpose_inverse, &local_normal);
	world_normal.w = 0.0f;
	return (vector_normalization(world_normal));
}
