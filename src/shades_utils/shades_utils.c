#include "canvas.h"
#include "patterns.h"
#include "ray.h"
#include "scene.h"
#include "shades.h"
#include "vector.h"

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	float	dot;

	dot = vector_dot_product(in, normal);
	return (vector_sub(in, vector_scale(normal, 2.0f * dot)));
}

t_light	light_constructor(t_vec3 position, t_vec3 color, float brightness)
{
	t_light	l;

	l.position = position;
	l.color = color;
	l.brightness = brightness;
	return (l);
}

t_material	material_default(void)
{
	t_pattern	pattern;
	t_material	material;

	pattern = pattern_constructor(PATTERN_SOLID, color_constructor(0, 0, 0),
			color_constructor(1, 1, 1));
	material.color = color_constructor(1.0f, 1.0f, 1.0f);
	material.ambient = 0.1f;
	material.diffuse = 0.8f;
	material.specular = 0.2f;
	material.shininess = 32.0f;
	material.reflective = 0.0f;
	material.transparency = 0.0f;
	material.refractive_index = 1.0f;
	material.pattern = pattern;
	return (material);
}
