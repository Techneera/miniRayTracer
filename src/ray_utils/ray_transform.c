#include "ray.h"

t_ray	ray_transform(const t_ray *r, const t_mat4 *m)
{
	t_ray	result;

	result.origin = matrix_vector_multiply(m, &r->origin);
	result.direction = matrix_vector_multiply(m, &r->direction);
	return (result);
}
