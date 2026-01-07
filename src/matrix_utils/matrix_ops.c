#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"

# define DIM4 4
# define DIM16 16

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

t_vec3	matrix_vector_multiply(double *m, t_vec3 v)
{
	t_vec3	result;

	result.x = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3];
	result.y = m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7] * v[3];
	result.z = m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11] * v[3];
	result.w = m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3];
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
		while (j < DIM4)
		{
			idx_i = i * DIM4 + j;
			idx_j = j * DIM4 + i;
			tmp = m[idx_i];
			m[idx_i] = m[idxj];
			m[idx_j] = tmp;
		}
		j++;
	}
	i++;
}

/*
int	main(void)
{
	double	matrix1[16];
	double	matrix2[16];
	double	matrix3[16];
	int		i = 0;
	//double	matrix2[16];
	//double	matrix3[16];
	//int		i;
	//int		j;
	
	t_vec3	v = vector_constructor(1.0, 3.0, 4.0);
	for(i = 0; i < DIM; i++)
		matrix_row_constructor(matrix1, v, i);

	t_vec3 v2 = vector_constructor(5.0, -3.0, 1.0);
	for(i = 0; i < DIM; i++)
		matrix_row_constructor(matrix2, v2, i);
	matrix_multiply(matrix1, matrix2, matrix3);
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if ((i + 1) % 2 != 0)
				matrix[i * DIM + j] = i * 4 + j + 1;
			else
				matrix[i * DIM + j] = i * 4 + j + 1.5;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < DIM)
	{
		j = 0;
		while (j < DIM)
		{
			matrix2[i * DIM + j] = i + j;
			j++;
		}
		i++;
	}

	if (matrix_compare(matrix, matrix2, 1e-10))
		exit(1);
	if (matrix_compare(matrix, matrix3, 1e-10))
		exit(1);
	exit(0);
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("Position (%d, %d):\t%.1f\n", i, j, matrix[i][j]);
		}
	}
}
*/
