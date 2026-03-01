#include "scene.h"
#include "canvas.h"
#include "scene_api.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// -----------------------------------------------------------------------------
// Scene Construction
// -----------------------------------------------------------------------------

void build_glassbox_scene(t_scene *scene)
{
    t_object *floor;
    t_object *back_wall;
    t_object *glass_cube;
    t_object *inner_sphere;
    t_object *mirror_sphere;
    t_object *striped_cylinder;

    scene->world.object_count = 0;

    // --- 1. Environment & Lighting ---
    scene->world.a_light.ratio = 0.15f;
    scene->world.a_light.color = color_constructor(1.0f, 1.0f, 1.0f);
    scene->world.light.position = point_constructor(-5.0f, 10.0f, -10.0f);
    scene->world.light.color = color_constructor(1.0f, 1.0f, 1.0f);
    scene->world.light.brightness = 1.0f;

    // Floor (Checkered to show off refraction bending)
    floor = spawn_plane(&scene->world);
    set_pattern(floor, PATTERN_CHECKER, 
                color_constructor(0.9f, 0.9f, 0.9f),
                color_constructor(0.2f, 0.2f, 0.2f), 0.5f);
    set_optics(floor, 0.8f, 0.2f, 0.3f, 0.0f, 1.0f); // Slightly reflective

    // Back Wall
    back_wall = spawn_plane(&scene->world);
    apply_rot_x(back_wall, M_PI / 2.0f);
    apply_translation(back_wall, 0.0f, 0.0f, 10.0f);
    set_color(back_wall, color_constructor(0.1f, 0.1f, 0.1f)); // Dark grey
    set_optics(back_wall, 0.9f, 0.1f, 0.0f, 0.0f, 1.0f);

    // --- 2. The Glass Box ---
    // A 2x2x2 transparent cube. Because it has flat sides, it will distort 
    // the background very differently than a sphere!
    glass_cube = spawn_cube(&scene->world);
    apply_scale(glass_cube, 2.0f, 2.0f, 2.0f);
    apply_rot_y(glass_cube, M_PI / 6.0f); // Rotate 30 degrees to catch edges
    apply_translation(glass_cube, 0.0f, 2.0f, 0.0f);
    set_color(glass_cube, color_constructor(0.0f, 0.0f, 0.0f)); 
    // Diff: 0.0, Spec: 1.0, Refl: 0.9, Trans: 1.0, RI: 1.5 (Glass)
    set_optics(glass_cube, 0.0f, 1.0f, 0.9f, 1.0f, 1.5f);
    glass_cube->material.ambient = 0.0f;
    glass_cube->material.shininess = 300.0f;

    // --- 3. The Nested Object ---
    // A sphere placed perfectly inside the glass cube
    inner_sphere = spawn_sphere(&scene->world);
    apply_scale(inner_sphere, 0.8f, 0.8f, 0.8f);
    apply_translation(inner_sphere, 0.0f, 2.0f, 0.0f);
    set_pattern(inner_sphere, PATTERN_RING, 
                color_constructor(1.0f, 0.1f, 0.1f), 
                color_constructor(1.0f, 1.0f, 1.0f), 0.2f);
    set_optics(inner_sphere, 0.9f, 0.1f, 0.0f, 0.0f, 1.0f); // Pure Matte

    // --- 4. Flanking Objects ---
    // Perfect Mirror Sphere to the right
    mirror_sphere = spawn_sphere(&scene->world);
    apply_scale(mirror_sphere, 1.5f, 1.5f, 1.5f);
    apply_translation(mirror_sphere, 3.5f, 1.5f, 2.0f);
    set_color(mirror_sphere, color_constructor(0.0f, 0.0f, 0.0f));
    set_optics(mirror_sphere, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f); // 100% reflective
    mirror_sphere->material.ambient = 0.0f;

    // Striped Cylinder (or use spawn_sphere if cylinder isn't ready) to the left
    striped_cylinder = spawn_cylinder(&scene->world, -1.0f, 1.0f, true);
    apply_scale(striped_cylinder, 1.2f, 1.2f, 1.2f);
    apply_rot_x(striped_cylinder, -M_PI / 4.0f); // Tilt it forward
    apply_rot_y(striped_cylinder, M_PI / 4.0f);  // Angle it right
    apply_translation(striped_cylinder, -3.5f, 1.2f, 1.0f);
    set_pattern(striped_cylinder, PATTERN_STRIPE, 
                color_constructor(0.2f, 0.8f, 0.2f), 
                color_constructor(0.1f, 0.1f, 0.5f), 0.3f);
    set_optics(striped_cylinder, 0.7f, 0.3f, 0.2f, 0.0f, 1.0f); // Slight shine

    // --- 5. Camera Setup ---
    scene->camera = camera_constructor(WIN_WIDTH, WIN_HEIGHT, 65.0f);
    scene->camera.transform = view_transform(
        point_constructor(0.0f, 4.0f, -7.0f),  // Looking from above and back
        point_constructor(0.0f, 1.5f, 0.0f),   // Looking down at the cube
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
	
	build_glassbox_scene(&scene);
	
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
