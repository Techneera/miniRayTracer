#include "canvas.h"
#include "librt.h"
#include "matrix.h"
#include "ray.h"
#include "scene.h"
#include "shades.h"
#include "shadows.h"
#include "vector.h"
#include "refraction.h"
#include <math.h>

void	intersect_sort(t_intersect *this)
{
	t_intersection	temp;
	int				i;
	int				j;

	i = 0;
	while (i < this->count - 1)
	{
		j = 0;
		while (j < this->count - i - 1)
		{
			if (this->i[j].t > this->i[j + 1].t)
			{
				temp = this->i[j];
				this->i[j] = this->i[j + 1];
				this->i[j + 1] = temp;
			}
			++j;
		}
		++i;
	}
}

t_intersect	intersect_world(t_world *world, t_ray *ray)
{
	t_intersect	this;
	t_intersect	current;
	int			i;
	int			j;

	i = 0;
	this.count = 0;
	while (i < world->object_count)
	{
		current = intersect(ray, &world->objects[i]);
		j = 0;
		while (j < current.count && this.count < MAX_INTERSECTION)
		{
			this.i[this.count] = current.i[j];
			++this.count;
			++j;
		}
		++i;
	}
	intersect_sort(&this);
	return (this);
}

t_computation	prepare_computations(t_intersection hit, t_ray *ray, t_intersect *xs)
{
	t_computation	this;
	const t_object	*containers[MAX_CONTAINERS] = {NULL};
	int				container_count;
	int				i;

	this.t = hit.t;
	this.object = hit.object;
	this.point = ray_position(ray, this.t);
	this.eyev = vector_scale(ray->direction, -1.0);
	this.normalv = normal_at(this.object, this.point);
	this.inside = false;
	if (vector_dot_product(this.normalv, this.eyev) < 0)
	{
		this.inside = true;
		this.normalv = vector_scale(this.normalv, -1.0);
	}
	this.reflectv = reflect(ray->direction, this.normalv);
	this.over_point = vector_add(
		this.point,
		vector_scale(this.normalv, EPSILON)
	);
	this.under_point = vector_sub(
		this.point,
		vector_scale(this.normalv, EPSILON)
	);
	i = 0;
	container_count = 0;
	while (i < xs->count)
	{
		if (xs->i[i].t == hit.t && xs->i[i].object == hit.object)
		{
			if (container_count == 0)
				this.n1 = 1.0f;
			else
				this.n1 = containers[container_count - 1]->material.refractive_index;
		}
		manage_containers(containers, &container_count, xs->i[i].object);
		if (xs->i[i].t == hit.t && xs->i[i].object == hit.object)
		{
			if (container_count == 0)
				this.n2 = 1.0f;
			else
				this.n2 = containers[container_count - 1]->material.refractive_index;
			break;
		}
		i++;
	}
	return (this);
}

t_vec3	shade_hit(t_world *world, t_computation *computations, int depth)
{
	t_vec3	surface_color;
	t_vec3	reflected;
	t_vec3	refracted;
	float	reflectance;

	surface_color = lighting(
			computations->object->material,
			computations->object,
			&world->light,
			&world->a_light,
			computations->over_point,
			computations->eyev,
			computations->normalv,
			is_shadowed(*world, computations->over_point)
	);
	reflected = reflected_color(world, computations, depth);
	refracted = refracted_color(world, computations, depth);
	if (computations->object->material.reflective > 0.0f && computations->object->material.transparency > 0.0f)
	{
		reflectance = schlick(computations);
		reflected = vector_scale(reflected, reflectance);
		refracted = vector_scale(refracted, 1.0f - reflectance);
	}
	return (vector_add(surface_color, vector_add(reflected, refracted)));
}

t_vec3	color_at(t_world *world, t_ray *ray, int depth)
{
	t_intersect		xs;
	t_computation	comps;
	int				hit_index;
	int				index;
	float			min_t;

	min_t = INFINITY;
	xs = intersect_world(world, ray);
	index = 0;
	hit_index = -1;
	while (index < xs.count)
	{
		if (xs.i[index].t > EPSILON && xs.i[index].t < min_t)
		{
			min_t = xs.i[index].t;
			hit_index = index;
		}
		++index;
	}
	if (hit_index == -1)
		return (color_constructor(0.0f, 0.0f, 0.0f));
	comps = prepare_computations(xs.i[hit_index], ray, &xs);
	return (shade_hit(world, &comps, depth));
}

t_mat4	view_transform(t_vec3 from, t_vec3 to, t_vec3 up)
{
	t_vec3	forward;
	t_vec3	up_normalized;
	t_vec3	left;
	t_vec3	true_up;
	t_vec3	from_n;
	t_mat4	orientation;
	t_mat4	trans;

	forward = vector_normalization(vector_sub(to, from));
	if (fabs(forward.x) < EPSILON && fabs(forward.z) < EPSILON)
		up = vector_constructor(0.0f, 0.0f, 1.0f);
	up_normalized = vector_normalization(up);
	left = vector_cross_product(forward, up_normalized);
	true_up = vector_cross_product(left, forward);
	forward = vector_scale(forward, -1);
	orientation = (t_mat4) {
		.m = {
			left.x, left.y, left.z, 0,
			true_up.x, true_up.y, true_up.z, 0,
			forward.x, forward.y, forward.z, 0,
			0, 0, 0, 1
		}
	};
	from_n = vector_scale(from, -1);
	trans = matrix_translation(from_n.x, from_n.y, from_n.z);
	return (matrix_multiply(
			&orientation,
			&trans));
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
	half_view = tan(fov_radians / 2);
	aspect = (float) this.hsize / (float) this.vsize;
	if (aspect >= 1)
	{
		this.half_width = half_view;
		this.half_height = half_view / aspect;
	}
	else
	{
		this.half_width = half_view * aspect;
		this.half_height = half_view;
	}
	this.pixel_size = (this.half_width * 2.0) / this.hsize;
	return (this);
}
t_ray	ray_for_pixel(t_camera *c, int px, int py)
{
	float	x_offset;
	float	y_offset;
	float	world_x;
	float	world_y;
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	pixel;
	t_mat4	inv;
	t_vec3	p_target;
	t_vec3	p_origin;


	x_offset = (px + 0.5) * c->pixel_size;
	y_offset = (py + 0.5) * c->pixel_size;
	world_x = c->half_width - x_offset;
	world_y = c->half_height - y_offset;
	inv = matrix_inverse(&c->transform);
	p_target = point_constructor(world_x, world_y, -1.0f);
	p_origin = point_constructor(0.0f, 0.0f, 0.0f);
	pixel = matrix_vector_multiply(
		&inv,
		&p_target
	);
	origin = matrix_vector_multiply(
		&inv,
		&p_origin
	);
	direction = vector_normalization(vector_sub(pixel, origin));
	return (ray_constructor(origin, direction));
}

void	render(t_canvas *canvas, t_camera *c, t_world *w)
{
	t_ray		ray;
	t_vec3		color;
	int			x;
	int			y;

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
