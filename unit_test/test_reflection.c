#include "vector.h"
#include "matrix.h"
#include "shades.h"
#include "librt.h"
#include "ray.h"
#include "scene.h"
#include <stdio.h>

static
int close_program(t_canvas *c)
{
    canvas_destructor(c);
    mlx_destroy_window(c->mlx, c->win);
    exit(0);
    return (0);
}

static
int handle_keypress(int keycode, t_canvas *c)
{
    if (keycode == 65307)
        close_program(c);
    return (0);
}

int main(void)
{
    t_world     world;
    t_camera    camera;
    t_canvas    canvas;
    void        *win;
    t_object    *obj;
    t_mat4      ident, trans, scale, combo;

    // 1. Initialize empty world
    world.object_count = 0;
    
    // Default Ambient Light (Required by the new pipeline)
    world.a_light.ratio = 0.1f;
    world.a_light.color = color_constructor(1.0f, 1.0f, 1.0f);
    
    // 2. Light Source (White light, above and to the left)
    world.light.position = point_constructor(-10.0f, 10.0f, -10.0f);
    world.light.color = color_constructor(1.0f, 1.0f, 1.0f);
    world.light.brightness = 1.0f;

    // Helper: Initialize an identity matrix for objects that don't move
    matrix_identity(&ident);

    // 3. The Floor (Slightly reflective, matte finish)
    obj = &world.objects[world.object_count++];
    obj->type = PLANE;
    obj->id = get_shape_id();
    set_transform(obj, &ident);
    // params: ambient(0.1), diffuse(0.7), specular(0.3), shininess(200), reflective(0.4)
    obj->material = new_material(0.1f, 0.7f, 0.3f, 200.0f, 0.4f, pattern_default());
    obj->material.color = color_constructor(1.0f, 0.9f, 0.9f); // Off-white

    // 4. Middle Sphere (The "Perfect Mirror")
    // To make a mirror: diffuse is 0, base color is black, reflective is 1.0
    obj = &world.objects[world.object_count++];
    obj->type = SPHERE;
    obj->id = get_shape_id();
    trans = matrix_translation(-0.5f, 1.0f, 0.5f);
    set_transform(obj, &trans);
    obj->material = new_material(0.0f, 0.0f, 1.0f, 500.0f, 1.0f, pattern_default());
    obj->material.color = color_constructor(0.0f, 0.0f, 0.0f);

    // 5. Right Sphere (Semi-reflective colored ball)
    obj = &world.objects[world.object_count++];
    obj->type = SPHERE;
    obj->id = get_shape_id();
    trans = matrix_translation(1.5f, 0.5f, -0.5f);
    scale = matrix_scale(0.5f, 0.5f, 0.5f);
    combo = matrix_multiply(&trans, &scale); // Passing by reference
    set_transform(obj, &combo);
    obj->material = new_material(0.1f, 0.5f, 1.0f, 300.0f, 0.5f, pattern_default());
    obj->material.color = color_constructor(0.1f, 0.1f, 0.8f); // Dark Blue

    // 6. Left Sphere (Matte, non-reflective)
    obj = &world.objects[world.object_count++];
    obj->type = SPHERE;
    obj->id = get_shape_id();
    trans = matrix_translation(-1.5f, 0.33f, -0.75f);
    scale = matrix_scale(0.33f, 0.33f, 0.33f);
    combo = matrix_multiply(&trans, &scale); // Passing by reference
    set_transform(obj, &combo);
    obj->material = new_material(0.1f, 0.9f, 0.1f, 10.0f, 0.0f, pattern_default());
    obj->material.color = color_constructor(1.0f, 0.2f, 0.1f); // Bright Red

    // 7. Setup Camera
    // Looking from slightly above and back, down at the middle sphere.
    // Note: Passed 60.0 instead of M_PI / 3.0 because camera_constructor now expects degrees.
    camera = camera_constructor(800, 600, 60.0f); 
    camera.transform = view_transform(
        point_constructor(0.0f, 1.5f, -5.0f), // Camera Position
        point_constructor(0.0f, 1.0f, 0.0f),  // Looking at
        vector_constructor(0.0f, 1.0f, 0.0f)  // Up vector
    );

    // 8. Render
    printf("Rendering scene...\n");
    // Passing pointers to camera and world based on our performance refactoring
    canvas = render(canvas.mlx, &camera, &world); 

    // 9. Display
    win = mlx_new_window(canvas.mlx, canvas.width, canvas.height, "Reflection Sandbox");
    canvas.win = win; // Link window to canvas for safe cleanup
    mlx_put_image_to_window(canvas.mlx, win, canvas.img.img, 0, 0);
    
    // Updated to match the new MLX keyhook signatures from earlier
    mlx_hook(win, 2, 1L << 0, handle_keypress, &canvas);
    mlx_hook(win, 17, 0L, close_program, &canvas);
    
    printf("Done! Press ESC to exit.\n");
    mlx_loop(canvas.mlx);
    
    return (0);
}
