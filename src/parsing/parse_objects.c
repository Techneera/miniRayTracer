#include "librt.h"
#include "parser.h"
#include "vector.h"

int	parse_sphere(char *line, t_scene *scene)
{
	t_vec3	sphere_center;

	if (scene->object_count == MAX_OBJECTS)
		return (1);
	scene->objects->type = SPHERE;
	line = skip_to_next(line);
	if (parse_vec3(&line, &sphere_center) != 0)
		return (1);
	sphere_center.w = 1;
	scene->objects->object.sp.center = sphere_center;
	line = skip_to_next(line);
	if (parse_float(&line, &scene->objects->object.sp.radius) != 0)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &scene->objects->object.sp.color) != 0
		|| is_valid_color(scene->objects->object.sp.color) == false)
		return (1);
	color_normalize(&scene->objects->object.sp.color);
	++scene->object_count;
	return (0);
}

int	parse_plane(char *line, t_scene *scene)
{
	if (scene->object_count == MAX_OBJECTS)
		return (1);
	++scene->object_count;
	scene->objects->type = PLANE;
	line = skip_to_next(line);
	return (0);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	if (scene->object_count == MAX_OBJECTS)
		return (1);
	++scene->object_count;
	scene->objects->type = CYLINDER;
	line = skip_to_next(line);
	return (0);
}
