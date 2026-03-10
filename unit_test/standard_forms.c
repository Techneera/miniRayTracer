#include "scene.h"
#include "canvas.h"
#include "scene_api.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

// -----------------------------------------------------------------------------
// Scene Construction
// -----------------------------------------------------------------------------

static void build_room_scene(t_scene *scene)
{
	t_object *floor;
	t_object *left_wall;
	t_object *right_wall;
	t_object *middle_sphere;
	t_object *right_sphere;
	t_object *left_sphere;
	
	scene->world.object_count = 0;
	
	// Lighting setup
	scene->world.a_light.ratio = 0.1f;
	scene->world.a_light.color = color_constructor(1.0f, 1.0f, 1.0f);
	scene->world.light.position = point_constructor(-10.0f, 10.0f, -10.0f);
	scene->world.light.color = color_constructor(1.0f, 1.0f, 1.0f);
	scene->world.light.brightness = 1.0f;
	
	// 1. Floor
	floor = spawn_plane(&scene->world);
	set_pattern(floor, pattern_scaled(PATTERN_CHECKER,
			color_constructor(0.8f, 0.8f, 0.8f),
			color_constructor(0.2f, 0.2f, 0.2f), 0.25f));
	set_optics(floor, (t_optics_params){0.7f, 0.3f, 0.2f, 0.0f, 1.0f});
	
	// 2. Left Wall
	left_wall = spawn_plane(&scene->world);
	apply_rot_x(left_wall, M_PI / 2.0f);      // Stand it up
	apply_rot_y(left_wall, -M_PI / 4.0f);     // Angle it inwards (-45 deg)
	apply_translation(left_wall, 0.0f, 0.0f, 5.0f); // Push it back
	set_color(left_wall, color_constructor(0.6f, 0.4f, 0.5f)); // Muted mauve
	set_optics(left_wall, (t_optics_params){0.9f, 0.1f, 0.0f, 0.0f, 1.0f});
	
	// 3. Right Wall
	right_wall = spawn_plane(&scene->world);
	apply_rot_x(right_wall, M_PI / 2.0f);     // Stand it up
	apply_rot_y(right_wall, M_PI / 4.0f);      // Angle it inwards (+45 deg)
	apply_translation(right_wall, 0.0f, 0.0f, 5.0f); // Push it back
	set_color(right_wall, color_constructor(0.4f, 0.5f, 0.6f)); // Muted slate blue
	set_optics(right_wall, (t_optics_params){0.9f, 0.1f, 0.0f, 0.0f, 1.0f});
	
	// --- Objects (3 Spheres) ---
	
	// 1. Middle Sphere (Glass / Perfect Mirror)
	middle_sphere = spawn_sphere(&scene->world);
	apply_translation(middle_sphere, -0.5f, 1.0f, 0.5f);
	set_color(middle_sphere, color_constructor(0.0f, 0.0f, 0.0f));
	set_optics(middle_sphere, (t_optics_params){0.1f, 0.9f, 0.9f, 1.0f,
			1.5f}); // High reflection, Glass RI
	
	// 2. Right Sphere (Gradient)
	right_sphere = spawn_sphere(&scene->world);
	apply_scale(right_sphere, 0.5f, 0.5f, 0.5f);
	apply_translation(right_sphere, 1.5f, 0.5f, -0.5f);
	set_pattern(right_sphere, pattern_scaled(PATTERN_GRADIENT,
			color_constructor(1.0f, 0.0f, 0.0f),
			color_constructor(0.0f, 0.0f, 1.0f), 1.0f));
	set_optics(right_sphere, (t_optics_params){0.7f, 0.3f, 0.1f, 0.0f,
			1.0f});
	
	// 3. Left Sphere (Solid/Matte)
	left_sphere = spawn_sphere(&scene->world);
	apply_scale(left_sphere, 0.33f, 0.33f, 0.33f);
	apply_translation(left_sphere, -1.5f, 0.33f, -0.75f);
	set_color(left_sphere, color_constructor(0.2f, 0.8f, 0.2f)); // Bright green
	set_optics(left_sphere, (t_optics_params){0.9f, 0.1f, 0.0f, 0.0f, 1.0f});
	
	// --- Camera Setup ---
	scene->camera = camera_constructor(WIN_WIDTH, WIN_HEIGHT, 60.0f);
	scene->camera.transform = view_transform(
	    point_constructor(0.0f, 1.5f, -5.0f),  // Position (Looking from front-center)
	    point_constructor(0.0f, 1.0f, 0.0f),   // Target (Looking at center)
	    vector_constructor(0.0f, 1.0f, 0.0f)   // Up Vector
	);
}

// -----------------------------------------------------------------------------
// Main Execution
// -----------------------------------------------------------------------------

int main(void)
{
	t_scene     scene;
	t_canvas    canvas;
	
	build_room_scene(&scene);
	
	canvas.mlx = mlx_init();
	if (canvas.mlx == NULL)
		return (ft_error("Unable to initialize MLX\n"), 1);
	render(&canvas, &scene.camera, &scene.world);
	
	canvas.win = mlx_new_window(canvas.mlx, WIN_WIDTH, WIN_HEIGHT, "Show Room");
	mlx_put_image_to_window(canvas.mlx, canvas.win, canvas.img.img, 0, 0);
	mlx_hook(canvas.win, 2, 1L << 0, key_hook, &canvas);
	mlx_hook(canvas.win, 17, 0L, close_program, &canvas);
	
	printf("Render complete! Press ESC to exit.\n");
	mlx_loop(canvas.mlx);
	
	return (0);
}
