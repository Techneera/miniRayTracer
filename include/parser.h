#ifndef PARSER_H
# define PARSER_H

# include "librt.h"
# include <stdlib.h>
# include <stdbool.h>

# define RGB_FACTOR 0.00392156862745

int		parse_line(char *line, t_scene *scene);
int		parse_float(char **line, float *value);
int		parse_vec3(char **line, t_vec3 *v);
bool	is_valid_color(t_vec3 color);

int		parse_ambient_light(char **line, t_scene *scene);

char	*skip_to_next(char *ptr);
float	ft_atof(char **ptr, int *error);

#endif
