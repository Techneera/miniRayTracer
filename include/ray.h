#ifndef RAY_H
# define RAY_H

#include "vector.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

t_ray	ray_constructor(t_vec3 origin, t_vec3 direction);

#endif
