#include "libft.h"
#include "parser.h"
#include <fcntl.h>

static
int	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension == NULL || ft_strcmp(filename, ".rt") != 0)
		return (1);
	return (0);
}

int	load_scene(char *filename, t_scene *scene)
{
	t_reader	r;
	char		line[LINE_SIZE];

	if (filename == NULL || check_extension(filename) != 0)
		return (1);
	r.pos = 0;
	r.size = 0;
	r.fd = open(filename, O_RDONLY);
	if (r.fd < 0)
		return (1);
	while (get_line_buf(&r, line, LINE_SIZE) == 0)
	{
		if (parse_line(line, scene) != 0)
		{
			close(r.fd);
			return (1);
		}
	}
	return (0);
}
