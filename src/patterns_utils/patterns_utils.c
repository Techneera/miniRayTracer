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

t_vec3 pattern_at_object(t_pattern pattern, const t_object *object, t_vec3 world_point)
{
	t_vec3	object_point;
	t_vec3	pattern_point;
	t_mat4	inv_obj;
	t_mat4	inv_pat;

	inv_obj = matrix_inverse(&object->transform);
	inv_pat = matrix_inverse(&pattern.transform);
	object_point = matrix_vector_multiply(
		&inv_obj,
		&world_point
	);
	pattern_point = matrix_vector_multiply(
		&inv_pat,
		&object_point
	);
	return (pattern_at(pattern, pattern_point));
}

void set_pattern_transform(t_pattern *pattern, t_mat4 transform)
{
	pattern->transform = transform;
	pattern->transform_inv = matrix_inverse(&pattern->transform);
}

t_pattern	pattern_default(void)
{
	return (pattern_constructor(
		PATTERN_SOLID,
		color_constructor(0.0f, 0.0f, 0.0f),
		color_constructor(1.0f, 1.0f, 1.0f)
	));
}
