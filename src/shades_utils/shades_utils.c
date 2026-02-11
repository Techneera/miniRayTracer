#include "shades.h"
#include "ray.h"
#include "canvas.h"
#include <math.h>

t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	float	dot;

	dot = vector_dot_product(in, normal);
	return (vector_sub(in, vector_scale(normal, 2.0f * dot)));
}

t_material	new_material(float ambient, float diffuse, float specular, float shininess)
{
	t_material	result;

	result.color = color_constructor(1.0, 1.0, 1.0);
	result.ambient = ambient; // STANDARD VALUE 0.1
	result.diffuse = diffuse; // STANDARD VALUE 0.9
	result.specular = specular; // STANDARD VALUE 0.9
	result.shininess = shininess; // STANDARD VALUE 200.0
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
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;

	effective_color = vector_multiply(m.color, light.intensity);
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
