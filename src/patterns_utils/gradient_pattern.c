#include "patterns.h"
#include "vector.h"
#include <math.h>

t_pattern	pattern_gradient(t_vec3 color_a, t_vec3 color_b)
{
	return (pattern_constructor(PATTERN_GRADIENT, color_a, color_b));
}

t_vec3	gradient_at(t_pattern pattern, t_vec3 point)
{
	t_vec3	distance;
	float	fraction;

	distance = vector_sub(pattern.b, pattern.a);
	fraction = point.x - floorf(point.x);
	return (vector_add(pattern.a, vector_scale(distance, fraction)));
}

