#include "canvas.h"

int	color_to_int(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = round(color.x * RGB_MAX);
	g = round(color.y * RGB_MAX);
	b = round(color.z * RGB_MAX);
	return ((r << 16) | (g << 8) | b);
}
