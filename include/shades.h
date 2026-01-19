#ifndef SHADES_H
#define SHADES_H

#include "matrix.h"
#include "vector.h"

typedef struct s_material
{
	t_vec3	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

typedef struct s_point_light
{
	t_vec3	position;
	t_vec3	intensity;
}	t_point_light;

t_vec3			normal_at(t_sphere s, t_vec3 world_point);
t_vec3			reflect(t_vec3 in, t_vec3 normal);

t_material		new_material(void);

t_point_light	point_light(t_vec3 position, t_vec3 intensity);

#endif
