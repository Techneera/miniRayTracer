#include "canvas.h"

int	color_to_int(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	if (color.x > 1.0f)
		color.x = 1.0f;
	if (color.y > 1.0f)
		color.y = 1.0f;
	if (color.z > 1.0f)
		color.z = 1.0f;
	r = round(color.x * RGB_MAX);
	g = round(color.y * RGB_MAX);
	b = round(color.z * RGB_MAX);
	return ((r << 16) | (g << 8) | b);
}
