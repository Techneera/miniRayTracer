#ifndef SHADES_H
#define SHADES_H

#include "matrix.h"
#include "vector.h"

t_vec3	normal_at(t_sphere s, t_vec3 world_point);
t_vec3	reflect(t_vec3 in, t_vec3 normal);

#endif
