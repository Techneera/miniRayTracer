#include "vector.h"

float	vector_dot_product(t_vec3 u, t_vec3 v)
{
	t_vec3	tmp;

	tmp.v = u.v * v.v;
	return (tmp.x + tmp.y + tmp.z);
}

t_vec3	vector_cross_product(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	result.w = 0.0f;
	return (result);
}

t_vec3	vector_add(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.v = u.v + v.v;
	return (result);
}

t_vec3	vector_sub(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.v = u.v - v.v;
	return (result);
}

t_vec3	vector_scale(t_vec3 u, float scalar)
{
	t_vec3	result;

	result.v = u.v * scalar;
	return (result);
}
