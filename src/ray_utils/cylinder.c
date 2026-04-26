#include "ray.h"

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

static t_quadratic	calc_cylinder_quadratic(const t_ray *ray)
{
	t_quadratic	q;

	q.a = ray->direction.x * ray->direction.x + ray->direction.z
		* ray->direction.z;
	q.b = 2.0f * ray->origin.x * ray->direction.x + 2.0f * ray->origin.z
		* ray->direction.z;
	q.c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1.0f;
	q.discriminant = q.b * q.b - 4.0f * q.a * q.c;
	return (q);
}

static void	add_valid_intersection(t_intersect *res, float t,
			const t_object *cylinder, const t_ray *ray)
{
	float	y;

	y = ray->origin.y + t * ray->direction.y;
	if (cylinder->cy.min_y < y && y < cylinder->cy.max_y)
	{
		res->i[res->count].t = t;
		res->i[res->count].object = cylinder;
		res->count++;
	}
}

t_intersect	local_intersect_cylinder(const t_object *cylinder, const t_ray *ray)
{
	t_intersect	res;
	t_quadratic	q;
	float		t0;
	float		t1;
	float		tmp;

	res.count = 0;
	q = calc_cylinder_quadratic(ray);
	if (fabsf(q.a) >= EPSILON && q.discriminant >= 0.0f)
	{
		t0 = (-q.b - sqrtf(q.discriminant)) / (2.0f * q.a);
		t1 = (-q.b + sqrtf(q.discriminant)) / (2.0f * q.a);
		if (t0 > t1)
		{
			tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		add_valid_intersection(&res, t0, cylinder, ray);
		add_valid_intersection(&res, t1, cylinder, ray);
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
