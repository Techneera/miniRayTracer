#include "ray.h"

void	add_cone_intersect(t_intersect *res, const t_object *cone, \
const t_ray *ray, float t)
{
	float	y;

	y = ray->origin.y + t * ray->direction.y;
	if (cone->co.min_y < y && y < cone->co.max_y)
	{
		res->i[res->count].t = t;
		res->i[res->count].object = cone;
		res->count++;
	}
}

void	calc_cone_roots(t_intersect *res, const t_object *cone, \
const t_ray *ray, t_quadratic *q)
{
	t_helper_cone	hc;

	q->discriminant = q->b * q->b - 4.0f * q->a * q->c;
	if (q->discriminant < 0.0f)
		return ;
	hc.t0 = (-q->b - sqrtf(q->discriminant)) / (2.0f * q->a);
	hc.t1 = (-q->b + sqrtf(q->discriminant)) / (2.0f * q->a);
	if (hc.t0 > hc.t1)
	{
		hc.tmp = hc.t0;
		hc.t0 = hc.t1;
		hc.t1 = hc.tmp;
	}
	add_cone_intersect(res, cone, ray, hc.t0);
	add_cone_intersect(res, cone, ray, hc.t1);
}
