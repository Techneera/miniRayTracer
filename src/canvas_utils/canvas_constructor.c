#include <stdlib.h>
#include "canvas.h"

bool	canvas_constructor(int width, int height, t_canvas *canvas)
{
	canvas->mlx = mlx_init();
	if (canvas->mlx == NULL)
		return (false);
	canvas->img.img = mlx_new_image(canvas->mlx, width, height);
	if (canvas->img.img == NULL)
		return (false);
	canvas->img.addr = mlx_get_data_addr(
		canvas->img.img,
		&canvas->img.bpp,
		&canvas->img.line_len,
		&canvas->img.endian
	);
	canvas->width = width;
	canvas->height = height;
	canvas->bg_color = color_constructor(0, 0, 0);
	return (true);
}

void	canvas_destructor(t_canvas *c)
{
	if (c->mlx == NULL)
		return ;
	mlx_destroy_image(c->mlx, c->img.img);
	mlx_destroy_display(c->mlx);
	free(c->mlx);
}

void	write_pixel(t_canvas *c, int x, int y, t_vec3 color)
{
	char	*dest;

	dest = c->img.addr + (y * c->img.line_len + x * (c->img.bpp / 8));
	*(t_uint *)dest = (t_uint) color_to_int(color);
}
