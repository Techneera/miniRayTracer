#ifndef LIBRT_H
# define LIBRT_H

typedef struct s_scene
{
	struct s_ambient_light;
	struct s_camera;
	struct s_light;
	union u_objects
	{
		struct s_sphere;
		struct s_plane;
		struct s_cylinder;
	};
} t_scene;

#endif
