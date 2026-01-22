#ifndef PARSER_H
# define PARSER_H

# include "librt.h"
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define RGB_FACTOR 0.00392156862745
# define BUF_SIZE 4096
# define LINE_SIZE 1024

typedef struct e_reader
{
	int		fd;
	int		pos;
	int		size;
	char	buf[BUF_SIZE];
}	t_reader;

typedef int (*t_parse_fn)(char *, t_scene *);

int		parse_line(char *line, t_scene *scene);
int		parse_float(char **line, float *value);
int		parse_vec3(char **line, t_vec3 *v);
bool	is_valid_color(t_vec3 color);
void	color_normalize(t_vec3 *color);

int		parse_ambient_light(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);

int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);

char	*skip_to_next(char *ptr);
float	ft_atof(char **ptr, int *error);

int		get_line_buf(t_reader *r, char *line, int max_size);

int		load_scene(char *filename, t_scene *scene);

#endif
