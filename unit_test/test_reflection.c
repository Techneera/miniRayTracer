#include "vector.h"
#include "matrix.h"
#include "ray.h"
#include "shades.h"
#include "scene.h"
#include <stdio.h>

int	main(void)
{
t_world		world;
	t_camera	camera;
	t_canvas	canvas;
	void		*win;

	// 1. Initialize empty world
	world.object_count = 0;
	
	// 2. Light Source (White light, above and to the left)
	world.light = point_light(
		point_constructor(-10, 10, -10), 
		color_constructor(1, 1, 1)
	);

	// 3. The Floor (Slightly reflective, matte finish)
	t_plane floor = plane();
	// params: ambient(0.1), diffuse(0.7), specular(0.3), shininess(200), reflective(0.4)
	floor.shape.material = new_material(0.1, 0.7, 0.3, 200.0, 0.4, pattern_default());
	floor.shape.material.color = color_constructor(1.0, 0.9, 0.9); // Off-white
	world.objects[world.object_count].type = PLANE;
	world.objects[world.object_count++].object.pl = floor;

	// 4. Middle Sphere (The "Perfect Mirror")
	// To make a mirror, diffuse is 0, base color is black, reflective is 1.0
	t_sphere middle = sphere();
	set_transform(&middle.shape, matrix_translation(-0.5, 1, 0.5));
	middle.shape.material = new_material(0.0, 0.0, 1.0, 500.0, 1.0, pattern_default());
	middle.shape.material.color = color_constructor(0.0, 0.0, 0.0);
	world.objects[world.object_count].type = SPHERE;
	world.objects[world.object_count++].object.sp = middle;

	// 5. Right Sphere (Semi-reflective colored ball)
	// Darker base colors (like this dark blue) show off reflections much better than bright ones.
	t_sphere right = sphere();
	set_transform(&right.shape, matrix_multiply(
		matrix_translation(1.5, 0.5, -0.5), 
		matrix_scale(0.5, 0.5, 0.5)
	));
	right.shape.material = new_material(0.1, 0.5, 1.0, 300.0, 0.5, pattern_default());
	right.shape.material.color = color_constructor(0.1, 0.1, 0.8); // Dark Blue
	world.objects[world.object_count].type = SPHERE;
	world.objects[world.object_count++].object.sp = right;

	// 6. Left Sphere (Matte, non-reflective)
	// Just a standard object for the other spheres to reflect.
	t_sphere left = sphere();
	set_transform(&left.shape, matrix_multiply(
		matrix_translation(-1.5, 0.33, -0.75), 
		matrix_scale(0.33, 0.33, 0.33)
	));
	left.shape.material = new_material(0.1, 0.9, 0.1, 10.0, 0.0, pattern_default());
	left.shape.material.color = color_constructor(1.0, 0.2, 0.1); // Bright Red
	world.objects[world.object_count].type = SPHERE;
	world.objects[world.object_count++].object.sp = left;

	// 7. Setup Camera
	// Looking from slightly above and back, down at the middle sphere
	camera = camera_constructor(800, 600, M_PI / 3.0);
	camera.transform = view_transform(
		point_constructor(0, 1.5, -5), // Camera Position
		point_constructor(0, 1, 0),    // Looking at
		vector_constructor(0, 1, 0)    // Up vector
	);

	// 8. Render
	printf("Rendering scene...\n");
	canvas = render(camera, world);

	// 9. Display (Assuming standard MLX setup)
	win = mlx_new_window(canvas.mlx, canvas.width, canvas.height, "Reflection Sandbox");
	mlx_put_image_to_window(canvas.mlx, win, canvas.img.img, 0, 0);
	mlx_key_hook(win, key_hook, &canvas);
	
	printf("Done! Press ESC to exit.\n");
	mlx_loop(canvas.mlx);
	
	return (0);
}
