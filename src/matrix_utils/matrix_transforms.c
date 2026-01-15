#include "matrix.h"

t_mat4	matrix_translation(float x, float y, float z)
{
	t_mat4	result;

	matrix_identity(&result);
	result.m[3] = x;
	result.m[7] = x;
	result.m[11] = x;
	return (result);
}

t_mat4	matrix_inverse_translation(t_mat4 m, float x, float y, float z)
{
	t_mat4	result;

	result = matrix_inverse(m);
	return (matrix_translation(x, y, z));
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

void	matrix_shear_constructor(double *m, t_shear proportions)
{
	m[0] = 1.0;
	m[1] = proportions.xy;
	m[2] = proportions.xz;
	m[3] = 0.0;

	m[4] = proportions.yx;
	m[5] = 1.0;
	m[6] = proportions.yx;
	m[7] = 0.0;

	m[8] = proportions.zx;
	m[9] = proportions.zy;
	m[10] = 1.0;
	m[11] = 0.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;
}

t_vec3	matrix_shearing(t_vec3 point_target, t_shear proportions)
{
	double	m_shear[16];

	matrix_shear_constructor(m_shear, proportions);
	return (matrix_vector_multiply(m_shear, point_target));
}
