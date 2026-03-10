#include "canvas.h"
#include "librt.h"
#include "matrix.h"
#include "ray.h"
#include "refraction.h"
#include "scene.h"
#include "shades.h"
#include "shadows.h"
#include "vector.h"
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

t_computation	prepare_computations(t_intersection hit, t_ray *ray,
		t_intersect *xs)
{
	t_computation	this;

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
	this.over_point = vector_add(this.point, vector_scale(this.normalv,
				EPSILON));
	this.under_point = vector_sub(this.point, vector_scale(this.normalv,
				EPSILON));
	set_refractive_indices(&this, hit, xs);
	return (this);
}

t_vec3	shade_hit(t_world *world, t_computation *computations, int depth)
{
	t_vec3				surface_color;
	t_vec3				reflected;
	t_vec3				refracted;
	float				reflectance;
	t_lighting_data		lighting_data;

	lighting_data = (t_lighting_data){&world->light, &world->a_light,
		computations->over_point, computations->eyev, computations->normalv,
		is_shadowed(*world, computations->over_point)};
	surface_color = lighting(computations->object->material,
			computations->object, lighting_data);
	reflected = reflected_color(world, computations, depth);
	refracted = refracted_color(world, computations, depth);
	if (computations->object->material.reflective > 0.0f
		&& computations->object->material.transparency > 0.0f)
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
