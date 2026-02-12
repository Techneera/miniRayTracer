#include "canvas.h"
#include "patterns.h"
#include "vector.h"

t_pattern	pattern_constructor(t_pattern_type type, t_vec3 color_a, t_vec3 color_b)
{
	t_pattern	pattern;

	pattern.type = type;
	pattern.a = color_a;
	pattern.b = color_b;
	return (pattern);
}

t_vec3 pattern_at(t_pattern pattern, t_vec3 point)
{
	if (pattern.type == PATTERN_STRIPE)
		return (stripe_at(pattern, point));
	return (color_constructor(0, 0, 0));
}