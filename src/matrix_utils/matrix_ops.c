#include "vector.h"
#include "matrix.h"

void	matrix_row_constructor(double *matrix, t_vec3 this, int row)
{
	int	col;

	col = 0;
	while (col < DIM4)
	{
		matrix[row * DIM4 + col] = this.v[col];
		col++;
	}
}

void	matrix_multiply(double *m1, double *m2, double *m3)
{
	m3[0] = m1[0] * m2[0] + m1[1] * m2[4] + m1[2] * m2[8] + m1[3] * m2[12];
	m3[1] = m1[0] * m2[1] + m1[1] * m2[5] + m1[2] * m2[9] + m1[3] * m2[13];
	m3[2] = m1[0] * m2[2] + m1[1] * m2[6] + m1[2] * m2[10] + m1[3] * m2[14];
	m3[3] = m1[0] * m2[3] + m1[1] * m2[7] + m1[2] * m2[11] + m1[3] * m2[15];
	m3[4] = m1[4] * m2[0] + m1[5] * m2[4] + m1[6] * m2[8] + m1[7] * m2[12];
	m3[5] = m1[4] * m2[1] + m1[5] * m2[5] + m1[6] * m2[9] + m1[7] * m2[13];
	m3[6] = m1[4] * m2[2] + m1[5] * m2[6] + m1[6] * m2[10] + m1[7] * m2[14];
	m3[7] = m1[4] * m2[3] + m1[5] * m2[7] + m1[6] * m2[11] + m1[7] * m2[15];
	m3[8] = m1[8] * m2[0] + m1[9] * m2[4] + m1[10] * m2[8] + m1[11] * m2[12];
	m3[9] = m1[8] * m2[1] + m1[9] * m2[5] + m1[10] * m2[9] + m1[11] * m2[13];
	m3[10] = m1[8] * m2[2] + m1[9] * m2[6] + m1[10] * m2[10] + m1[11] * m2[14];
	m3[11] = m1[8] * m2[3] + m1[9] * m2[7] + m1[10] * m2[11] + m1[11] * m2[15];
	m3[12] = m1[12] * m2[0] + m1[13] * m2[4] + m1[14] * m2[8] + m1[15] * m2[12];
	m3[13] = m1[12] * m2[1] + m1[13] * m2[5] + m1[14] * m2[9] + m1[15] * m2[13];
	m3[14] = m1[12] * m2[2] + m1[13] * m2[6] + m1[14] * m2[10] + m1[15] * m2[14];
	m3[15] = m1[12] * m2[3] + m1[13] * m2[7] + m1[14] * m2[11] + m1[15] * m2[15];
}

t_vec3	matrix_vector_multiply(double *m, t_vec3 this)
{
	t_vec3	result;

	result.x = m[0] * this.v[0] + m[1] * this.v[1] + m[2] * this.v[2] + m[3] * this.v[3];
	result.y = m[4] * this.v[0] + m[5] * this.v[1] + m[6] * this.v[2] + m[7] * this.v[3];
	result.z = m[8] * this.v[0] + m[9] * this.v[1] + m[10] * this.v[2] + m[11] * this.v[3];
	result.w = m[12] * this.v[0] + m[13] * this.v[1] + m[14] * this.v[2] + m[15] * this.v[3];
	return (result);
}

void	identity_matrix_constructor(double *m)
{
	m[0] = 1.0;
	m[1] = 0.0;
	m[2] = 0.0;
	m[3] = 0.0;
	m[4] = 0.0;
	m[5] = 1.0;
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

void	matrix_transpose(double *m)
{
	double	tmp;
	int		i;
	int		j;
	int		idx_i;
	int		idx_j;

	i = 1;
	while (i < DIM4)
	{
		j = 0;
		while (j < i)
		{
			idx_i = i * DIM4 + j;
			idx_j = j * DIM4 + i;
			tmp = m[idx_i];
			m[idx_i] = m[idx_j];
			m[idx_j] = tmp;
			j++;
		}
		i++;
	}
}

double	matrix_determinant_2x2(double *m)
{
	return (m[0] * m[3] - m[1] * m[2]);
}

double	matrix_determinant_3x3(double *m)
{
	return (m[0] * (m[4] * m[8] - m[5] * m[7]) - \
m[1] * (m[3] * m[8] - m[5] * m[6]) + \
m[2] * (m[3] * m[7] - m[4] * m[6]));
}

void	submatrix_constructor_3x3(double *original, double *result, int row, int col)
{
	int	original_row;
	int	original_col;
	int	result_row;
	int	result_col;

	original_row = 0;
	result_row = 0;
	while (original_row < DIM3)
	{
		if (original_row == row)
		{
			original_row++;
			continue ;
		}
		original_col = 0;
		result_col = 0;
		while (original_col < DIM3)
		{
			if (original_col == col)
			{
				original_col++;
				continue ;
			}
			result[result_row * DIM2 + result_col] = original[original_row * DIM3 + original_col];
			result_col++;
			original_col++;
		}
		original_row++;
		result_row++;
	}
}

void	submatrix_constructor_4x4(double *original, double *result, int row, int col)
{
	int	original_row;
	int	original_col;
	int	result_row;
	int	result_col;

	result_row = 0;
	original_row = 0;
	while (original_row < DIM4)
	{
		if (original_row == row)
		{
			original_row++;
			continue ;
		}
		original_col = 0;
		result_col = 0;
		while (original_col < DIM4)
		{
			if (original_col == col)
			{
				original_col++;
				continue ;
			}
			result[result_row * DIM3 + result_col] = original[original_row * DIM4 + original_col];
			original_col++;
			result_col++;
		}
		original_row++;
		result_row++;
	}
}

double	minor_matrix_3x3(double *m, int row, int col)
{
	double	tmp[4];

	submatrix_constructor_3x3(m, tmp, row, col);
	return (matrix_determinant_2x2(tmp));
}

double	cofactor_compute_3x3(double *m, int row, int col)
{
	double	tmp;

	tmp = minor_matrix_3x3(m, row, col);
	if ((row + col) % 2 != 0)
		return (-tmp);
	return (tmp);
}

double	determinant3x3(double *m)
{
	double	det;
	int		col;

	det = 0.0;
	col = 0.0;
	while (col < DIM3)
	{
		det += m[col] * cofactor_compute_3x3(m, 0, col);
		col++;
	}
	return (det);
}

double	determinant4x4(double *m)
{
	double	det;
	double	submatrix[9];
	double	minor;
	int		col;

	det = 0.0;
	col = 0.0;
	while (col < DIM4)
	{
		submatrix_constructor_4x4(m, submatrix, 0, col);
		minor = matrix_determinant_3x3(submatrix);
		if (col % 2 == 0)
			det += m[col] * minor;
		else
			det -= m[col] * minor;
		col++;
	}
	return (det);
}

double	determinant(double *m, int size)
{
	if (size == 2)
		return (matrix_determinant_2x2(m));
	else if (size == 3)
		return (matrix_determinant_3x3(m));
	else if (size == 4)
		return (determinant4x4(m));
	return (0.0);
}
