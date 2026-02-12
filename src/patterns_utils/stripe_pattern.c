#include "patterns.h"
#include "vector.h"
#include <math.h>

t_pattern	pattern_stripe(t_vec3 color_a, t_vec3 color_b)
{
	return (pattern_constructor(PATTERN_STRIPE, color_a, color_b));
}

t_vec3 stripe_at(t_pattern pattern, t_vec3 point)
{
	if ((int) floor(point.x) % 2 == 0)
		return (pattern.a);
	return (pattern.b);
}