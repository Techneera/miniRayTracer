#include "canvas.h"
#include "librt.h"
#include "matrix.h"
#include "ray.h"
#include "scene.h"
#include "shades.h"
#include "shadows.h"
#include "vector.h"
#include <math.h>

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
	o1.sp.shape.material.color = color_constructor(0.8, 1.0, 0.6);
	o1.sp.shape.material.diffuse = 0.7;
	o1.sp.shape.material.specular = 0.2;
	o2.sp = sphere();
	set_transform(&o2.sp.shape, matrix_scale(0.5, 0.5, 0.5));
	world.object_count = 0;
	world.light = light;
	world.objects[world.object_count].object = o1;
	world.objects[world.object_count++].type = SPHERE;
	world.objects[world.object_count].object = o2;
	world.objects[world.object_count++].type = SPHERE;
	return (world);
}

void	intersect_sort(t_intersect *this)
{
	t_intersection	temp;
	int				i;
	int				j;

	i = 0;
	while (i < this->count)
	{
		j = i + 1;
		while (j < this->count)
		{
			if (this->i[i].t > this->i[j].t)
			{
				temp = this->i[i];
				this->i[i] = this->i[j];
				this->i[j] = temp;
			}
			++j;
		}
		++i;
	}
}

t_intersect	intersect_world(t_world *world, t_ray ray)
{
	t_intersect	this;
	t_intersect	current;
	int			i;
	int			j;

	i = 0;
	this.count = 0;
	while (i < world->object_count)
	{
		if (world->objects[i].type == SPHERE)
			current = intersect(ray, &world->objects[i].object.sp.shape);
		j = 0;
		while (j < current.count)
			this.i[this.count++] = current.i[j++];
		++i;
	}
	intersect_sort(&this);
	return (this);
}

t_computation	prepare_computations(t_intersection i, t_ray ray)
{
	t_computation	this;

	this.t = i.t;
	this.object = i.object;
	this.point = ray_position(ray, this.t);
	this.eyev = vector_scale(ray.direction, -1.0);
	this.normalv = normal_at(&i.object.sp.shape, this.point);
	this.reflectv = reflect(ray.direction, this.normalv);
	this.inside = false;
	if (vector_dot_product(this.normalv, this.eyev) < 0)
	{
		this.inside = true;
		this.normalv = vector_scale(this.normalv, -1.0);
	}
	this.over_point = vector_add(
		this.point,
		vector_scale(this.normalv, EPSILON)
	);
	return (this);
}

t_vec3	shade_hit(t_world world, t_computation computations)
{
	return (lighting(
			computations.object.sp.shape.material,
			world.light,
			computations.over_point,
			computations.eyev,
			computations.normalv,
			is_shadowed(world, computations.over_point))
	);
}

t_vec3	color_at(t_world world, t_ray ray)
{
	t_intersect		xs;
	t_computation	comps;
	int				hit_index;
	int				index;

	xs = intersect_world(&world, ray);
	index = 0;
	hit_index = -1;
	while (index < xs.count)
	{
		if (xs.i[index].t > 0)
		{
			hit_index = index;
			break ;
		}
		++index;
	}
	if (hit_index == -1)
		return (color_constructor(0, 0, 0));
	comps = prepare_computations(xs.i[hit_index], ray);
	return (shade_hit(world, comps));
}

t_mat4	view_transform(t_vec3 from, t_vec3 to, t_vec3 up)
{
	t_vec3	forward;
	t_vec3	up_normalized;
	t_vec3	left;
	t_vec3	true_up;
	t_vec3	from_n;
	t_mat4	orientation;

	forward = vector_normalization(vector_sub(to, from));
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
	return (matrix_multiply(
			orientation,
			matrix_translation(from_n.x, from_n.y, from_n.z)));
}
t_camera	camera_constructor(int hsize, int vsize, float field_of_view)
{
	t_camera	this;
	float		half_view;
	float		aspect;

	this.hsize = hsize;
	this.vsize = vsize;
	this.field_of_view = field_of_view;
	matrix_identity(&this.transform);
	half_view = tan(this.field_of_view / 2);
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
	this.pixel_size = (this.half_width * 2) / this.hsize;
	return (this);
}
t_ray	ray_for_pixel(t_camera c, int px, int py)
{
	float	x_offset;
	float	y_offset;
	float	world_x;
	float	world_y;
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	pixel;


	x_offset = (px + 0.5) * c.pixel_size;
	y_offset = (py + 0.5) * c.pixel_size;
	world_x = c.half_width - x_offset;
	world_y = c.half_height - y_offset;
	pixel = matrix_vector_multiply(
		matrix_inverse(c.transform),
		point_constructor(world_x, world_y, -1)
	);
	origin = matrix_vector_multiply(
		matrix_inverse(c.transform),
		point_constructor(0, 0, 0)
	);
	direction = vector_normalization(vector_sub(pixel, origin));
	return (ray_constructor(origin, direction));
}
t_canvas	render(t_camera c, t_world w)
{
	t_canvas	image;
	t_ray		ray;
	t_vec3		color;
	int			x;
	int			y;

	canvas_constructor(c.hsize, c.vsize, &image);
	y = 0;
	while (y < c.vsize)
	{
		x = 0;
		while (x < c.hsize)
		{
			ray = ray_for_pixel(c, x, y);
			color = color_at(w, ray);
			write_pixel(&image, x, y, color);
			++x;
		}
		++y;
	}
	return (image);
}
