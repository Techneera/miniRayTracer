#ifndef LIBRT_H
# define LIBRT_H

# include "vector.h"
# include "matrix.h"
# include "shades.h"

# define MAX_OBJECTS 50
# define EPSILON 0.001

#ifndef WIN_WIDTH
# define WIN_WIDTH 1080
#endif

#ifndef WIN_HEIGHT
# define WIN_HEIGHT 920
#endif

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CUBE,
	CONE
}	t_obj_type;

typedef struct s_cylinder
{
	float	min_y;
	float	max_y;
	bool	closed;
}	t_cylinder;

typedef struct s_object
{
	int			id;
	t_obj_type	type;
	t_mat4		transform;
	t_mat4		transform_inv;
	t_cylinder	cy;
	t_cylinder	co;
	t_material	material;
}	t_object;

typedef struct s_ambient_light
{
	float	ratio;
	t_vec3	color;
}	t_ambient_light;

typedef struct s_light
{
	t_vec3	position;
	t_vec3	color;
	float	brightness;
}	t_light;

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

typedef struct s_world
{
	t_ambient_light	a_light;
	t_light			light;
	t_object		objects[MAX_OBJECTS];
	int				object_count;
}	t_world;

typedef struct s_scene
{
	t_camera	camera;
	t_world		world;
}	t_scene;

#endif
