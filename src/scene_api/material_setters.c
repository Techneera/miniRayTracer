#include "scene_api.h"
#include "matrix.h"
#include "patterns.h"

void	set_color(t_object *obj, t_vec3 color)
{
	obj->material.color = color;
	obj->material.pattern = pattern_constructor(PATTERN_SOLID, color, color);
}

void	set_pattern(t_object *obj, t_pattern_type type, t_vec3 color_a, t_vec3 color_b, float scale)
{
	t_pattern	pat;

	pat = pattern_constructor(type, color_a, color_b);
	pat.transform = matrix_scale(scale, scale, scale);
	pat.transform_inv = matrix_inverse(&pat.transform);
	obj->material.pattern = pat;
}

void	set_optics(t_object *obj, float diffuse, float specular, float reflective, float transparency, float refractive_index)
{
	obj->material.diffuse = diffuse;
	obj->material.specular = specular;
	obj->material.reflective = reflective;
	obj->material.transparency = transparency;
	obj->material.refractive_index = refractive_index;
}
