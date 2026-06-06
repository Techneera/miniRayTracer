#include "matrix.h"
#include "ray.h"
#include "scene_api.h"

void	chain_transform(t_object *obj, t_mat4 *new_transform)
{
	t_mat4	res;

	res = matrix_multiply(new_transform, &obj->transform);
	set_transform(obj, &res);
}

void	apply_translation(t_object *obj, float x, float y, float z)
{
	t_mat4	trans;

	trans = matrix_translation(x, y, z);
	chain_transform(obj, &trans);
}

void	apply_scale(t_object *obj, float x, float y, float z)
{
	t_mat4	scale;

	scale = matrix_scale(x, y, z);
	chain_transform(obj, &scale);
}
