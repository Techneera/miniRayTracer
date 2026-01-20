#include "libft.h"
#include "parser.h"
#include "canvas.h"

int	parse_line(char *line, t_scene *scene)
{
	static t_parse_fn	parse[] = {
		parse_ambient_light,
		parse_camera,
		parse_light,
		parse_sphere,
		parse_plane,
		parse_cylinder,
	};
	static char			*element[] = {"A", "C", "L", "sp ", "pl ", "cy ", NULL};
	int					i;

	if (line == NULL)
		return (1);
	while (*line == ' ' || *line == '\t')
		++line;
	if (*line == '\n' || *line == '\0')
		return (0);
	i = 0;
	while (element[i] != NULL)
	{
		if (ft_strcmp(line, element[i]) == 0)
			return (parse[i](line, scene));
		++i;
	}
	return (1);
}

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
		color.x >= 0 && color.x <= RGB_MAX
		&& color.y >= 0 && color.y <= RGB_MAX
		&& color.z >= 0 && color.z <= RGB_MAX
	);
}

void	color_normalize(t_vec3 *color)
{
	color->x = round(color->x * RGB_FACTOR);
	color->y = round(color->y * RGB_FACTOR);
	color->z = round(color->z * RGB_FACTOR);
	color->w = 2.0;
}
