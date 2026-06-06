#include "libft.h"
#include "parser.h"

static float	ft_atof_error(int *error)
{
	*error = 1;
	return (0.0);
}

static void	init_vars(float *result, float *div, int *sign)
{
	*result = 0.0;
	*div = 10.0;
	*sign = 1;
}

static char	**handle_signal(char **ptr, int *sign)
{
	if (**ptr == '-' || **ptr == '+')
	{
		if (**ptr == '-')
			*sign *= -1;
		++(*ptr);
	}
	return (ptr);
}

static int	check_trailing_chars(char **ptr)
{
	if (**ptr != '\0' && **ptr != ' ' && **ptr != '\t' && **ptr != ','
		&& **ptr != '\n')
		return (1);
	if (**ptr == ',')
		++(*ptr);
	return (0);
}

float	ft_atof(char **ptr, int *error)
{
	float	result;
	float	div;
	int		sign;

	init_vars(&result, &div, &sign);
	ptr = handle_signal(ptr, &sign);
	if (!ft_isdigit(**ptr) && **ptr != '.')
		return (ft_atof_error(error));
	while (ft_isdigit(**ptr))
		result = result * 10.0 + ((*(*ptr)++) - '0');
	if (**ptr == '.')
	{
		++(*ptr);
		if (!ft_isdigit(**ptr))
			return (ft_atof_error(error));
		while (ft_isdigit(**ptr))
		{
			result = result + ((*(*ptr)++) - '0') / div;
			div *= 10;
		}
	}
	if (check_trailing_chars(ptr) != 0)
		return (ft_atof_error(error));
	return (result * sign);
}
