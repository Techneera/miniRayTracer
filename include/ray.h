#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "matrix.h"
# include "shades.h"

# ifndef MAX_INTERSECTION
#  define MAX_INTERSECTION 10
# endif

typedef enum e_shape_type
{
	SHAPE_SPHERE,
	SHAPE_PLANE,
	SHAPE_TEST
}	t_shape_type;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_shape
{
	t_shape_type	type;
	int				id;
	t_mat4			transform;
	t_mat4			transform_inv;
	t_material		material;
}	t_shape;

typedef struct s_sphere
{
	t_shape	shape;
	t_vec3	center;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_shape		shape;
}	t_plane;

typedef union u_object
{
	t_sphere	sp;
	t_plane		pl;
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

t_shape			test_shape(void);
void			set_transform(t_shape *s, t_mat4 t);
t_intersect		intersect(t_ray ray, t_shape *shape);
t_vec3			normal_at(t_shape *s, t_vec3 world_point);
int				get_shape_id(void);

t_sphere		sphere(void);
t_intersect		local_intersect_sphere(t_sphere *sphere, t_ray local_ray);
t_vec3			local_normal_at_sphere(t_sphere *sphere, t_vec3 local_point);

t_plane 		plane(void);
t_vec3  		local_normal_at_plane(void);
t_intersect		local_intersect_plane(t_plane *plane, t_ray ray);

void			sphere_set_transform(t_sphere *s, t_mat4 t);
t_intersect		sphere_intersect(t_ray ray, t_sphere sphere);

t_intersection	intersection(float t, t_object object);
t_intersect		*intersections(t_intersection *items, t_intersect *result, int size);
t_intersection	*hit(t_intersect *items, t_intersection *smallest, int size);

t_ray			ray_transform(t_ray r, t_mat4 m);
#endif
