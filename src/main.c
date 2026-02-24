#include "parser.h"
#include "scene.h"
#include "canvas.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static
void	ft_error(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

int main(int argc, char **argv)
{
	t_scene     scene;
	t_canvas    canvas;
	void        *mlx;
	
	if (argc != 2)
	    ft_error("Invalid number of arguments. Usage: ./miniRT <scene.rt>");
	scene.world.object_count = 0;
	if (load_scene(argv[1], &scene) != 0)
	    ft_error("Failed to parse the scene file. Check formatting and extension.");
	mlx = mlx_init();
	if (!mlx)
	    ft_error("Failed to initialize MLX.");
	canvas = render(mlx, &scene.camera, &scene.world);
	if (!canvas.img.img)
	    ft_error("Failed to allocate image buffer.");
	canvas.win = mlx_new_window(mlx, scene.camera.hsize, scene.camera.vsize, "miniRT");
	if (!canvas.win)
	    ft_error("Failed to create MLX window.");
	mlx_put_image_to_window(mlx, canvas.win, canvas.img.img, 0, 0);
	mlx_hook(canvas.win, 2, 1L << 0, key_hook, &canvas);
	mlx_hook(canvas.win, 17, 0L, close_program, &canvas);
	mlx_loop(mlx);
	return (0);
}
