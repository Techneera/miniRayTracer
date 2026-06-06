#include "librt.h"
#include "refraction.h"

static int	find_container_idx(const t_object *containers[], int count,
		const t_object *obj)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (containers[i] == obj)
			return (i);
		i++;
	}
	return (-1);
}

void	manage_containers(const t_object *containers[], int *count,
		const t_object *obj)
{
	int	i;
	int	found_idx;

	found_idx = find_container_idx(containers, *count, obj);
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
