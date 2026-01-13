#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

# define DIM2 2
# define DIM3 3
# define DIM4 4

typedef struct s_shear
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
}	t_shear;

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
void	matrix_inverse(double *m);

void	matrix_translation_constructor(double *m_trans, double x, double y, double z);
t_vec3	matrix_translation(double *translation_matrix, t_vec3 point_trans, t_vec3 point_target);
t_vec3	matrix_inverse_translation(double *translation_matrix, t_vec3 point_trans, t_vec3 point_target);
void	matrix_scale_constructor(double *scale_matrix, t_vec3 point);
t_vec3	matrix_scale(double *scale_matrix, t_vec3 point_scale, t_vec3 point_target);
t_vec3	matrix_scale_inverse(double *scale_matrix, t_vec3 point_scale, t_vec3 point_target);
void	rotation_x_constructor(double *m, double angle);
void	rotation_y_constructor(double *m, double angle);
void	rotation_z_constructor(double *m, double angle);
t_vec3	matrix_rotation(t_vec3 point_target, double angle, void(*f)(double *, double));
void	matrix_shear_constructor(double *m, t_shear proportions);
t_vec3	matrix_shearing(t_vec3 point_target, t_shear proportions);
#endif
