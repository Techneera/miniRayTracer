#include "librt.h"
#include "refraction.h"

void	manage_containers(const t_object *containers[], int *count,
		const t_object *obj)
{
	int	i;
	int	found_idx;

	i = 0;
	found_idx = -1;
	while (i < *count)
	{
		if (containers[i] == obj)
		{
			found_idx = i;
			break ;
		}
		i++;
	}
	if (found_idx != -1)
	{
		i = found_idx;
		while (i < *count - 1)
		{
			containers[i] = containers[i + 1];
			i++;
		}
		(*count)--;
	}
	else
	{
		if (*count < MAX_CONTAINERS)
		{
			containers[*count] = obj;
			(*count)++;
		}
	}
}
