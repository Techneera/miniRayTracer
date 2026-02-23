#include "librt.h"
#include "ray.h"
#include "vector.h"
#include <math.h>

t_object	plane(void)
{
	t_object	plane;
	
	plane.id = get_shape_id();
	plane.type = PLANE;
	matrix_identity(&plane.transform);
	matrix_identity(&plane.transform_inv);
	return (plane);
}

t_vec3	local_normal_at_plane(void)
{
	return (
		vector_constructor(0.0f, 1.0f, 0.0f)
	);
}

t_intersect	local_intersect_plane(const t_object *plane, const t_ray *ray)
{
	t_intersect	result;
	
	result.count = 0;
	if (fabsf(ray->direction.y) < EPSILON)
	    return (result);
	result.count = 1;
	result.i[0].t = -ray->origin.y / ray->direction.y;
	result.i[0].object = plane;
	return (result);
}
