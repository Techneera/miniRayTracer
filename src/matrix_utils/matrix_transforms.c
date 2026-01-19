#include "matrix.h"

t_mat4	matrix_translation(float x, float y, float z)
{
	t_mat4	result;

	matrix_identity(&result);
	result.m[3] = x;
	result.m[7] = y;
	result.m[11] = z;
	return (result);
}

t_mat4	matrix_scale(float x, float y, float z)
{
	t_mat4	result;

	matrix_identity(&result);
	result.m[0] = x;
	result.m[5] = y;
	result.m[10] = z;
	return (result);
}

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
	result.m[1] = sin_;
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

t_mat4	matrix_shear(t_shear p)
{
	t_mat4	result;

	matrix_identity(&result);
	result.m[1] = p.xy;
	result.m[2] = p.xz;
	result.m[4] = p.yx;
	result.m[6] = p.yz;
	result.m[8] = p.zx;
	result.m[9] = p.zy;
	return (result);
}

t_vec3	matrix_shearing(t_shear p, t_vec3 target)
{
	t_mat4	shear_matrix;

	shear_matrix = matrix_shear(p);
	return (matrix_vector_multiply(shear_matrix, target));
}
