#include "canvas.h"
#include "librt.h"
#include "parser.h"
#include "patterns.h"
#include "ray.h"
#include "vector.h"
#include "matrix.h"

static int	set_up(char **line, t_helper *h, t_object *obj, t_obj_type type)
{
	obj->type = type;
	obj->id = get_shape_id();
	*line = skip_to_next(*line);
	if (parse_vec3(line, &h->pos) != 0)
		return (1);
	return (0);
}

int	parse_sphere(char *line, t_scene *scene)
{
	t_helper	h;
	t_object	*obj;

	if (scene->world.object_count >= MAX_OBJECTS)
		return (1);
	obj = &scene->world.objects[scene->world.object_count];
	if (set_up(&line, &h, obj, SPHERE) != 0)
		return (1);
	line = skip_to_next(line);
	if (parse_float(&line, &h.diameter) != 0 || h.diameter <= 0.0f)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &h.color) != 0 || is_valid_color(h.color) == false)
		return (1);
	color_normalize(&h.color);
	h.scale = matrix_scale(h.diameter * 0.5f, h.diameter * 0.5f, h.diameter
			* 0.5f);
	h.trans = matrix_translation(h.pos.x, h.pos.y, h.pos.z);
	h.transform = matrix_multiply(&h.trans, &h.scale);
	set_transform(obj, &h.transform);
	obj->material = material_default();
	obj->material.color = h.color;
	++scene->world.object_count;
	return (0);
}

int	parse_plane(char *line, t_scene *scene)
{
	t_helper	h;
	t_object	*obj;

	if (scene->world.object_count == MAX_OBJECTS)
		return (1);
	obj = &scene->world.objects[scene->world.object_count];
	if (set_up(&line, &h, obj, PLANE) != 0)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &h.vec) != 0 || !is_valid_direction(h.vec))
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &h.color) != 0 || !is_valid_color(h.color))
		return (1);
	color_normalize(&h.color);
	h.rot = align_up_vector(h.vec);
	h.trans = matrix_translation(h.pos.x, h.pos.y, h.pos.z);
	h.transform = matrix_multiply(&h.trans, &h.rot);
	set_transform(obj, &h.transform);
	obj->material = material_default();
	obj->material.color = h.color;
	++scene->world.object_count;
	return (0);
}

static void	set_cylinder_params(t_object *obj, t_helper *h)
{
	obj->cy.min_y = -h->height * 0.5f;
	obj->cy.max_y = h->height * 0.5f;
	obj->cy.closed = true;
	h->scale = matrix_scale(h->diameter * 0.5f, 1.0f, h->diameter * 0.5f);
	h->rot = align_up_vector(h->vec);
	h->trans = matrix_translation(h->pos.x, h->pos.y, h->pos.z);
	h->temp = matrix_multiply(&h->trans, &h->rot);
	h->transform = matrix_multiply(&h->temp, &h->scale);
	set_transform(obj, &h->transform);
	obj->material = material_default();
	obj->material.color = h->color;
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_helper	h;
	t_object	*obj;

	if (scene->world.object_count == MAX_OBJECTS)
		return (1);
	obj = &scene->world.objects[scene->world.object_count];
	if (set_up(&line, &h, obj, CYLINDER) != 0)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &h.vec) != 0 || !is_valid_direction(h.vec))
		return (1);
	line = skip_to_next(line);
	if (parse_float(&line, &h.diameter) != 0 || h.diameter <= 0.0f)
		return (1);
	line = skip_to_next(line);
	if (parse_float(&line, &h.height) != 0 || h.height <= 0.0f)
		return (1);
	line = skip_to_next(line);
	if (parse_vec3(&line, &h.color) != 0 || !is_valid_color(h.color))
		return (1);
	color_normalize(&h.color);
	set_cylinder_params(obj, &h);
	++scene->world.object_count;
	return (0);
}
