#ifndef REFRACTION_H
# define REFRACTION_H

# include "scene.h"

# define MAX_CONTAINERS 36

void	manage_containers(const t_object *containers[], \
int *count, const t_object *obj);
t_vec3	refracted_color(t_world *world, t_computation *comps, int depth);
float	schlick(t_computation *comps);

#endif
