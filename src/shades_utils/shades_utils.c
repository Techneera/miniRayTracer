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

t_material	new_material(float ambient, float diffuse, float specular, float shininess, float reflective, t_pattern pattern)
{
	t_material	result;

	result.color = color_constructor(1.0, 1.0, 1.0);
	result.ambient = ambient; // STANDARD VALUE 0.1
	result.diffuse = diffuse; // STANDARD VALUE 0.9
	result.specular = specular; // STANDARD VALUE 0.9
	result.shininess = shininess; // STANDARD VALUE 200.0
	result.reflective = reflective; // STANDARD VALUE 0.0
	result.pattern = pattern;
	return (result);
}

t_point_light	point_light(t_vec3 position, t_vec3 intensity)
{
	t_point_light	l;

	l.position = position;
	l.intensity = intensity;
	return (l);
}

/*
** Calculates the color of a point based on the Phong Reflection Model.
**
** @param m: The material of the surface.
** @param light: The light source.
** @param point: The point on the surface being illuminated.
** @param eyev: The vector from the point to the camera (normalized).
** @param normalv: The surface normal at the point (normalized).
*/
t_vec3			lighting(t_material m, t_point_light light, t_vec3 point, t_vec3 eyev, t_vec3 normalv, bool in_shadow)
{
	t_vec3	effective_color;
	t_vec3	lightv;
	t_vec3	ambient;
	t_vec3	reflectv;
	t_vec3	diffuse;
	t_vec3	specular;
	t_vec3	color;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;

	if (m.pattern.type != PATTERN_SOLID)
		color = pattern_at(m.pattern, point);
	else
		color = m.color;
	effective_color = vector_multiply(color, light.intensity);
	lightv = vector_normalization(vector_sub(light.position, point));
	ambient = vector_scale(effective_color, m.ambient);
	if (in_shadow == true)
		return (ambient);
	light_dot_normal = vector_dot_product(lightv, normalv);
	if (light_dot_normal < 0.0f)
	{
		diffuse = color_constructor(0.0, 0.0, 0.0);
		specular = color_constructor(0.0, 0.0, 0.0);
	}
	else
	{
		diffuse = vector_scale(effective_color, m.diffuse * light_dot_normal);
		reflectv = reflect(vector_scale(lightv, -1.0), normalv);
		reflect_dot_eye = vector_dot_product(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = color_constructor(0.0, 0.0, 0.0);
		else
		{
			factor = powf(reflect_dot_eye, m.shininess);
			specular = vector_scale(light.intensity, m.specular * factor);
		}
	}
	return (vector_add(vector_add(ambient, diffuse), specular));
}

t_vec3	reflected_color(t_world *world, t_computation computations)
{
	(void)world;
	(void)computations;

	return (color_constructor(0.0, 0.0, 0.0));
}

t_material	material_default(void)
{
	t_pattern	pattern;

	pattern = pattern_constructor(
		PATTERN_SOLID,
		color_constructor(0, 0, 0),
		color_constructor(1, 1, 1)
	);
	return (new_material(0.1f, 0.9f, 0.9f, 200.0f, 0.0f, pattern));
}
