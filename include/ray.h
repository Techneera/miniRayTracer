#ifndef RAY_H
# define RAY_H

#include "vector.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_sphere
{
	int		id;
	t_vec3	center;
	double	radius;
}	t_sphere;

typedef struct s_intersect
{
	int		count;
	double	t[2];
}	t_intersect;

struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
};

t_ray		ray_constructor(t_vec3 origin, t_vec3 direction);
t_vec3		ray_position(t_ray ray, double t);

t_sphere	sphere(void);
t_intersect	sphere_intersect(t_ray ray, t_sphere sphere);

#endif
