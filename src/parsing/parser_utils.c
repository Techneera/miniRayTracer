#include "parser.h"

char	*skip_to_next(char *ptr)
{
	if (ptr == NULL)
		return (NULL);
	while (*ptr && (*ptr != ' ' && *ptr != '\t'))
		++ptr;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		++ptr;
	return (ptr);
}

static
float	ft_atof_error(int *error)
{
	*error = 1;
	return (0.0);
}

static
void	init_vars(float *result, float *div, int *sign)
{
	*result = 0.0;
	*div = 10.0;
	*sign = 1;
}

static
bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static
char	**handle_signal(char **ptr, int *sign)
{
	if (**ptr == '-' || **ptr == '+')
	{
		if (**ptr == '-')
			*sign *= -1;
		++(*ptr);
	}
	return (ptr);
}

float	ft_atof(char **ptr, int *error)
{
	float	result;
	float	div;
	int		sign;

	init_vars(&result, &div, &sign);
	ptr = handle_signal(ptr, &sign);
	if (ft_isdigit(**ptr) != true && **ptr != '.')
		return (ft_atof_error(error));
	while (ft_isdigit(**ptr) == true)
		result = result * 10.0 + ((*(*ptr)++) - '0');
	if (**ptr == '.')
	{
		++(*ptr);
		if (ft_isdigit(**ptr) != true)
			return (ft_atof_error(error));
		while (ft_isdigit(**ptr) == true)
		{
			result = result + ((*(*ptr)++) - '0') / div;
			div *= 10;
		}
	}
	if (**ptr != '\0' && **ptr != ' ' && **ptr != '\t'
		&& **ptr != ',' && **ptr != '\n')
		return (ft_atof_error(error));
	return (result * sign);
}
