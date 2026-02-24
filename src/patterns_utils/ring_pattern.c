#include "patterns.h"
#include "vector.h"
#include <math.h>

t_pattern	pattern_ring(t_vec3 color_a, t_vec3 color_b)
{
	return (pattern_constructor(PATTERN_RING, color_a, color_b));
}

t_vec3 ring_at(t_pattern pattern, t_vec3 point)
{
	float result;

	result = sqrtf(point.x * point.x + point.z * point.z);
	if ((int) floorf(result) % 2 == 0)
		return (pattern.a);
	return (pattern.b);
}
