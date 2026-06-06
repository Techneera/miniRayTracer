#include "matrix.h"

float	matrix_determinant_2x2(float a, float b, float c, float d)
{
	return (a * d - b * c);
}

static void	get_indices(int row, int col, int *idx, int *idy)
{
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
}

static float	calc_cofactor_determinant(const t_mat4 *m, int *idx, int *idy)
{
	return (m->m[idx[0] * 4 + idy[0]] * matrix_determinant_2x2(m->m[idx[1] * 4
				+ idy[1]], m->m[idx[1] * 4 + idy[2]], m->m[idx[2] * 4 + idy[1]],
			m->m[idx[2] * 4 + idy[2]]) - m->m[idx[0] * 4 + idy[1]]
		* matrix_determinant_2x2(m->m[idx[1] * 4 + idy[0]], m->m[idx[1] * 4
				+ idy[2]], m->m[idx[2] * 4 + idy[0]], m->m[idx[2] * 4 + idy[2]])
		+ m->m[idx[0] * 4 + idy[2]] * matrix_determinant_2x2(m->m[idx[1] * 4
				+ idy[0]], m->m[idx[1] * 4 + idy[1]], m->m[idx[2] * 4 + idy[0]],
			m->m[idx[2] * 4 + idy[1]]));
}

float	matrix_cofactor_3x3(const t_mat4 *m, int row, int col)
{
	int	idx[3];
	int	idy[3];

	get_indices(row, col, idx, idy);
	return (calc_cofactor_determinant(m, idx, idy));
}

float	matrix_determinant(const t_mat4 *m)
{
	return (m->m[0] * matrix_cofactor_3x3(m, 0, 0) - m->m[1]
		* matrix_cofactor_3x3(m, 0, 1) + m->m[2] * matrix_cofactor_3x3(m, 0, 2)
		- m->m[3] * matrix_cofactor_3x3(m, 0, 3));
}
