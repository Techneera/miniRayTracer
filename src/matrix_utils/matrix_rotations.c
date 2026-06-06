#include "matrix.h"

t_mat4	matrix_rot_x(float angle)
{
	t_mat4	result;
	float	cos_;
	float	sin_;

	cos_ = cosf(angle);
	sin_ = sinf(angle);
	matrix_identity(&result);
	result.m[5] = cos_;
	result.m[6] = -sin_;
	result.m[9] = sin_;
	result.m[10] = cos_;
	return (result);
}

t_mat4	matrix_rot_y(float angle)
{
	t_mat4	result;
	float	cos_;
	float	sin_;

	cos_ = cosf(angle);
	sin_ = sinf(angle);
	matrix_identity(&result);
	result.m[0] = cos_;
	result.m[2] = sin_;
	result.m[8] = -sin_;
	result.m[10] = cos_;
	return (result);
}

t_mat4	matrix_rot_z(float angle)
{
	t_mat4	result;
	float	cos_;
	float	sin_;

	cos_ = cosf(angle);
	sin_ = sinf(angle);
	matrix_identity(&result);
	result.m[0] = cos_;
	result.m[1] = -sin_;
	result.m[4] = sin_;
	result.m[5] = cos_;
	return (result);
}
