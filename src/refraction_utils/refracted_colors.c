#include "ray.h"
#include "refraction.h"
#include "shades.h"

t_vec3	refracted_color(t_world *world, t_computation *comps, int depth)
{
	t_ray	refracted_ray;
	float	n_ratio;
	float	cos_i;
	float	sin2_t;
	float	cos_t;

	if (depth <= 0 || comps->object->material.transparency == 0.0f)
		return (color_constructor(0.0f, 0.0f, 0.0f));
	n_ratio = comps->n1 / comps->n2;
	cos_i = vector_dot_product(comps->eyev, comps->normalv);
	sin2_t = (n_ratio * n_ratio) * (1.0f - (cos_i * cos_i));
	if (sin2_t > 1.0)
		return (color_constructor(0.0f, 0.0f, 0.0f));
	cos_t = sqrtf(1.0f - sin2_t);
	refracted_ray = ray_constructor(comps->under_point,
			vector_sub(vector_scale(comps->normalv, (n_ratio * cos_i) - cos_t),
				vector_scale(comps->eyev, n_ratio)));
	return (vector_scale(color_at(world, &refracted_ray, depth - 1),
			comps->object->material.transparency));
}

float	schlick(t_computation *comps)
{
	float	cos_i;
	float	n_ratio;
	float	sin2_t;
	float	r0;
	float	inv_cos;

	cos_i = vector_dot_product(comps->eyev, comps->normalv);
	if (comps->n1 > comps->n2)
	{
		n_ratio = comps->n1 / comps->n2;
		sin2_t = (n_ratio * n_ratio) * (1.0f - (cos_i * cos_i));
		if (sin2_t > 1.0f)
			return (1.0f);
		cos_i = sqrtf(1.0f - sin2_t);
	}
	r0 = ((comps->n1 - comps->n2) / (comps->n1 + comps->n2));
	r0 = r0 * r0;
	inv_cos = 1.0f - cos_i;
	return (r0 + (1.0f - r0) * (inv_cos * inv_cos * inv_cos * inv_cos
			* inv_cos));
}
