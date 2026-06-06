#include "ray.h"

bool	check_caps(const t_ray *ray, float t)
{
	float	x;
	float	z;

	x = ray->origin.x + ray->direction.x * t;
	z = ray->origin.z + ray->direction.z * t;
	return ((x * x + z * z) <= 1.0f + EPSILON);
}
