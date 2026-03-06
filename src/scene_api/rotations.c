#include "matrix.h"
#include "scene_api.h"

void	apply_rot_x(t_object *obj, float angle)
{
	t_mat4	t;

	t = matrix_rot_x(angle);
	chain_transform(obj, &t);
}

void	apply_rot_y(t_object *obj, float angle)
{
	t_mat4	t;

	t = matrix_rot_y(angle);
	chain_transform(obj, &t);
}

void	apply_rot_z(t_object *obj, float angle)
{
	t_mat4	t;

	t = matrix_rot_z(angle);
	chain_transform(obj, &t);
}
