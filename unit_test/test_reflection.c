#include "vector.h"
#include "matrix.h"
#include "shades.h"
#include "librt.h"
#include "ray.h"
#include "scene.h"
#include <mlx.h> // Ensure MLX is explicitly included
#include <stdio.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

int main(void)
{
    t_world     world;
    t_camera    camera;
    t_canvas    canvas;
    void        *mlx;
    t_object    *obj;
    t_mat4      ident, trans, scale, rot, combo;
    t_pattern   pat;

    // --- 0. CRITICAL FIX: Initialize MLX FIRST ---
    mlx = mlx_init();
    if (!mlx)
    {
        printf("Error: MLX failed to initialize.\n");
        return (1);
    }

    world.object_count = 0;
    
    world.a_light.ratio = 0.1f;
    world.a_light.color = color_constructor(1.0f, 1.0f, 1.0f);
    
    world.light.position = point_constructor(-10.0f, 10.0f, -10.0f);
    world.light.color = color_constructor(1.0f, 1.0f, 1.0f);
    world.light.brightness = 1.0f;

    matrix_identity(&ident);

    // --- 1. The Floor (Checkerboard) ---
    obj = &world.objects[world.object_count++];
    obj->type = PLANE;
    obj->id = get_shape_id();
    set_transform(obj, &ident);
    
    // Create checkers and scale them down so they repeat
    pat = pattern_constructor(PATTERN_CHECKER, color_constructor(0.8f, 0.8f, 0.8f), color_constructor(0.2f, 0.2f, 0.2f));
    pat.transform = matrix_scale(0.25f, 0.25f, 0.25f);
    pat.transform_inv = matrix_inverse(&pat.transform);
    
    // Give it a slightly glossy finish
    obj->material = material_default();
    obj->material.ambient = 0.1f;
    obj->material.diffuse = 0.7f;
    obj->material.specular = 0.3f;
    obj->material.shininess = 200.0f;
    obj->material.reflective = 0.2f;
    obj->material.pattern = pat;

    // --- 2. Middle Sphere (Diagonal Stripes & Semi-Reflective) ---
    obj = &world.objects[world.object_count++];
    obj->type = SPHERE;
    obj->id = get_shape_id();
    trans = matrix_translation(-0.5f, 1.0f, 0.5f);
    set_transform(obj, &trans);
    
    pat = pattern_constructor(PATTERN_STRIPE, color_constructor(0.2f, 0.3f, 0.6f), color_constructor(0.8f, 0.9f, 0.2f));
    // Scale the stripes down, then rotate them diagonally
    scale = matrix_scale(0.2f, 0.2f, 0.2f);
    rot = matrix_rot_z(M_PI / 4.0f); // 45 degrees
    pat.transform = matrix_multiply(&rot, &scale);
    pat.transform_inv = matrix_inverse(&pat.transform);
    
    // Mix diffuse and reflective so we see both the pattern and the reflection
    obj->material = material_default();
    obj->material.ambient = 0.1f;
    obj->material.diffuse = 0.5f;
    obj->material.specular = 0.9f;
    obj->material.shininess = 300.0f;
    obj->material.reflective = 0.5f;
    obj->material.pattern = pat;

    // --- 3. Right Sphere (Smooth Gradient) ---
    obj = &world.objects[world.object_count++];
    obj->type = SPHERE;
    obj->id = get_shape_id();
    trans = matrix_translation(1.5f, 0.5f, -0.5f);
    scale = matrix_scale(0.5f, 0.5f, 0.5f);
    combo = matrix_multiply(&trans, &scale);
    set_transform(obj, &combo);
    
    // Gradients interpolate between color A and B based on the X coordinate
    pat = pattern_constructor(PATTERN_GRADIENT, color_constructor(1.0f, 0.0f, 0.0f), color_constructor(0.0f, 0.0f, 1.0f));
    // Translate the pattern slightly so the gradient blends beautifully across the sphere's surface
    pat.transform = matrix_translation(1.0f, 0.0f, 0.0f);
    pat.transform_inv = matrix_inverse(&pat.transform);
    
    obj->material = material_default();
    obj->material.ambient = 0.1f;
    obj->material.diffuse = 0.7f;
    obj->material.specular = 0.3f;
    obj->material.shininess = 200.0f;
    obj->material.reflective = 0.1f;
    obj->material.pattern = pat;

    // --- 4. Left Sphere (Bullseye Rings) ---
    obj = &world.objects[world.object_count++];
    obj->type = SPHERE;
    obj->id = get_shape_id();
    trans = matrix_translation(-1.5f, 0.33f, -0.75f);
    scale = matrix_scale(0.33f, 0.33f, 0.33f);
    combo = matrix_multiply(&trans, &scale);
    set_transform(obj, &combo);
    
    pat = pattern_constructor(PATTERN_RING, color_constructor(1.0f, 0.2f, 0.1f), color_constructor(1.0f, 1.0f, 1.0f));
    // Scale rings down to create a tight bullseye
    pat.transform = matrix_scale(0.2f, 0.2f, 0.2f);
    pat.transform_inv = matrix_inverse(&pat.transform);
    
    obj->material = material_default();
    obj->material.ambient = 0.1f;
    obj->material.diffuse = 0.9f;
    obj->material.specular = 0.1f;
    obj->material.shininess = 10.0f;
    obj->material.reflective = 0.0f;
    obj->material.pattern = pat;

    // --- 5. Setup Camera ---
    camera = camera_constructor(800, 600, 60.0f); 
    camera.transform = view_transform(
        point_constructor(0.0f, 1.5f, -5.0f), 
        point_constructor(0.0f, 1.0f, 0.0f),  
        vector_constructor(0.0f, 1.0f, 0.0f)  
    );

    // --- 6. Render ---
    printf("Rendering scene...\n");
    canvas.mlx = mlx;
    render(&canvas, &camera, &world);

    // --- 7. Display ---
    canvas.win = mlx_new_window(mlx, canvas.width, canvas.height, "Patterns Sandbox");
    mlx_put_image_to_window(mlx, canvas.win, canvas.img.img, 0, 0);
    
    mlx_hook(canvas.win, 2, 1L << 0, key_hook, &canvas);
    mlx_hook(canvas.win, 17, 0L, close_program, &canvas);
    
    printf("Done! Press ESC to exit.\n");
    mlx_loop(mlx);
    
    return (0);
}
