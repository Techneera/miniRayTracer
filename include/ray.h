#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "matrix.h"

# ifndef MAX_INTERSECTION
#  define MAX_INTERSECTION 10
# endif

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_sphere
{
	int		id;
	t_vec3	center;
	float	radius;
	t_mat4	transform;
	t_mat4	transform_inv;
}	t_sphere;

typedef union u_object
{
	t_sphere	sp;
}	t_object;

typedef struct s_intersection
{
	float		t;
	t_object	object;
}	t_intersection;

typedef struct s_intersect
{
	int				count;
	t_intersection	i[MAX_INTERSECTION];
}	t_intersect;

struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
};

t_ray			ray_constructor(t_vec3 origin, t_vec3 direction);
t_vec3			ray_position(t_ray ray, float t);

t_sphere		sphere(void);
t_intersect		sphere_intersect(t_ray ray, t_sphere sphere);

t_intersection	intersection(float t, t_object object);
t_intersect		*intersections(t_intersection *items, t_intersect *result, int size);
t_intersection	*hit(t_intersect *items, t_intersection *smallest, int size);

t_ray			ray_transform(t_ray r, t_mat4 m);
#endif
