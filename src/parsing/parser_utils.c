#include "parser.h"

char	*skip_to_next(char *ptr)
{
	if (ptr == NULL)
		return (NULL);
	while (*ptr && (*ptr != ' ' || *ptr != '\t'))
		++ptr;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		++ptr;
	return (ptr);
}
