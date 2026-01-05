#include "vector.h"

inline
t_vec3	point_constructor(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 1.0;
	return (result);
}

inline
t_vec3	vector_constructor(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 0.0;
	return (result);
}

inline
double	vector_length_squared(const t_vec3 u)
{
	return (u.x * u.x + u.y * u.y + u.z * u.z);
}

inline
double	vector_length(const t_vec3 u)
{
	return (sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}

inline
t_vec3	vector_normalization(const t_vec3 u)
{
	double	len;
	t_vec3	result;

	len = vector_length(u);
	if (len > 0.0)
	{
		len = 1.0 / len;
		result.x = u.x * len;
		result.y = u.y * len;
		result.z = u.z * len;
		result.w = u.w;
		return (result);
	}
	result.x = 0.0;
	result.y = 0.0;
	result.z = 0.0;
	result.w = u.w;
	return (result);
}

inline
double	vector_dot_product(const t_vec3 u, const t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

inline
t_vec3	vector_cross_product(const t_vec3 u, const t_vec3 v)
{
	t_vec3	result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	result.w = 0.0;
	return (result);
}

inline
t_vec3	vector_add(const t_vec3 u, const t_vec3 v)
{
	t_vec3	result;

	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	result.w = 0.0;
	return (result);
}

inline
t_vec3	vector_sub(const t_vec3 u, const t_vec3 v)
{
	t_vec3	result;

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	result.w = 0.0;
	return (result);
}

inline
t_vec3	vector_scale(const t_vec3 u, double scalar)
{
	t_vec3	result;

	result.x = u.x * scalar;
	result.y = u.y * scalar;
	result.z = u.z * scalar;
	result.w = u.w;
	return (result);
}
