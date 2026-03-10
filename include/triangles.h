#ifndef TRIANGLES_H
# define TRIANGLES_H

# include "vector.h"
# include "ray.h"

typedef struct	s_tri
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	normal;
	t_vec3	inv_normal;
}	t_tri;

t_tri		triangle_constructor(t_vec3 p1, t_vec3 p2, t_vec3 p3);

t_intersect	local_intersect_triangle(const t_object *triangle, const t_ray *ray);

#endif
