#incldue "triangle.h"

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
	t_vec3		dir_cross_e2;
	t_vec3		origin_cross_e1
	float		det;
	float		u;
	float		v;

	res.count = 0;
	dir_cross_e2 = vector_cross_product(ray->direction, triangle->edge.e2);
	det = vector_dot_product(triangle->edge.e1, dir_cross_e2);
	if (fabsf(det) < EPSILON)
		return (res);
	u = vector_dot_product(
				vector_sub(ray->direction, triangle->edge.p1),
				dir_cross_e2) * (1.0f / det));
	if (u < 0.0f || u > 1.0f)
		return (res);
	origin_cross_e1 = vector_cross_product(
				vector_sub(ray->direction, triangle->edge.p1),
				triangle->edge.e1);
	v = vector_dot_product(
			ray->direction, origin_cross_e1) * (1.0f / det);
	if (v < 0.0f || (u + v) > 1.0f)
		return (res);
	res.count = 1;
	res.i[0].t = vector_dot_product(obj->tri.e2, origin_cross_e1) * (1.0f / det);
	res.i[0].obj = triangle;
	return (res);
}
