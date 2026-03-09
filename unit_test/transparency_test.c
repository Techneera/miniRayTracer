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

static void build_glass_showcase(t_scene *scene)
{
    t_object *floor;
    t_object *wall;
    t_object *clear_glass;
    t_object *tinted_glass;
    t_object *anchor_sphere;
    
    scene->world.object_count = 0;
    
    // Lighting: Placed specifically to catch tight specular highlights on the glass
    scene->world.a_light.ratio = 0.1f;
    scene->world.a_light.color = color_constructor(1.0f, 1.0f, 1.0f);
    scene->world.light.position = point_constructor(-10.0f, 10.0f, -10.0f);
    scene->world.light.color = color_constructor(1.0f, 1.0f, 1.0f);
    scene->world.light.brightness = 1.0f;
    
    // --- The Environment ---
    
    // The Floor (Checkered so we can see the refraction bend the straight lines)
    floor = spawn_plane(&scene->world);
    set_pattern(floor, pattern_scaled(PATTERN_CHECKER,
                color_constructor(0.8f, 0.8f, 0.8f),
                color_constructor(0.2f, 0.2f, 0.2f), 0.25f));
    set_optics(floor, (t_optics_params){0.7f, 0.3f, 0.2f, 0.0f, 1.0f});
    
    // Back Wall (Dark grey to contrast the bright highlights)
    wall = spawn_plane(&scene->world);
    apply_rot_x(wall, M_PI / 2.0f); 
    apply_translation(wall, 0.0f, 0.0f, 5.0f);
    set_color(wall, color_constructor(0.2f, 0.2f, 0.2f));
    set_optics(wall, (t_optics_params){0.9f, 0.1f, 0.0f, 0.0f, 1.0f});
    
    // --- The Test Objects ---

    // 1. Clear Glass Sphere (Rules 1, 2, and 4)
    // Clear glass: High reflection/transparency, ZERO diffuse/ambient, tight highlight
    clear_glass = spawn_sphere(&scene->world);
    apply_translation(clear_glass, -1.2f, 1.0f, 0.0f);
    set_color(clear_glass, color_constructor(0.0f, 0.0f, 0.0f)); // Black base
    set_optics(clear_glass, (t_optics_params){0.0f, 1.0f, 0.9f, 0.9f,
                1.5f}); // Diffuse 0.0, Spec 1.0
    clear_glass->material.ambient = 0.0f;       // Rule 2
    clear_glass->material.shininess = 300.0f;   // Rule 4
    
    // 2. Tinted Red Glass Mirror (Rules 3 and 4)
    // Tinted glass: Dark base color, low diffuse, high reflection, tight highlight
    tinted_glass = spawn_sphere(&scene->world);
    apply_translation(tinted_glass, 1.2f, 1.0f, 0.0f);
    set_color(tinted_glass, color_constructor(0.2f, 0.0f, 0.0f)); // Very dark red (Rule 3)
    set_optics(tinted_glass, (t_optics_params){0.1f, 1.0f, 0.8f, 0.8f,
                1.5f}); // Slight diffuse to show color
    tinted_glass->material.ambient = 0.05f;     // Very low ambient (Rule 3)
    tinted_glass->material.shininess = 300.0f;  // Rule 4

    // 3. Anchor Object (Behind the glass)
    // A solid, brightly colored sphere placed in the background so the glass has
    // something obvious to refract and reflect.
    anchor_sphere = spawn_sphere(&scene->world);
    apply_scale(anchor_sphere, 1.5f, 1.5f, 1.5f);
    apply_translation(anchor_sphere, 0.0f, 1.5f, 3.0f);
    set_pattern(anchor_sphere, pattern_scaled(PATTERN_GRADIENT,
                color_constructor(0.0f, 0.0f, 1.0f),
                color_constructor(0.0f, 1.0f, 0.0f), 1.0f)); // Green
    set_optics(anchor_sphere, (t_optics_params){0.8f, 0.2f, 0.0f, 0.0f,
                1.0f}); // Matte

    // --- Camera Setup ---
    scene->camera = camera_constructor(WIN_WIDTH, WIN_HEIGHT, 60.0f);
    scene->camera.transform = view_transform(
        point_constructor(0.0f, 1.5f, -5.0f),  
        point_constructor(0.0f, 1.0f, 0.0f),   
        vector_constructor(0.0f, 1.0f, 0.0f)   
    );
}
// -----------------------------------------------------------------------------
// Main Execution
// -----------------------------------------------------------------------------

int main(void)
{
	t_scene     scene;
	t_canvas    canvas;
	
	build_glass_showcase(&scene);
	
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
