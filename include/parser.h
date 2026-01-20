#ifndef PARSER_H
# define PARSER_H

# include "librt.h"
# include <stdlib.h>
# include <stdbool.h>

# define RGB_FACTOR 0.00392156862745

int		parse_line(char *line, t_scene *scene);

int		parse_ambient_light(char **line, t_scene *scene);

char	*skip_to_next(char *ptr);
float	ft_atof(char **ptr, int *error);

#endif
