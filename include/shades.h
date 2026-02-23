#ifndef SHADES_H
#define SHADES_H

#include "patterns.h"
#include "vector.h"

typedef struct s_object t_object;
typedef struct s_light t_light;
typedef struct s_ambient_light t_ambient_light;

typedef struct s_material
{
	t_vec3		color;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
	float		reflective;
	t_pattern	pattern;
}	t_material;

t_vec3			reflect(t_vec3 in, t_vec3 normal);
t_vec3			lighting(t_material m, const t_object *obj, const t_light *light, const t_ambient_light *a_light, t_vec3 point, t_vec3 eyev, t_vec3 normalv, bool in_shadow);

t_material		new_material(float ambient, float diffuse, float specular, float shininess, float reflective, t_pattern pattern);

t_light	light_constructor(t_vec3 position, t_vec3 color, float brightness);
t_material		material_default(void);

#endif
