#include "canvas.h"
#include "ray.h"
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
			current = sphere_intersect(ray, world->objects[i].object.sp);
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
	this.normalv = normal_at(i.object.sp, this.point);
	return (this);
}