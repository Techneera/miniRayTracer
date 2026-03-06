#include "ray.h"

static bool	check_caps(const t_ray *ray, float t)
{
	float	x;
	float	z;

	x = ray->origin.x + ray->direction.x * t;
	z = ray->origin.z + ray->direction.z * t;
	return ((x * x + z * z) <= 1.0f + EPSILON);
}

static void	intersect_caps(const t_object *cy, const t_ray *ray,
		t_intersect *xs)
{
	float	t;

	if (cy->cy.closed == false || fabsf(ray->direction.y) < EPSILON)
		return ;
	t = (cy->cy.min_y - ray->origin.y) / ray->direction.y;
	if (check_caps(ray, t))
	{
		xs->i[xs->count].t = t;
		xs->i[xs->count].object = cy;
		xs->count++;
	}
	t = (cy->cy.max_y - ray->origin.y) / ray->direction.y;
	if (check_caps(ray, t))
	{
		xs->i[xs->count].t = t;
		xs->i[xs->count].object = cy;
		xs->count++;
	}
}

t_intersect	local_intersect_cylinder(const t_object *cylinder, const t_ray *ray)
{
	t_intersect	res;
	t_quadratic	q;
	float		tmp;
	float		t0;
	float		t1;
	float		y0;
	float		y1;

	res.count = 0;
	q.a = ray->direction.x * ray->direction.x + ray->direction.z
		* ray->direction.z;
	if (fabsf(q.a) >= EPSILON)
	{
		q.b = 2.0f * ray->origin.x * ray->direction.x + 2.0f * ray->origin.z
			* ray->direction.z;
		q.c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z
			- 1.0f;
		q.discriminant = q.b * q.b - 4.0f * q.a * q.c;
		if (q.discriminant >= 0.0f)
		{
			t0 = (-q.b - sqrtf(q.discriminant)) / (2.0f * q.a);
			t1 = (-q.b + sqrtf(q.discriminant)) / (2.0f * q.a);
			if (t0 > t1)
			{
				tmp = t0;
				t0 = t1;
				t1 = tmp;
			}
			y0 = ray->origin.y + t0 * ray->direction.y;
			if (cylinder->cy.min_y < y0 && y0 < cylinder->cy.max_y)
			{
				res.i[res.count].t = t0;
				res.i[res.count].object = cylinder;
				res.count++;
			}
			y1 = ray->origin.y + t1 * ray->direction.y;
			if (cylinder->cy.min_y < y1 && y1 < cylinder->cy.max_y)
			{
				res.i[res.count].t = t1;
				res.i[res.count].object = cylinder;
				res.count++;
			}
		}
	}
	intersect_caps(cylinder, ray, &res);
	return (res);
}

t_vec3	local_normal_at_cylinder(const t_object *obj, t_vec3 local_point)
{
	float	dist;

	dist = (local_point.x * local_point.x) + (local_point.z * local_point.z);
	if (dist < 1.0f && local_point.y >= obj->cy.max_y - EPSILON)
		return (vector_constructor(0.0f, 1.0f, 0.0f));
	if (dist < 1.0f && local_point.y <= obj->cy.min_y + EPSILON)
		return (vector_constructor(0.0f, -1.0f, 0.0f));
	return (vector_constructor(local_point.x, 0.0f, local_point.z));
}
