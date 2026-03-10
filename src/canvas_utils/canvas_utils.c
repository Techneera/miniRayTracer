#include "canvas.h"
#include "libft.h"

void	write_pixel(t_canvas *c, int x, int y, t_vec3 color)
{
	char	*dest;

	if (x >= c->width || x < 0 || y >= c->height || y < 0)
		return ;
	dest = c->img.addr + (y * c->img.line_len + x * (c->img.bpp / 8));
	*(t_uint *)dest = (t_uint)color_to_int(color);
}

int	key_hook(int keycode, t_canvas *canvas)
{
	if (keycode == 65307)
		close_program(canvas);
	return (0);
}

int	close_program(t_canvas *canvas)
{
	canvas_destructor(canvas);
	exit(0);
	return (0);
}

void	ft_error(char *msg)
{
	ft_putstr("Error\n");
	ft_putstr(msg);
}
