#include "librt.h"
#include "vector.h"
#include "matrix.h"

t_mat4	align_up_vector(t_vec3 target_up)
{
	t_vec3	up;
	t_vec3	right;
	t_vec3	forward;
	t_mat4	result;

	up = vector_constructor(0.0f, 1.0f, 0.0f);
	target_up = vector_normalization(target_up);
	if (fabs(target_up.y - 1.0f) < EPSILON)
	{
		matrix_identity(&result);
		return (result);
	}
	if (fabs(target_up.y + 1.0f) < EPSILON)
		return (matrix_rot_x(M_PI));
	right = vector_normalization(vector_cross_product(up, target_up));
	forward = vector_cross_product(target_up, right);
	matrix_identity(&result);
	result = (t_mat4){.m = {right.x, target_up.x, forward.x, 0.0f, right.y,
		target_up.y, forward.y, 0.0f, right.z, target_up.z, forward.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}};
	return (result);
}
