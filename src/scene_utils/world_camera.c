#include "canvas.h"
#include "librt.h"
#include "matrix.h"
#include "ray.h"
#include "scene.h"
#include "vector.h"
#include <math.h>

static t_mat4	orientation_with_translation(t_mat4 *orientation, t_vec3 from)
{
	t_mat4	trans;
	t_vec3	from_n;

	from_n = vector_scale(from, -1.0f);
	trans = matrix_translation(from_n.x, from_n.y, from_n.z);
	return (matrix_multiply(orientation, &trans));
}

t_mat4	view_transform(t_vec3 from, t_vec3 to, t_vec3 up)
{
	t_vec3	forward;
	t_vec3	up_normalized;
	t_vec3	left;
	t_vec3	true_up;
	t_mat4	orientation;

	forward = vector_normalization(vector_sub(to, from));
	if (fabs(forward.x) < EPSILON && fabs(forward.z) < EPSILON)
		up = vector_constructor(0.0f, 0.0f, 1.0f);
	up_normalized = vector_normalization(up);
	left = vector_cross_product(forward, up_normalized);
	true_up = vector_cross_product(left, forward);
	forward = vector_scale(forward, -1.0f);
	orientation = (t_mat4){.m = {left.x, left.y, left.z, 0.0f, true_up.x,
		true_up.y, true_up.z, 0.0f, forward.x, forward.y, forward.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}};
	return (orientation_with_translation(&orientation, from));
}

t_camera	camera_constructor(int hsize, int vsize, float field_of_view)
{
	t_camera	this;
	float		half_view;
	float		aspect;
	float		fov_radians;

	this.hsize = hsize;
	this.vsize = vsize;
	this.field_of_view = field_of_view;
	matrix_identity(&this.transform);
	fov_radians = field_of_view * (M_PI / 180.0f);
	half_view = tan(fov_radians / 2.0f);
	aspect = (float)this.hsize / (float)this.vsize;
	if (aspect >= 1.0f)
	{
		this.half_width = half_view;
		this.half_height = half_view / aspect;
	}
	else
	{
		this.half_width = half_view * aspect;
		this.half_height = half_view;
	}
	this.pixel_size = (this.half_width * 2.0f) / this.hsize;
	return (this);
}

t_ray	ray_for_pixel(t_camera *c, int px, int py)
{
	float	world_x;
	float	world_y;
	t_vec3	origin;
	t_vec3	pixel;
	t_mat4	inv;

	world_x = c->half_width - ((px + 0.5f) * c->pixel_size);
	world_y = c->half_height - ((py + 0.5f) * c->pixel_size);
	inv = matrix_inverse(&c->transform);
	pixel = matrix_vector_multiply(&inv,
			&((t_vec3){.x = world_x, .y = world_y, .z = -1.0f, .w = 1.0f}));
	origin = matrix_vector_multiply(&inv,
			&((t_vec3){.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f}));
	return (ray_constructor(origin,
			vector_normalization(vector_sub(pixel, origin))));
}

void	render(t_canvas *canvas, t_camera *c, t_world *w)
{
	t_ray	ray;
	t_vec3	color;
	int		x;
	int		y;

	if (canvas_constructor(c->hsize, c->vsize, canvas) == false)
	{
		ft_error("Failed to lauch canvas\n");
		close_program(canvas);
	}
	y = 0;
	while (y < c->vsize)
	{
		x = 0;
		while (x < c->hsize)
		{
			ray = ray_for_pixel(c, x, y);
			color = color_at(w, &ray, MAX_BOUNCE);
			write_pixel(canvas, x, y, color);
			++x;
		}
		++y;
	}
}
