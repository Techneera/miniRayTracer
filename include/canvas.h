#ifndef COLOR_H
# define COLOR_H
# define RGB_MAX 255.0

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <mlx.h>
# include "vector.h"

typedef unsigned int t_uint;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_canvas
{
	void	*mlx;
	t_img	img;
	int		width;
	int		height;
	t_vec3	bg_color;
}	t_canvas;

t_vec3	color_constructor(double r, double g, double b);
t_vec3	color_add(t_vec3 u, t_vec3 v);
t_vec3	color_subtract(t_vec3 u, t_vec3 v);
t_vec3	color_scalar(t_vec3 u, double scalar);
t_vec3	color_multiply(t_vec3 u, t_vec3 v);

int		color_to_int(t_vec3 color);

bool	canvas_constructor(int width, int height, t_canvas *canvas);
void	write_pixel(t_canvas *c, int x, int y, t_vec3 color);

#endif
