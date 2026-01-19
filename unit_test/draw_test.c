#include "librt.h"
#include <unistd.h>

# define WIDTH 980
# define HEIGHT 720

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
