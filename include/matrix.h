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
	float	xy;
	float	xz;
	float	yx;
	float	yz;
	float	zx;
	float	zy;
}	t_shear;

void	matrix_identity(t_mat4 *dst);
t_mat4	matrix_multiply(const t_mat4 *a, const t_mat4 *b);
t_vec3	matrix_vector_multiply(const t_mat4 *m, const t_vec3 *v);
t_mat4	matrix_transpose(const t_mat4 *dst);

float	matrix_determinant_2x2(float a, float b, float c, float d);
float	matrix_cofactor_3x3(const t_mat4 *m, int row, int col);
float	matrix_determinant(const t_mat4 *m);
int		matrix_is_invertable(const t_mat4 *m);
t_mat4	matrix_inverse(const t_mat4 *m);

t_mat4	matrix_translation(float x, float y, float z);
t_mat4	matrix_scale(float x, float y, float z);
t_mat4	matrix_rot_x(float angle);
t_mat4	matrix_rot_y(float angle);
t_mat4	matrix_rot_z(float angle);

t_mat4	matrix_shear(t_shear p);
t_vec3	matrix_shearing(t_shear p, t_vec3 target);

t_mat4	align_up_vector(t_vec3 target_up);

#endif
