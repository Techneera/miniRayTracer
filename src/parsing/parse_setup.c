#include "parser.h"
#include "vector.h"

int	parse_ambient_light(char *line, t_scene *scene)
{
	line = skip_to_next(line);
	if (parse_float(&line, &scene->a_light.ratio) != 0)
		return (1);
	if (scene->a_light.ratio < 0.0 || scene->a_light.ratio > 1.0)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &scene->a_light.color) != 0
		|| is_valid_color(scene->a_light.color) != true)
		return (1);
	scene->a_light.color.x = round(scene->a_light.color.x * RGB_FACTOR);
	scene->a_light.color.y = round(scene->a_light.color.y * RGB_FACTOR);
	scene->a_light.color.z = round(scene->a_light.color.z * RGB_FACTOR);
	return (0);
}

bool	is_valid_direction(t_vec3 v)
{
	return (
		v.x >= -1.0 && v.x <= 1.0
		&& v.y >= -1.0 && v.y <= 1.0
		&& v.z >= -1.0 && v.z <= 1.0
	);
}

int	parse_camera(char *line, t_scene *scene)
{
	line = skip_to_next(line);
	if (parse_vec3(&line, &scene->camera.position) != 0)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &scene->camera.direction) != 0
	 	|| is_valid_direction(scene->camera.direction) != 0)
		return (1);
	line = skip_to_next(line);
	if (parse_float(&line, &scene->camera.fov) != 0
		|| scene->camera.fov < 0 || scene->camera.fov > 180.0)
		return (1);
	return (0);
}

int	parse_light(char *line, t_scene *scene);
