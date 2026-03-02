#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "matrix.h"
# include "librt.h"

# ifndef MAX_INTERSECTION
#  define MAX_INTERSECTION 64
# endif

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_intersection
{
	float			t;
	const t_object	*object;
}	t_intersection;

typedef struct s_intersect
{
	int				count;
	t_intersection	i[MAX_INTERSECTION];
}	t_intersect;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
}	t_quadratic;

t_ray			ray_constructor(t_vec3 origin, t_vec3 direction);
t_vec3			ray_position(const t_ray *ray, float t);
t_ray			ray_transform(const t_ray *r, const t_mat4 *m);

t_intersect		intersect(const t_ray *ray, const t_object *obj);
t_vec3			normal_at(const t_object *obj, t_vec3 world_point);
t_intersection	intersection(float t, const t_object *obj);
t_intersect		*intersections(t_intersection *items, t_intersect *result, int size);
t_intersection	*hit(t_intersect *items, t_intersection *smallest, int size);

void			set_transform(t_object *obj, const t_mat4 *t);

t_object		test_object(void);
int				get_shape_id(void);

t_intersect		local_intersect_sphere(const t_object *sphere, const t_ray *ray);
t_vec3			local_normal_at_sphere(t_vec3 local_point);

t_vec3  		local_normal_at_plane(void);
t_intersect		local_intersect_plane(const t_object *plane, const t_ray *ray);

#endif
