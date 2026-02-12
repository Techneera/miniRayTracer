#include "canvas.h"
#include "patterns.h"
#include "vector.h"
#include "ray.h"
#include "matrix.h"

t_pattern	pattern_constructor(t_pattern_type type, t_vec3 color_a, t_vec3 color_b)
{
	t_pattern	pattern;

	pattern.type = type;
	pattern.a = color_a;
	pattern.b = color_b;
	matrix_identity(&pattern.transform);
	return (pattern);
}

t_vec3 pattern_at(t_pattern pattern, t_vec3 point)
{
	if (pattern.type == PATTERN_STRIPE)
		return (stripe_at(pattern, point));
	else if (pattern.type == PATTERN_GRADIENT)
		return (gradient_at(pattern, point));
	else if (pattern.type == PATTERN_RING)
		return (ring_at(pattern, point));
	else if (pattern.type == PATTERN_CHECKER)
		return (checker_at(pattern, point));
	return (color_constructor(point.x, point.y, point.z));
}

t_vec3 pattern_at_object(t_pattern pattern, t_shape object, t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	pattern_point;

	object_point = matrix_vector_multiply(
		matrix_inverse(object.transform),
		world_point
	);
	pattern_point = matrix_vector_multiply(
		matrix_inverse(pattern.transform),
		object_point
	);
	return (pattern_at(pattern, pattern_point));
}

void set_pattern_transform(t_pattern *pattern, t_mat4 transform)
{
	pattern->transform = transform;
}
