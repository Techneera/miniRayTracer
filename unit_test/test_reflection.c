#include "vector.h"
#include "matrix.h"
#include "ray.h"
#include "shades.h"
#include "scene.h"
#include <stdio.h>

int	main(void)
{
	t_computation	comps;
	t_object		shape;
	t_intersection	i;
	t_ray			r;

	shape.pl = plane();
	r = ray_constructor(
			point_constructor(0.0, 1.0, -1.0),
			vector_constructor(0.0, -0.70711, 0.70711)
			);
	i = intersection(0.70711, shape);
	comps = prepare_computations(i, r);
}
