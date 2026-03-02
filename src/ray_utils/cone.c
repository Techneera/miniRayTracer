#include "ray.h"

static
bool	check_caps(const t_ray *ray, float t, float y)
{
	float	x;
	float	z;

	x = ray->origin.x + ray->direction.x * t;
	z = ray->origin.z + ray->direction.z * t;
	return ((x * x + z * z) <= (y * y) + EPSILON);
}

static
void	intersect_caps(const t_object *cone, const t_ray *ray, t_intersect *xs)
{
	float	t;

	if (cone->co.closed == false || fabsf(ray->direction.y) < EPSILON)
		return ;
	t = (cone->co.min_y - ray->origin.y) / ray->direction.y;
	if (check_caps(ray, t, cone->co.min_y))
	{
		xs->i[xs->count].t = t;
		xs->i[xs->count].object = cone;
		xs->count++;
	}
	t = (cone->co.max_y - ray->origin.y) / ray->direction.y;
	if (check_caps(ray, t, cone->co.max_y))
	{
		xs->i[xs->count].t = t;
		xs->i[xs->count].object = cone;
		xs->count++;
	}
}

t_intersect	local_intersect_cone(const t_object *cone, const t_ray *ray)
{
	t_intersect	res;
	t_quadratic	q;
	float		tmp;
	float		t0;
	float		t1;
	float		y0;
	float		y1;

	res.count = 0;
	q.a = (ray->direction.x * ray->direction.x) - (ray->direction.y * ray->direction.y) + (ray->direction.z * ray->direction.z);
	q.b = 2.0f * ((ray->origin.x * ray->direction.x) - (ray->origin.y * ray->direction.y) + (ray->origin.z * ray->direction.z));
	q.c = (ray->origin.x * ray->origin.x) - (ray->origin.y * ray->origin.y) + (ray->origin.z * ray->origin.z);

	if (fabsf(q.a) < EPSILON)
	{
		if (fabsf(q.b) >= EPSILON)
		{
			t0 = -q.c / (2.0f * q.b);
			y0 = ray->origin.y + t0 * ray->direction.y;
			if (cone->co.min_y < y0 && y0 < cone->co.max_y)
			{
				res.i[res.count].t = t0;
				res.i[res.count].object = cone;
				res.count++;
			}
		}
	}
	else
	{
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
			if (cone->co.min_y < y0 && y0 < cone->co.max_y)
			{
				res.i[res.count].t = t0;
				res.i[res.count].object = cone;
				res.count++;
			}
			
			y1 = ray->origin.y + t1 * ray->direction.y;
			if (cone->co.min_y < y1 && y1 < cone->co.max_y)
			{
				res.i[res.count].t = t1;
				res.i[res.count].object = cone;
				res.count++;
			}
		}
	}
	
	intersect_caps(cone, ray, &res);
	
	return (res);
}

t_vec3	local_normal_at_cone(const t_object *obj, t_vec3 local_point)
{
	float	dist;
	float	normal_y;

	dist = (local_point.x * local_point.x) + (local_point.z * local_point.z);
	if (dist < (local_point.y * local_point.y) && \
			local_point.y >= obj->co.max_y - EPSILON)
		return (vector_constructor(0.0f, 1.0f, 0.0f));
	if (dist < (local_point.y * local_point.y) && \
			local_point.y <= obj->co.min_y + EPSILON)
		return (vector_constructor(0.0f, -1.0f, 0.0f));
	normal_y = sqrtf(dist);
	if (local_point.y > 0.0f)
		normal_y = -normal_y;
	return (vector_constructor(local_point.x, normal_y, local_point.z));
}
