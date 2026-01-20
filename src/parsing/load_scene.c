#include "libft.h"
#include "parser.h"

static
int	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension == NULL || ft_strcmp(filename, ".rt") != 0)
		return (1);
	return (0);
}
