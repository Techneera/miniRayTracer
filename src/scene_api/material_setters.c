#include "matrix.h"
#include "patterns.h"
#include "scene_api.h"

void	set_color(t_object *obj, t_vec3 color)
{
	obj->material.color = color;
	obj->material.pattern = pattern_constructor(PATTERN_SOLID, color, color);
}

t_pattern	pattern_scaled(t_pattern_type type, t_vec3 color_a,
		t_vec3 color_b, float scale)
{
	t_pattern	pat;

	pat = pattern_constructor(type, color_a, color_b);
	pat.transform = matrix_scale(scale, scale, scale);
	pat.transform_inv = matrix_inverse(&pat.transform);
	return (pat);
}

void	set_pattern(t_object *obj, t_pattern pattern)
{
	obj->material.pattern = pattern;
}

void	set_optics(t_object *obj, t_optics_params params)
{
	obj->material.diffuse = params.diffuse;
	obj->material.specular = params.specular;
	obj->material.reflective = params.reflective;
	obj->material.transparency = params.transparency;
	obj->material.refractive_index = params.refractive_index;
}
