#ifndef SCENE_API_H
# define SCENE_API_H

# include "librt.h"

/*			OBJECT SPWAN				*/
t_object	*spawn_sphere(t_world *world);
t_object	*spawn_plane(t_world *world);
t_object	*spawn_cylinder(t_world *world, float min_y, float max_y, bool closed);

/*			TRANSFORMATIONS				*/
void		chain_transform(t_object *obj, t_mat4 *new_transform);
void		apply_translation(t_object *obj, float x, float y, float z);
void		apply_scale(t_object *obj, float x, float y, float z);
void		apply_rot_x(t_object *obj, float angle);
void		apply_rot_y(t_object *obj, float angle);
void		apply_rot_z(t_object *obj, float angle);

/*			MATERIAL SETTERS			*/
void		set_color(t_object *obj, t_vec3 color);
void		set_pattern(t_object *obj, t_pattern_type type, t_vec3 color_a, t_vec3 color_b, float scale);
void		set_optics(t_object *obj, float diffuse, float specular, float reflective, float transparency, float refractive_index);

#endif
