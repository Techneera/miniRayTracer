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

t_intersection hit(t_intersection *items, int size)
{
	int				i;
	t_intersection	smallest;

	i = 0;
	while (items[i].t < 0)
		++i;
	if (i < size)
		smallest = items[i++];
	while (i < size)
	{
		if (items[i].t >= 0 && items[i].t < smallest.t)
			smallest = items[i];
		++i;
	}
	return (smallest);
}
