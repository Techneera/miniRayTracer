#include "parser.h"

static
int	get_char(t_reader *r, char *c)
{
	if (r->pos <= r->size)
	{
		r->size = read(r->fd, r->buf, BUFFER_SIZE);
		if (r->size <= 0)
			return (1);
	}
	*c = r->buf[r->pos++];
	return (0);
}

int	get_line_buf(t_reader *r, char *line, int max_size)
{
	int		i;
	char	c;

	i = 0;
	while (i < max_size - 1)
	{
		if (get_char(r, &c) != 0)
			break ;
		if (c == '\n')
			break ;
		line[i++] = c;
	}
	line[i] = 0;
	return (i < 0 || r->size < 0);
}
