#include "patterns.h"
#include "vector.h"
#include <math.h>

t_pattern	pattern_checker(t_vec3 color_a, t_vec3 color_b)
{
	return (pattern_constructor(PATTERN_CHECKER, color_a, color_b));
}

t_vec3 checker_at(t_pattern pattern, t_vec3 point)
{
	float	result;

	result = fabsf(point.x) + fabsf(point.y) + fabsf(point.z);
	if ((int) result % 2 == 0)
		return (pattern.a);
	return (pattern.b);
}
