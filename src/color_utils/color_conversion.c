#include "color.h"

int	color_to_int(t_vec3 color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = round(color.x * RGB_MAX);
	g = round(color.y * RGB_MAX);
	b = round(color.z * RGB_MAX);
	return ((r << 16) | (g << 8) | b);
}
