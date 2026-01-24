/*
int	main(void)
{
	t_vec3		ray_origin = point_constructor(0, 0, -5);
	float		wall_dist = 10.0f;
	float		wall_size = 7.0f;
	int			pxs = 980;
	float		pixel_size = wall_size / pxs;
	float		half = wall_size / 2.0f;

	t_sphere	s = sphere();
	t_vec3		color = color_constructor(1.0f, 0.0f, 0.0f);

	t_canvas	canvas;
	void		*win;
	if (!canvas_constructor(pxs, pxs, &canvas))
	{
		fprintf(stderr, "Error initializing mlx\n");
		return (1);
	}
	win = mlx_new_window(canvas.mlx, canvas.width, canvas.height, "MiniRT Sphere Shadow");

	// 4. RENDERING LOOP
	int y = 0;
	while (y < pxs)
	{
		// Compute world y coordinate (Top = +half, Bottom = -half)
		float world_y = half - pixel_size * y;
		
		int x = 0;
		while (x < pxs)
		{
			// Compute world x coordinate (Left = -half, Right = +half)
			float world_x = -half + pixel_size * x;

			// Describe the point on the wall the ray targets
			t_vec3 position = point_constructor(world_x, world_y, wall_dist);

			// Create Ray: Origin -> (Position - Origin) normalized
			t_vec3 direction = vector_sub(position, ray_origin);
			direction = vector_normalization(direction);
			t_ray r = ray_constructor(ray_origin, direction);

			// Check Intersection
			t_intersect xs = sphere_intersect(r, s);
			
			// Hit Check
			t_intersection closest_hit_buffer;
			t_intersection *hit_record = hit(&xs, &closest_hit_buffer, xs.count);

			if (hit_record != NULL)
			{
				write_pixel(&canvas, x, y, color);
			}
			x++;
		}
		y++;
	}

	// 5. DISPLAY AND EVENTS
	mlx_put_image_to_window(canvas.mlx, win, canvas.img.img, 0, 0);
	
	// Hook events to close window properly
	mlx_key_hook(win, key_hook, &canvas);         // ESC key
	
	mlx_loop(canvas.mlx);
	return (0);
}
*/
#include <stdio.h>
#include "canvas.h"
#include "ray.h"
#include "matrix.h"
#include "shades.h"
#include "librt.h"

int	close_program(t_canvas *vars)
{
	canvas_destructor(vars);
	exit(0);
	return (0);
}

int	main(void)
{
	// 1. SCENE CONFIGURATION
	t_vec3		ray_origin = point_constructor(0, 0, -15);
	float		wall_z = 10.0f;
	float		wall_size = 7.0f;
	int			canvas_pixels = 980; // Increased resolution
	float		pixel_size = wall_size / canvas_pixels;
	float		half = wall_size / 2.0f;

	// 2. OBJECT SETUP (Sphere + Material)
	t_sphere	shape = sphere();
	
	// Assign Material
	shape.material = new_material();
	shape.material.color = color_constructor(0.0f, 0.2f, 1.0f);

	// 3. LIGHT SETUP
	t_vec3			light_position = point_constructor(-10, 10, -10);
	t_vec3			light_color = color_constructor(1, 0.75, 0.4);
	t_point_light	light = point_light(light_position, light_color);

	// 4. CANVAS INIT
	t_canvas	canvas;
	void		*win;

	if (!canvas_constructor(canvas_pixels, canvas_pixels, &canvas))
	{
		fprintf(stderr, "Error initializing mlx\n");
		return (1);
	}
	win = mlx_new_window(canvas.mlx, canvas.width, canvas.height, "MiniRT - Shaded Sphere");

	// 5. RENDERING LOOP
	int y = 0;
	while (y < canvas_pixels)
	{
		float world_y = half - pixel_size * y;
		int x = 0;
		while (x < canvas_pixels)
		{
			float world_x = -half + pixel_size * x;
			t_vec3 position = point_constructor(world_x, world_y, wall_z);

// 1. Cast Ray
            t_vec3 direction = vector_normalization(vector_sub(position, ray_origin));
            t_ray r = ray_constructor(ray_origin, direction);

            // 2. Intersect (Fixing the error here)
            // Old: int count = sphere_intersect(r, shape);
            // New: Store the full struct returned by the team's function
            t_intersect xs = sphere_intersect(r, shape);
            
            // 3. Find closest hit using the team's hit() function
            t_intersection closest_buffer;
            t_intersection *hit_record = hit(&xs, &closest_buffer, xs.count);

            if (hit_record != NULL)
            {
                // Calculate point, normal, eye, and lighting
                t_vec3 point = ray_position(r, hit_record->t);
                t_vec3 normal = normal_at(shape, point);
                t_vec3 eye = vector_scale(r.direction, -1.0f);
                
                t_vec3 color = lighting(shape.material, light, point, eye, normal);
                
                write_pixel(&canvas, x, y, color);
            }
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(canvas.mlx, win, canvas.img.img, 0, 0);
	mlx_hook(win, 17, 0, close_program, &canvas);
	mlx_key_hook(win, key_hook, &canvas);
	mlx_loop(canvas.mlx);
	return (0);
}
