#include "color.h"

t_vec3 color_constructor(double r, double g, double b)
{
	t_vec3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	color.w = 2.0;
	return (color);
}
