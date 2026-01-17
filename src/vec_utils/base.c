#include "vector.h"

t_vec3	point_constructor(float x, float y, float z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 1.0f;
	return (result);
}

t_vec3	vector_constructor(float x, float y, float z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 0.0f;
	return (result);
}

float	vector_length_squared(t_vec3 u)
{
	return (u.x * u.x + u.y * u.y + u.z * u.z);
}

float	vector_length( t_vec3 u)
{
	float	dot;

	dot = vector_dot_product(u, u);
	if (dot == 0.0f)
		return (0.0f);
	return (sqrtf(dot));
}

t_vec3	vector_normalization(t_vec3 u)
{
	float	len;
	float	inv_len;

	len = vector_length(u);
	if (len == 0.0f)
		return (u);
	inv_len = 1.0f / len;
	return (vector_scale(u, inv_len));
}

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
