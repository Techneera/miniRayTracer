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

float	vector_length(t_vec3 u)
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
