#include "libft.h"
#include "matrix.h"
#include "ray.h"
#include "scene_api.h"
#include "shades.h"

t_object	*init_base_object(t_world *world, t_obj_type type)
{
	t_object	*obj;
	t_mat4		ident;

	if (world->object_count >= MAX_OBJECTS)
	{
		ft_putstr("Error\nMaximum number of objects reached\n");
		return (NULL);
	}
	obj = &world->objects[world->object_count++];
	obj->type = type;
	obj->id = get_shape_id();
	matrix_identity(&ident);
	set_transform(obj, &ident);
	obj->material = material_default();
	return (obj);
}