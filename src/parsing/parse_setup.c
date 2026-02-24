#include "parser.h"
#include "scene.h"
#include "vector.h"

int	parse_ambient_light(char *line, t_scene *scene)
{
	line = skip_to_next(line);
	if (parse_float(&line, &scene->world.a_light.ratio) != 0)
		return (1);
	if (scene->world.a_light.ratio < 0.0 || scene->world.a_light.ratio > 1.0)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &scene->world.a_light.color) != 0
		|| is_valid_color(scene->world.a_light.color) != true)
		return (1);
	color_normalize(&scene->world.a_light.color);
	return (0);
}

bool	is_valid_direction(t_vec3 v)
{
	return (
		v.x >= -1.0f && v.x <= 1.0f
		&& v.y >= -1.0f && v.y <= 1.0f
		&& v.z >= -1.0f && v.z <= 1.0f
		&& !(fabs(v.x) < EPSILON && fabs(v.y) < EPSILON && fabs(v.z) < EPSILON)
	);
}

int	parse_camera(char *line, t_scene *scene)
{
	t_vec3	pos;
	t_vec3	dir;
	float	fov;
	t_vec3	to;
	t_vec3	up;

	line = skip_to_next(line);
	if (parse_vec3(&line, &pos) != 0)
		return (1);
	pos.w = 1.0f;
	line = skip_to_next(line);
	if (parse_vec3(&line, &dir) != 0
	 	|| !is_valid_direction(dir))
		return (1);
	dir = vector_normalization(dir);
	dir.w = 0.0f;
	line = skip_to_next(line);
	if (parse_float(&line, &fov) != 0
		|| fov < 0.0f || fov > 180.0f)
		return (1);
	scene->camera = camera_constructor(WIN_WIDTH, WIN_HEIGHT, fov);
	to = vector_add(pos, dir);
	up = vector_constructor(0.0f, 1.0f, 0.0f);
	scene->camera.transform = view_transform(pos, to, up);
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	line = skip_to_next(line);
	if (parse_vec3(&line, &scene->world.light.position) != 0)
		return (1);
	scene->world.light.position.w = 1.0f;
	line = skip_to_next(line);
	if (parse_float(&line, &scene->world.light.brightness) != 0
		|| scene->world.light.brightness < 0.0f || scene->world.light.brightness > 1.0f)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &scene->world.light.color) != 0
		|| is_valid_color(scene->world.light.color) != true)
		return (1);
	color_normalize(&scene->world.light.color);
	return (0);
}
