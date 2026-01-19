#ifndef PARSER_H
# define PARSER_H

# include "librt.h"
# include <stdlib.h>
# include <stdbool.h>

int		parse_line(char *line, t_scene *scene);

void	parse_ambient_light(char **line, t_scene *scene);

char	*skip_to_next(char *ptr);
float	ft_atof(char **ptr, int *error);

#endif
