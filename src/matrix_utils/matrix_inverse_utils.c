#include "matrix.h"

static void	calculate_inverse_element(const t_mat4 *m, t_mat4 *result,
		float inv_det)
{
	float	sign;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			sign = 1.0f - (2.0f * ((i + j) % 2));
			result->m[j * 4 + i] = matrix_cofactor_3x3(m, i, j) * inv_det
				* sign;
		}
	}
}

t_mat4	matrix_inverse(const t_mat4 *m)
{
	t_mat4	result;
	float	det;
	float	inv_det;

	det = matrix_determinant(m);
	if (fabsf(det) < 1e-6)
	{
		matrix_identity(&result);
		return (result);
	}
	inv_det = 1.0f / det;
	calculate_inverse_element(m, &result, inv_det);
	return (result);
}

int	matrix_is_invertable(const t_mat4 *m)
{
	float	det;

	det = matrix_determinant(m);
	if (fabsf(det) < 1e-6)
		return (0);
	return (1);
}
