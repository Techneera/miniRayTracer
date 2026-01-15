#include "matrix.h"

t_mat4	matrix_multiply(t_mat4 a, t_mat4 b)
{
	t_mat4	result;
	int		i;

	i = 0;
	while(i < 4)
	{
		result.rows[i] = (b.rows[0] * a.m[i * 4]) + \
						(b.rows[1] * a.m[i * 4 + 1]) + \
						(b.rows[2] * a.m[i * 4 + 2]) + \
						(b.rows[3] * a.m[i * 4 + 3]);
		i++;
	}
	return (result);
}

t_vec3	matrix_vector_multiply(t_mat4 m, t_vec3 v)
{
	t_vec3	result;
	t_f4	tmp;

	tmp = m.rows[0] * v.v;
	result.x = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	tmp = m.rows[1] * v.v;
	result.y = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	tmp = m.rows[2] * v.v;
	result.z = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	tmp = m.rows[3] * v.v;
	result.w = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	if (result.w != 1.0f && result.w != 0.0)
		result.v /= res.w;
	return (result);
}

void	matrix_identity(t_mat4 *dst)
{
	dst->row[0] = (t_f4){1, 0, 0, 0};
	dst->row[1] = (t_f4){0, 1, 0, 0};
	dst->row[2] = (t_f4){0, 0, 1, 0};
	dst->row[3] = (t_f4){0, 0, 0, 1};
}

t_mat4	matrix_transpose(t_mat4 m)
{
	t_mat4	result;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[j * 4 + i] = m.m[i * 4 + j];
			j++;
		}
		i++;
	}
	return (result);
}

float	matrix_determinant_2x2(float a, float b, float c, float d)
{
	return (a * d - b * c);
}

float	matrix_cofactor_3x3(t_mat4 m, int row, int col)
{
	int	idx[3];
	int	idy[3];
	int	k;
	int	l;

	k = -1;
	l = 0;
	while (++k < 4)
	{
		if (k != row)
			idx[l++] = k;
	}
	k = -1;
	l = 0;
	while (++k < 4)
	{
		if (k != col)
			idy[l++] = k;
	}
	return (m.m[idx[0] * 4 + idy[0]] * \
		matrix_determinant_2x2(m.m[idx[1] * 4 + idy[1]], \
		m.m[idx[1] * 4 + idy[2]], \
		m.m[idx[2] * 4 + idy[1]], \
		m.m[idx[2] * 4 + idy[2]]) - \
		m.m[idx[0] * 4 + idy[1]] * \
		matrix_determinant_2x2(m.m[idx[1] * 4 + idy[0]], \
		m.m[idx[1] * 4 + idy[2]], m.m[idx[2] * 4 + idy[0]], \
		m.m[idx[2] * 4 + idy[2]]) + \
		m.m[idx[0] * 4 + idy[2]] * \
		matrix_determinant_2x2(m.m[idx[1] * 4 + idy[0]], \
		m.m[idx[1] * 4 + idy[1]], m.m[idx[2] * 4 + idy[0]], \
		m.m[idx[2] * 4 + idy[1]]));
}

float	matrix_determinant(t_mat4 m)
{
	return (m.m[0] * matrix_cofactor_3x3(m, 0, 0) - \
			m.m[1] * matrix_cofactor_3x3(m, 0, 1) + \
			m.m[2] * matrix_cofactor_3x3(m, 0, 2) - \
			m.m[3] * matrix_cofactor_3x3(m, 0, 3));
}

int	matrix_is_invertable(t_mat4 m)
{
	float	det;

	det = matrix_determinant(m);
	if (fabsf(det) < 1e-6)
		return (0);
	return (1);
}

t_mat4	matrix_inverse(t_mat4 m)
{
	t_mat4	result;
	float	det;
	float	inv_det;
	float	sign;
	int		i;
	int		j;

	det = matrix_determinant(m);
	if (fabsf(det) < 1e-6)
	{
		matrix_identity(&result);
		return (result);
	}
	inv_det = 1.0f / det;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			sign = 1.0f - (2.0f * ((i + j) % 2));
			result.m[j * 4 + i] = matrix_cofactor_3x3(m, i, j) * inv_det * sign;
		}
	}
	return (result);
}
