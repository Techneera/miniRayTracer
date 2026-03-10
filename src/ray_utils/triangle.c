#include "triangle.h"

t_tri	triangle_constructor(t_vec3	p1, t_vec3 p2, t_vec3 p3)
{
	t_tri	res;

	res.p1 = p1;
	res.p2 = p2;
	res.p3 = p3;
	res.e1 = vector_sub(p2, p1);
	res.e2 = vector_sub(p3, p1);
	res.normal = vector_normalization(vector_cross_product(res.e1, res.e2));
	return (res);
}

t_intersect	local_intersect_triangle(const t_object *triangle, const t_ray *ray)
{
	t_intersect	res;
	t_products	p;
	t_vec3		p1_to_origin;

	res.count = 0;
	p1_to_origin = vector_sub(ray->origin, triangle->edge.p1);
	p.dir_cross_e2 = vector_cross_product(ray->direction, triangle->edge.e2);
	p.det = vector_dot_product(triangle->edge.e1, p.dir_cross_e2);
	if (fabsf(p.det) < EPSILON)
		return (res);
	p.inv_det = 1.0f / p.det;
	p.u = vector_dot_product(p1_to_origin, p.dir_cross_e2) * p.inv_det;
	if (p.u < 0.0f || p.u > 1.0f)
		return (res);
	p.origin_cross_e1 = vector_cross_product(p1_to_origin, triangle->edge.e1);
	p.v = vector_dot_product(ray->direction, p.origin_cross_e1) * p.inv_det;
	if (p.v < 0.0f || (p.u + p.v) > 1.0f)
		return (res);
	res.count = 1;
	res.i[0].t = vector_dot_product(obj->tri.e2, p.origin_cross_e1) * p.inv_det;
	res.i[0].obj = triangle;
	return (res);
}
