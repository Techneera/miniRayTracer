#include "parser.h"

int	parse_line(char *line, t_scene *scene)
{
	if (line == NULL)
		return (1);
	while (*line == ' ' || *line == '\t')
		++line;
	if (*line == '\n' || *line == '\0')
		return (0);
	if (line[0] == 'A' && line[1] == ' ') // parse_ambient_light()
		;
	else if (line[0] == 'C' && line[1] == ' ') // parse_camera()
		;
	else if (line[0] == 'L' && line[1] == ' ') // parse_light()
		;
	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ') // parse_sphere()
		;
	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ') // parse_plane()
		;
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ') // parse_cylinder()
		;
	return (0);
}
