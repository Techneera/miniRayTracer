#include "canvas.h"
#include "patterns.h"
#include "ray.h"
#include "scene.h"
#include "shades.h"
#include "vector.h"
#include <math.h>

static t_lighting_base	lighting_base_values(t_material m,
		const t_object *obj,
		t_lighting_data data)
{
	t_lighting_base	base;
	t_vec3			color;

	if (m.pattern.type != PATTERN_SOLID)
		color = pattern_at_object(m.pattern, obj, data.point);
	else
		color = m.color;
	base.light_intensity = vector_scale(data.light->color,
			data.light->brightness);
	base.effective_color = vector_multiply(color, base.light_intensity);
	base.ambient = vector_multiply(color, vector_scale(data.a_light->color,
				data.a_light->ratio * m.ambient));
	return (base);
}

static t_vec3	lighting_specular(t_material m, t_lighting_data data,
		t_vec3 light_intensity, t_vec3 lightv)
{
	t_vec3	reflectv;
	float	reflect_dot_eye;
	float	factor;

	reflectv = reflect(vector_scale(lightv, -1.0f), data.normalv);
	reflect_dot_eye = vector_dot_product(reflectv, data.eyev);
	if (reflect_dot_eye <= 0.0f)
		return (color_constructor(0.0f, 0.0f, 0.0f));
	factor = powf(reflect_dot_eye, m.shininess);
	return (vector_scale(light_intensity, m.specular * factor));
}

static t_vec3	lighting_diffuse_specular(t_material m, t_lighting_data data,
		t_lighting_base base)
{
	t_vec3	lightv;
	t_vec3	diffuse;
	float	light_dot_normal;

	lightv = vector_normalization(vector_sub(data.light->position, data.point));
	light_dot_normal = vector_dot_product(lightv, data.normalv);
	if (light_dot_normal < 0.0f)
		return (color_constructor(0.0f, 0.0f, 0.0f));
	diffuse = vector_scale(base.effective_color, m.diffuse * light_dot_normal);
	return (vector_add(diffuse,
			lighting_specular(m, data, base.light_intensity, lightv)));
}

t_vec3	lighting(t_material m, const t_object *obj, t_lighting_data data)
{
	t_lighting_base	base;

	base = lighting_base_values(m, obj, data);
	if (data.in_shadow)
		return (base.ambient);
	return (vector_add(base.ambient, lighting_diffuse_specular(m, data, base)));
}
