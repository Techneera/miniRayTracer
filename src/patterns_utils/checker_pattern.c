#include "patterns.h"
#include "vector.h"
#include <math.h>

t_vec3 checker_at(t_pattern pattern, t_vec3 point)
{
	float	result;

	result = fabsf(point.x) + fabsf(point.y) + fabsf(point.z);
	if ((int) result % 2 == 0)
		return (pattern.a);
	return (pattern.b);
}