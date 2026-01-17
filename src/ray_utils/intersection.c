#include "ray.h"

t_intersection	intersection(double t, t_object object)
{
	t_intersection	i;

	i.t = t;
	i.object = object;
	return (i);
}

t_intersect	*intersections(t_intersection *items, t_intersect *result, int size)
{
	int			index;

	index = 0;
	result->count = size;
	while (index < size)
	{
		result->i[index] = items[index];
		++index;
	}
	return (result);
}

t_intersection *hit(t_intersect *items, t_intersection *smallest, int size)
{
	int				index;

	if (items == NULL || size == 0)
		return (NULL);
	index = 0;
	while (items->i[index].t < 0)
		++index;
	if (index >= size)
		return (NULL);
	*smallest = items->i[index++];
	while (index < size)
	{
		if (items->i[index].t >= 0 && items->i[index].t < smallest->t)
			*smallest = items->i[index];
		++index;
	}
	return (smallest);
}
