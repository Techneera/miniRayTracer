#include "parser.h"
#include "scene.h"
#include "canvas.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	t_scene     scene;
	t_canvas    canvas;
	
	if (argc != 2)
	    ft_error("Invalid number of arguments. Usage: ./miniRT <scene.rt>\n");
	scene.world.object_count = 0;
	if (load_scene(argv[1], &scene) != 0)
	    ft_error("Failed to parse the scene file. Check formatting and extension.\n");
	canvas.mlx = mlx_init();
	if (canvas.mlx == NULL)
	    ft_error("Failed to initialize MLX.\n");
	render(&canvas, &scene.camera, &scene.world);
	canvas.win = mlx_new_window(canvas.mlx, scene.camera.hsize, scene.camera.vsize, "miniRT");
	if (!canvas.win)
	    ft_error("Failed to create MLX window.\n");
	mlx_put_image_to_window(canvas.mlx, canvas.win, canvas.img.img, 0, 0);
	mlx_hook(canvas.win, 2, 1L << 0, key_hook, &canvas);
	mlx_hook(canvas.win, 17, 0L, close_program, &canvas);
	mlx_loop(canvas.mlx);
	return (0);
}
