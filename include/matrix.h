#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct __attribute__((aligned(32))) s_mat4
{
	union
	{
		float	m[16];
		t_f4	rows[4];
	};
}	t_mat4;

typedef struct s_shear
{
	double	xy;
	double	xz;
	double	yx;
	double	yz;
	double	zx;
	double	zy;
}	t_shear;

void	matrix_identity(t_mat4 *dst);
t_mat4	matrix_multiply(t_mat4 a, t_mat4 b);
t_vec3	matrix_vector_multiply(t_mat4 m, t_vec3 v);
t_mat4	matrix_transpose(t_mat4 dst);

float	matrix_determinant_2x2(float a, float b, float c, float d);
float	matrix_cofactor_3x3(t_mat4 m, int row, int col);
float	matrix_determinant(t_mat4 m);
int		matrix_is_invertable(t_mat4 m);
t_mat4	matrix_inverse(t_mat4 m);

t_mat4	matrix_translation(float x, float y, float z);
t_mat4	matrix_scale(float x, float y, float z);
t_mat4	matrix_rot_x(float angle);
t_mat4	matrix_rot_y(float angle);
t_mat4	matrix_rot_z(float angle);

void	matrix_inverse(t_mat4 m);

double	matrix_determinant(duble *m, int size);

void	matrix_shear_constructor(double *m, t_shear proportions);
t_vec3	matrix_shearing(t_vec3 point_target, t_shear proportions);
#endif
