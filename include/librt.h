#ifndef LIBRT_H
# define LIBRT_H

# include "ray.h"

# define MAX_OBJECTS 50

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

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
	float	brightness;
} t_light;

typedef struct s_scene
{
	t_ambient_light a_light;
	t_camera camera;
	t_light light;
	t_objects objects[MAX_OBJECTS];
} t_scene;

#endif
