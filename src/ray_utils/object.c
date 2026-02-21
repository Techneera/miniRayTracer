#include "libft.h"
#include "librt.h"
#include "ray.h"

t_object	object_constructor(t_shape_type type)
{
	t_object	object;

	ft_memset(&object, 0, sizeof(object));
	object.type = type;
	if (type == SHAPE_PLANE)
		object.pl = plane();
	else if (type == SHAPE_SPHERE)
		object.sp = sphere();
	return (object);
}