#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

# define DIM2 2
# define DIM3 3
# define DIM4 4

void	matrix_row_constructor(double *matrix, t_vec3 this, int row);
void	matrix_multiply(double *m1, double *m2, double *m3);
t_vec3	matrix_vector_multiply(double *m, t_vec3 v);
void	identity_matrix_constructor(double *m);
void	matrix_transpose(double *m);
double	matrix_determinant_2x2(double *m);
double	matrix_determinant_3x3(double *m);
void	submatrix_constructor_3x3(double *original, double *result, int row, int column);
void	submatrix_constructor_4x4(double *original, double *result, int row, int column);
double	minor_matrix_3x3(double *m, int row, int col);
double	cofactor_compute_3x3(double *m, int row, int col);
double	determinant3x3(double *m);
double	determinant4x4(double *m);
double	determinant(double *m, int size);
int		matrix_invertability(double *m);

void	matrix_translation_constructor(double *m_trans, double x, double y, double z);
#endif
