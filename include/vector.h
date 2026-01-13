#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_vec3
{
	union // Union for improved redability
	{
		struct
		{
			double	x; // X-axis
			double	y; // Y-axis
			double	z; // Z-axis
			double	w; // 1 for points \ 0 for vector
		};
		double	v[4]; // Array access for fast computation
	};
}	t_vec3;

t_vec3	point_constructor(double x, double y, double z);
t_vec3	vector_constructor(double x, double y, double z);
double	vector_length_squared(const t_vec3 u);
double	vector_length(const t_vec3 u);
t_vec3	vector_normalization(const t_vec3 u);
double	vector_dot_product(const t_vec3 u, const t_vec3 v);
t_vec3	vector_cross_product(const t_vec3 u, const t_vec3 v);
t_vec3	vector_add(const t_vec3 u, const t_vec3 v);
t_vec3	vector_sub(const t_vec3 u, const t_vec3 v);
t_vec3	vector_scale(const t_vec3 u, double scalar);

#endif
