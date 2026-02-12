#ifndef PATTERNS_H
# define PATTERNS_H

# include "vector.h"
# include "matrix.h"

typedef struct s_shape t_shape;

typedef enum e_pattern_type
{
	PATTERN_SOLID,
	PATTERN_STRIPE,
	PATTERN_CHECKER,
	PATTERN_GRADIENT,
	PATTERN_RING
}	t_pattern_type;

typedef struct s_pattern
{
	t_pattern_type	type;
	t_vec3			a;
	t_vec3			b;
	t_mat4			transform;
}	t_pattern;

t_pattern		pattern_constructor(t_pattern_type type, t_vec3 color_a, t_vec3 color_b);
t_pattern		pattern_solid(t_vec3 color);
t_pattern		pattern_stripe(t_vec3 color_a, t_vec3 color_b);
t_pattern		pattern_checker(t_vec3 color_a, t_vec3 color_b);
t_pattern		pattern_gradient(t_vec3 color_a, t_vec3 color_b);
t_pattern		pattern_ring(t_vec3 color_a, t_vec3 color_b);

void			set_pattern_transform(t_pattern *pattern, t_mat4 transform);

t_vec3			pattern_at(t_pattern pattern, t_vec3 point);
t_vec3			pattern_at_object(t_pattern pattern, t_shape object, t_vec3 world_point);

t_vec3			stripe_at(t_pattern pattern, t_vec3 point);
t_vec3			checker_at(t_pattern pattern, t_vec3 point);
t_vec3			gradient_at(t_pattern pattern, t_vec3 point);
t_vec3			ring_at(t_pattern pattern, t_vec3 point);

t_vec3			stripe_at_object(t_pattern pattern, t_shape object, t_vec3 world_point);

#endif