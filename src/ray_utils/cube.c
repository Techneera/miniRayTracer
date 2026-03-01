#include "ray.h"
#include "vector.h"
#include <math.h>

static
void	check_axis(float origin, float direction, float *t_min, float *t_max)
{
	float	tmin_num;
	float	tmax_num;
	float	tmp;

	tmin_num = -1.0 - origin;
	tmax_num = 1.0 - origin;
	if (fabsf(direction) >= EPSILON)
	{
		*t_min = tmin_num / direction;
		*t_max = tmax_num / direction;
	}
	else
	{
		*t_min = tmin_num * INFINITY;
		*t_max = tmax_num * INFINITY;
	}
	if (*t_min > *t_max)
	{
		tmp = *t_min;
		*t_min = *t_max;
		*t_max = tmp;
	}
}

t_intersect	local_intersect_cube(const t_object *cube, const t_ray *ray)
{
	t_intersect		result;
	t_helper_cube	h;

	result.count = 0;

	check_axis(ray->origin.x, ray->direction.x, &h.x_tmin, &h.x_tmax);
	check_axis(ray->origin.y, ray->direction.y, &h.y_tmin, &h.y_tmax);
	check_axis(ray->origin.z, ray->direction.z, &h.z_tmin, &h.z_tmax);

	h.tmin = h.x_tmin;
	if (h.y_tmin > h.tmin)
		h.tmin = h.y_tmin;
	if (h.z_tmin > h.tmin)
		h.tmin = h.z_tmin;

	h.tmax = h.x_tmax;
	if (h.y_tmax < h.tmax)
		h.tmax = h.y_tmax;
	if (h.z_tmax < h.tmax)
		h.tmax = h.z_tmax;

	if (h.tmin > h.tmax)
		return (result);
	result.count = 2;
	result.i[0].t = h.tmin;
	result.i[0].object = cube;
	result.i[1].t = h.tmax;
	result.i[1].object = cube;
	return (result);
}

t_vec3	local_normal_at_cube(t_vec3 local_point)
{
	float	max_c;
	float	xabs;
	float	yabs;
	float	zabs;

	xabs = fabs(local_point.x);
	yabs = fabs(local_point.y);
	zabs = fabs(local_point.z);

	max_c = xabs;
	if (max_c < yabs)
		max_c = yabs;
	if (max_c < zabs)
		max_c = zabs;

	if (max_c == xabs)
		return (vector_constructor(local_point.x, 0.0f, 0.0f));
	else if (max_c == yabs)
		return (vector_constructor(0.0f, local_point.y, 0.0f));
	return (vector_constructor(0.0f, 0.0f, local_point.z));
}
