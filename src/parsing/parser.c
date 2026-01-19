#include "parser.h"
#include "librt.h"
#include "vector.h"

//int	parse_line(char *line, t_scene *scene)
//{
//	if (line == NULL)
//		return (1);
//	while (*line == ' ' || *line == '\t')
//		++line;
//	if (*line == '\n' || *line == '\0')
//		return (0);
//	if (line[0] == 'A' && line[1] == ' ') // parse_ambient_light()
//		;
//	else if (line[0] == 'C' && line[1] == ' ') // parse_camera()
//		;
//	else if (line[0] == 'L' && line[1] == ' ') // parse_light()
//		;
//	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ') // parse_sphere()
//		;
//	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ') // parse_plane()
//		;
//	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ') // parse_cylinder()
//		;
//	return (0);
//}

int	parse_float(char **line, float *value)
{
	int	error;
	
	error = 0;
	*value = ft_atof(line, &error);
	return (error);
}

int	parse_vec3(char **line, t_vec3 *v)
{
	if (parse_float(line, &v->x) != 0
		|| parse_float(line, &v->y) != 0
	 	|| parse_float(line, &v->z) != 0)
		return (1);
	return (0);
}

bool	is_valid_color(t_vec3 color)
{
	return (
		color.x >= 0 && color.x <= 255.0
		&& color.y >= 0 && color.y <= 255.0
		&& color.z >= 0 && color.z <= 255.0
	);
}

void	parse_ambient_light(char **line, t_scene *scene)
{
	*line = skip_to_next(*line);
	if (parse_float(line, &scene->a_light.ratio) != 0
		|| parse_vec3(line, &scene->a_light.color) != 0)
		exit(1);
	if (scene->a_light.ratio < 0.0 || scene->a_light.ratio > 1.0)
		exit(1);
	if (is_valid_color(scene->a_light.color) != true)
		exit(1);
}
