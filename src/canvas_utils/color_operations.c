#include "canvas.h"
#include "vector.h"

t_vec3	color_constructor(double r, double g, double b)
{
	t_vec3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	color.w = 2.0;
	return (color);
}

t_vec3	color_add(t_vec3 u, t_vec3 v)
{
	return (color_constructor(
			u.x + v.x,
			u.y + v.y,
			u.z + v.z
		)
	);
}

t_vec3	color_subtract(t_vec3 u, t_vec3 v)
{
	return (color_constructor(
			u.x - v.x,
			u.y - v.y,
			u.z - v.z
		)
	);
}

t_vec3	color_scalar(t_vec3 u, double scalar)
{
	return (color_constructor(
			u.x * scalar,
			u.y * scalar,
			u.z * scalar
		)
	);
}

t_vec3	color_multiply(t_vec3 u, t_vec3 v)
{
	return (color_constructor(
			u.x * v.x,
			u.y * v.y,
			u.z * v.z
		)
	);
}
