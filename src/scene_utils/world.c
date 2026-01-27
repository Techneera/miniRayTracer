#include "scene.h"

t_world	default_world(void)
{
	t_world			world;
	t_point_light	light;
	t_object		o1;
	t_object		o2;

	light = point_light(
			point_constructor(-10, 10, -10),
			color_constructor(1, 1, 1));
	o1.sp = sphere();
	o1.sp.material.color = color_constructor(0.8, 1.0, 0.6);
	o1.sp.material.diffuse = 0.7;
	o1.sp.material.specular = 0.2;
	o2.sp = sphere();
	sphere_set_transform(&o2.sp, matrix_scale(0.5, 0.5, 0.5));
	world.object_count = 0;
	world.light = light;
	world.objects[world.object_count].object = o1;
	world.objects[world.object_count++].type = SPHERE;
	world.objects[world.object_count].object = o2;
	world.objects[world.object_count++].type = SPHERE;
	return (world);
}
