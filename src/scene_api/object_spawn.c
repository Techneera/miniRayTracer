#include "scene_api.h"
#include "matrix.h"
#include "shades.h"
#include "ray.h"
#include "libft.h"

static
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

t_object	*spawn_sphere(t_world *world)
{
	return (init_base_object(world, SPHERE));
}

t_object	*spawn_cube(t_world *world)
{
	return (init_base_object(world, CUBE));
}

t_object	*spawn_plane(t_world *world)
{
	return (init_base_object(world, PLANE));
}

t_object	*spawn_cylinder(t_world *world, float min_y, float max_y, bool closed)
{
	t_object	*obj;

	obj = init_base_object(world, CYLINDER);
	if (obj)
	{
		obj->cy.min_y = min_y;
		obj->cy.max_y = max_y;
		obj->cy.closed = closed;
	}
	return (obj);
}

t_object	*spawn_cone(t_world *world, float min_y, float max_y, bool closed)
{
	t_object	*obj;

	obj = init_base_object(world, CONE);
	if (obj)
	{
		obj->co.min_y = min_y;
		obj->co.max_y = max_y;
		obj->co.closed = closed;
	}
	return (obj);
}
