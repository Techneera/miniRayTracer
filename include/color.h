#ifndef COLOR_H
# define COLOR_H
# define RGB_MAX 0.003921569

# include <stdint.h>
# include "vector.h"

t_vec3	color_constructor(double r, double g, double b);
t_vec3	color_add(t_vec3 u, t_vec3 v);
t_vec3	color_subtract(t_vec3 u, t_vec3 v);
t_vec3	color_scalar(t_vec3 u, double scalar);
t_vec3	color_multiply(t_vec3 u, t_vec3 v);

#endif
