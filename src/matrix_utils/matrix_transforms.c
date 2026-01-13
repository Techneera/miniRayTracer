#include "matrix.h"

void	matrix_translation_constructor(double *m_trans, double x, double y, double z)
{
	m_trans[0] = 1.0;
	m_trans[1] = 0.0;
	m_trans[2] = 0.0;
	m_trans[3] = x;

	m_trans[4] = 0.0;
	m_trans[5] = 1.0;
	m_trans[6] = 0.0;
	m_trans[7] = y;

	m_trans[8] = 0.0;
	m_trans[9] = 0.0;
	m_trans[10] = 1.0;
	m_trans[11] = z;

	m_trans[12] = 0.0;
	m_trans[13] = 0.0;
	m_trans[14] = 0.0;
	m_trans[15] = 1.0;
}

t_vec3	matrix_translation(double *translation_matrix, t_vec3 point_trans, t_vec3 point_target)
{
	matrix_translation_constructor(translation_matrix, point_trans.x, point_trans.y, point_trans.z);
	return (matrix_vector_multiply(translation_matrix, point_target));
}

t_vec3	matrix_inverse_translation(double *translation_matrix, t_vec3 point_trans, t_vec3 point_target)
{
	matrix_translation_constructor(translation_matrix, point_trans.x, point_trans.y, point_trans.z);
	matrix_inverse(translation_matrix);
	return (matrix_vector_multiply(translation_matrix, point_target));
}

void	matrix_scale_constructor(double *scale_matrix, t_vec3 point)
{
	scale_matrix[0] = point.x;
	scale_matrix[1] = 0.0;
	scale_matrix[2] = 0.0;
	scale_matrix[3] = 0.0;

	scale_matrix[4] = 0.0;
	scale_matrix[5] = point.y;
	scale_matrix[6] = 0.0;
	scale_matrix[7] = 0.0;

	scale_matrix[8] = 0.0;
	scale_matrix[9] = 0.0;
	scale_matrix[10] = point.z;
	scale_matrix[11] = 0.0;

	scale_matrix[12] = 0.0;
	scale_matrix[13] = 0.0;
	scale_matrix[14] = 0.0;
	scale_matrix[15] = 1.0;
}

t_vec3	matrix_scale(double *scale_matrix, t_vec3 point_scale, t_vec3 point_target)
{
	matrix_scale_constructor(scale_matrix, point_scale);
	return (matrix_vector_multiply(scale_matrix, point_target));
}

t_vec3	matrix_scale_inverse(double *scale_matrix, t_vec3 point_scale, t_vec3 point_target)
{
	matrix_scale_constructor(scale_matrix, point_scale);
	matrix_inverse(scale_matrix);
	return (matrix_vector_multiply(scale_matrix, point_target));
}

void	rotation_x_constructor(double *m, double angle)
{
	m[0] = 1.0;
	m[1] = 0.0;
	m[2] = 0.0;
	m[3] = 0.0;

	m[4] = 0.0;
	m[5] = cos(angle);
	m[6] = -sin(angle);
	m[7] = 0.0;

	m[8] = 0.0;
	m[9] = sin(angle);
	m[10] = cos(angle);
	m[11] = 0.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;
}

void	rotation_y_constructor(double *m, double angle)
{
	m[0] = cos(angle);
	m[1] = 0.0;
	m[2] = sin(angle);
	m[3] = 0.0;

	m[4] = 0.0;
	m[5] = 1.0;
	m[6] = 0.0;
	m[7] = 0.0;

	m[8] = -sin(angle);
	m[9] = 0.0;
	m[10] = cos(angle);
	m[11] = 0.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;
}

void	rotation_z_constructor(double *m, double angle)
{
	m[0] = cos(angle);
	m[1] = -sin(angle);
	m[2] = 0.0;
	m[3] = 0.0;

	m[4] = sin(angle);
	m[5] = cos(angle);
	m[6] = 0.0;
	m[7] = 0.0;

	m[8] = 0.0;
	m[9] = 0.0;
	m[10] = 1.0;
	m[11] = 0.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;
}

t_vec3	matrix_rotation(t_vec3 point_target, double angle, void(*f)(double *, double))
{
	double	m_axis[16];

	f(m_axis, angle);
	return (matrix_vector_multiply(m_axis, point_target));
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
