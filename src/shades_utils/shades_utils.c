#include "patterns.h"
#include "shades.h"
#include "ray.h"
#include "canvas.h"
#include "scene.h"
#include "vector.h"
#include <math.h>

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	float	dot;

	dot = vector_dot_product(in, normal);
	return (vector_sub(in, vector_scale(normal, 2.0f * dot)));
}

t_material	new_material(float ambient, float diffuse, float specular, float shininess, float reflective, float transparency, float refractive_index, t_pattern pattern)
{
	t_material	result;

	result.color = color_constructor(1.0, 1.0, 1.0);
	result.ambient = ambient; // STANDARD VALUE 0.1
	result.diffuse = diffuse; // STANDARD VALUE 0.9
	result.specular = specular; // STANDARD VALUE 0.9
	result.shininess = shininess; // STANDARD VALUE 200.0
	result.reflective = reflective; // STANDARD VALUE 0.0
	result.transparency = transparency; // STANDARD VALUE 1.0
	result.refractive_index = refractive_index; // STANDARD VALUE 1.5
	result.pattern = pattern;
	return (result);
}

t_light	light_constructor(t_vec3 position, t_vec3 color, float brightness)
{
	t_light	l;

	l.position = position;
	l.color = color;
	l.brightness = brightness;
	return (l);
}

/*
** Calculates the color of a point based on the Phong Reflection Model.
**
** @param m:         The material of the surface.
** @param obj:       The object being illuminated (replacing t_shape).
** @param light:     The point light source.
** @param a_light:   The global ambient light for the scene.
** @param point:     The point on the surface being illuminated.
** @param eyev:      The vector from the point to the camera (normalized).
** @param normalv:   The surface normal at the point (normalized).
** @param in_shadow: Boolean flag indicating if the point is obscured.
*/
t_vec3 lighting(t_material m, const t_object *obj, const t_light *light, const t_ambient_light *a_light, t_vec3 point, t_vec3 eyev, t_vec3 normalv, bool in_shadow)
{
	t_vec3  color;
	t_vec3  light_intensity;
	t_vec3  effective_color;
	t_vec3  lightv;
	t_vec3  ambient;
	t_vec3  diffuse;
	t_vec3  specular;
	t_vec3  reflectv;
	float   light_dot_normal;
	float   reflect_dot_eye;
	float   factor;
	
	if (m.pattern.type != PATTERN_SOLID)
		color = pattern_at_object(m.pattern, obj, point);
	else
		color = m.color;
	
	light_intensity = vector_scale(light->color, light->brightness);
	effective_color = vector_multiply(color, light_intensity);
	ambient = vector_multiply(color, vector_scale(a_light->color, a_light->ratio * m.ambient));
	if (in_shadow)
		return (ambient);
	lightv = vector_normalization(vector_sub(light->position, point));
	light_dot_normal = vector_dot_product(lightv, normalv);
	if (light_dot_normal < 0.0f)
	{
		diffuse = color_constructor(0.0f, 0.0f, 0.0f);
		specular = color_constructor(0.0f, 0.0f, 0.0f);
	}
	else
	{
		diffuse = vector_scale(effective_color, m.diffuse * light_dot_normal);
		reflectv = reflect(vector_scale(lightv, -1.0f), normalv);
		reflect_dot_eye = vector_dot_product(reflectv, eyev);
		if (reflect_dot_eye <= 0.0f)
			specular = color_constructor(0.0f, 0.0f, 0.0f);
		else
		{
			factor = powf(reflect_dot_eye, m.shininess);
			specular = vector_scale(light_intensity, m.specular * factor);
		}
	}
	return (vector_add(vector_add(ambient, diffuse), specular));
}

t_material	material_default(void)
{
	t_pattern	pattern;

	pattern = pattern_constructor(
		PATTERN_SOLID,
		color_constructor(0, 0, 0),
		color_constructor(1, 1, 1)
	);
	return (new_material(0.1f, 0.8f, 0.2f, 32.0f, 0.0f, 0.0f, 1.0f, pattern));
}
