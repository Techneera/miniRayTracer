#ifndef LIBRT_H
# define LIBRT_H

# include "vector.h"
# include "matrix.h"
# include "shades.h"

# define MAX_OBJECTS 50
# define EPSILON 0.00001

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;


typedef enum e_shape_type
{
	SHAPE_SPHERE,
	SHAPE_PLANE,
	SHAPE_TEST
}	t_shape_type;

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
	t_shape_type	type;
	t_sphere		sp;
	t_plane			pl;
}	t_object;

typedef struct s_objects
{
	t_type	type;
	t_object object;
} t_objects;

typedef struct s_ambient_light
{
	float	ratio;
	t_vec3	color;
} t_ambient_light;

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	float		field_of_view;
	t_mat4		transform;
	float		pixel_size;
	float		half_width;
	float		half_height;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	t_vec3	color;
	float	brightness;
} t_light;

typedef struct s_scene
{
	t_ambient_light	a_light;
	t_camera 		camera;
	t_light 		light;
	t_objects 		objects[MAX_OBJECTS];
	int				object_count;
} t_scene;

#endif
