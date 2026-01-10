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
