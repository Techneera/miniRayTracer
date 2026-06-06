#include "canvas.h"
#include "libft.h"
#include <stdlib.h>

bool	canvas_constructor(int width, int height, t_canvas *canvas)
{
	if (canvas->mlx == NULL)
		return (false);
	canvas->img.img = mlx_new_image(canvas->mlx, width, height);
	if (canvas->img.img == NULL)
		return (false);
	canvas->img.addr = mlx_get_data_addr(canvas->img.img, &canvas->img.bpp,
			&canvas->img.line_len, &canvas->img.endian);
	if (canvas->img.addr == NULL)
		return (false);
	canvas->width = width;
	canvas->height = height;
	canvas->bg_color = color_constructor(0.0f, 0.0f, 0.0f);
	return (true);
}

void	canvas_destructor(t_canvas *c)
{
	if (c == NULL || c->mlx == NULL)
		return ;
	if (c->img.img)
	{
		mlx_destroy_image(c->mlx, c->img.img);
		c->img.img = NULL;
	}
	if (c->win)
	{
		mlx_destroy_window(c->mlx, c->win);
		c->win = NULL;
	}
	mlx_destroy_display(c->mlx);
	free(c->mlx);
	c->mlx = NULL;
}
