#include "matrix.h"

t_mat4	matrix_multiply(const t_mat4 *a, const t_mat4 *b)
{
	t_mat4	result;
	int		i;

	i = 0;
	while (i < 4)
	{
		result.rows[i] = (b->rows[0] * a->m[i * 4]) + (b->rows[1] * a->m[i * 4
				+ 1]) + (b->rows[2] * a->m[i * 4 + 2]) + (b->rows[3] * a->m[i
				* 4 + 3]);
		i++;
	}
	return (result);
}

t_vec3	matrix_vector_multiply(const t_mat4 *m, const t_vec3 *v)
{
	t_vec3	result;
	t_f4	tmp;

	tmp = m->rows[0] * v->v;
	result.x = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	tmp = m->rows[1] * v->v;
	result.y = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	tmp = m->rows[2] * v->v;
	result.z = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	tmp = m->rows[3] * v->v;
	result.w = tmp[0] + tmp[1] + tmp[2] + tmp[3];
	if (result.w != 1.0f && result.w != 0.0)
		result.v /= result.w;
	return (result);
}

void	matrix_identity(t_mat4 *dst)
{
	dst->rows[0] = (t_f4){1, 0, 0, 0};
	dst->rows[1] = (t_f4){0, 1, 0, 0};
	dst->rows[2] = (t_f4){0, 0, 1, 0};
	dst->rows[3] = (t_f4){0, 0, 0, 1};
}

t_mat4	matrix_transpose(const t_mat4 *m)
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
			result.m[j * 4 + i] = m->m[i * 4 + j];
			j++;
		}
		i++;
	}
	return (result);
}
