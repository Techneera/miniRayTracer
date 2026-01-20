#include "parser.h"

int	parse_ambient_light(char **line, t_scene *scene)
{
	*line = skip_to_next(*line);
	if (parse_float(line, &scene->a_light.ratio) != 0)
		return (1);
	if (scene->a_light.ratio < 0.0 || scene->a_light.ratio > 1.0)
		return (1);
	*line = skip_to_next(*line);
	if (parse_vec3(line, &scene->a_light.color) != 0)
		return (1);
	if (is_valid_color(scene->a_light.color) != true)
		return (1);
	scene->a_light.color.x = round(scene->a_light.color.x * RGB_FACTOR);
	scene->a_light.color.y = round(scene->a_light.color.y * RGB_FACTOR);
	scene->a_light.color.z = round(scene->a_light.color.z * RGB_FACTOR);
	return (0);
}
