#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <math.h>
# include <stdbool.h>

typedef float t_f4 __attribute__((vector_size(16)));

typedef struct __attribute__((aligned(16))) s_vec3
{
	union // Union for improved redability
	{
		t_f4	v; // Array access for fast computation
		struct
		{
			float	x; // X-axis
			float	y; // Y-axis
			float	z; // Z-axis
			float	w; // 1 for points \ 0 for vector
		};
	};
}	t_vec3;

t_vec3	point_constructor(float x, float y, float z);
t_vec3	vector_constructor(float x, float y, float z);
float	vector_length_squared(t_vec3 u);
float	vector_length(t_vec3 u);
t_vec3	vector_normalization(t_vec3 u);
float	vector_dot_product(t_vec3 u, t_vec3 v);
t_vec3	vector_cross_product(t_vec3 u, t_vec3 v);
t_vec3	vector_add(t_vec3 u, t_vec3 v);
t_vec3	vector_sub(t_vec3 u, t_vec3 v);
t_vec3	vector_scale(t_vec3 u, float scalar);
t_vec3	vector_multiply(t_vec3 u, t_vec3 v);

#endif
