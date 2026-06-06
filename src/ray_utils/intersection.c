#include "ray.h"

t_intersection	intersection(float t, const t_object *obj)
{
	t_intersection	i;

	i.t = t;
	i.object = obj;
	return (i);
}

t_intersect	*intersections(t_intersection *items, t_intersect *result, int size)
{
	int	index;

	index = 0;
	result->count = size;
	while (index < size)
	{
		result->i[index] = items[index];
		++index;
	}
	return (result);
}

t_intersection	*hit(t_intersect *items, t_intersection *smallest, int size)
{
	int		i;
	bool	found;

	if (items == NULL || smallest == NULL || size == 0)
		return (NULL);
	i = 0;
	found = false;
	while (i < size)
	{
		if (items->i[i].t >= 0.0f)
		{
			if (found == false || items->i[i].t < smallest->t)
			{
				*smallest = items->i[i];
				found = true;
			}
		}
		++i;
	}
	if (found == true)
		return (smallest);
	return (NULL);
}
