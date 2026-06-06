#include "vector.h"

t_vec3	vector_multiply(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result.v = u.v * v.v;
	return (result);
}
