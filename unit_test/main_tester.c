#include "mlx.h"
#include "vector.h"
#include "canvas.h"
#include "ray.h"

// Helper to get pixel from canvas
t_uint	get_pixel(t_canvas *c, int x, int y)
{
	char	*dest;

	dest = c->img.addr + (y * c->img.line_len + x * (c->img.bpp / 8));
	return (*(t_uint *)dest);
}

// Helper function to print vectors
static
void	print_vector(const char *name, t_vec3 v)
{
	printf("%s: (%.3f, %.3f, %.3f, w=%.3f)\n", name, v.x, v.y, v.z, v.w);
}

// Helper function to check if two vectors are equal within epsilon
static
bool	vectors_equal(t_vec3 a, t_vec3 b, double epsilon)
{
	return (fabs(a.x - b.x) < epsilon && 
			fabs(a.y - b.y) < epsilon && 
			fabs(a.z - b.z) < epsilon && 
			fabs(a.w - b.w) < epsilon);
}

// Helper function to check if two doubles are equal within epsilon
static
bool	doubles_equal(double a, double b, double epsilon)
{
	return fabs(a - b) < epsilon;
}

static
void	addition_tester(const double epsilon)
{
	t_vec3	add_a = point_constructor(3.0, -2.0, 5.0);
	t_vec3	add_b = vector_constructor(-2.0, 3.0, 1.0);
	t_vec3	add_result = vector_add(add_a, add_b);
	
	print_vector("Addend A", add_a);
	print_vector("Addend B", add_b);
	print_vector("A + B", add_result);
	
	t_vec3	expected = point_constructor(1.0, 1.0, 6.0);
	if (vectors_equal(expected, add_result, epsilon))
		printf("✓ Addition test passed\n\n");
	else
		printf("✗ Addition test failed\n\n");
}

static
void	subtraction_tester(const double epsilon)
{
	t_vec3 sub_a = point_constructor(3.0, 2.0, 1.0);
	t_vec3 sub_b = point_constructor(5.0, 6.0, 7.0);
	t_vec3 sub_result = vector_sub(sub_a, sub_b);
	
	print_vector("Element A", sub_a);
	print_vector("Element B", sub_b);
	print_vector("A - B", sub_result);
	
	t_vec3	expected = vector_constructor(-2.0, -4.0, -6.0);
	if (vectors_equal(expected, sub_result, epsilon))
		printf("✓ Subtraction test passed\n\n");
	else
		printf("✗ Subtraction test failed\n\n");
}

/* COLOR TESTS */
void	test_color_constructor(const double epsilon)
{
	t_vec3	color = color_constructor(-0.5, 0.4, 1.7);
	t_vec3	expected = {
		.x = -0.5,
		.y = 0.4,
		.z = 1.7,
		.w = 2.0
	};

	print_vector("color", color);

	if (vectors_equal(expected, color, epsilon))
		printf("✓ Color construction test passed\n\n");
	else
		printf("✗ Color construction test failed\n\n");
}

void	test_color_add(const double epsilon)
{
	t_vec3	u = color_constructor(0.9, 0.6, 0.75);
	t_vec3	v = color_constructor(0.7, 0.1, 0.25);

	t_vec3	expected = {
		.x = 1.6,
		.y = 0.7,
		.z = 1.0,
		.w = 2.0
	};

	t_vec3	color = color_add(u, v);
	print_vector("color", color);
	if (vectors_equal(expected, color, epsilon))
		printf("✓ Color addition test passed\n\n");
	else
		printf("✗ Color addition test failed\n\n");

}

void	test_color_subtract(const double epsilon)
{
	t_vec3	u = color_constructor(0.9, 0.6, 0.75);
	t_vec3	v = color_constructor(0.7, 0.1, 0.25);

	t_vec3	expected = {
		.x = 0.2,
		.y = 0.5,
		.z = 0.5,
		.w = 2.0
	};

	t_vec3	color = color_subtract(u, v);
	print_vector("color", color);
	if (vectors_equal(expected, color, epsilon))
		printf("✓ Color subtraction test passed\n\n");
	else
		printf("✗ Color subtraction test failed\n\n");

}

void	test_color_scalar(const double epsilon)
{
	t_vec3	u = color_constructor(0.2, 0.3, 0.4);
	double	scalar = 2.0;

	t_vec3	expected = {
		.x = 0.4,
		.y = 0.6,
		.z = 0.8,
		.w = 2.0
	};

	t_vec3	color = color_scalar(u, scalar);
	print_vector("color", color);
	if (vectors_equal(expected, color, epsilon))
		printf("✓ Color multiplying by a scale test passed\n\n");
	else
		printf("✗ Color multiplying by a scale test failed\n\n");

}

void	test_color_multiply(const double epsilon)
{
	t_vec3	u = color_constructor(1.0, 0.2, 0.4);
	t_vec3	v = color_constructor(0.9, 1.0, 0.1);

	t_vec3	expected = {
		.x = 0.9,
		.y = 0.2,
		.z = 0.04,
		.w = 2.0
	};

	t_vec3	color = color_multiply(u, v);
	print_vector("color", color);
	if (vectors_equal(expected, color, epsilon))
		printf("✓ Color multiplying test passed\n\n");
	else
		printf("✗ Color multiplying test failed\n\n");

}

void	test_color_to_int(void)
{
	int		expected = 0x9eeb34;
	t_vec3	color = color_constructor(0.61960784313, 0.92156862745, 0.20392156862);

	int	result = color_to_int(color);
	printf("color = %d\n", result);
	if (expected == result)
		printf("✓ Color conversion test passed\n\n");
	else
		printf("✗ Color conversion test failed\n\n");
}

void	test_canvas_constructor(double epsilon)
{
	t_canvas	expected_canvas = {
		.width = 10,
		.height = 20,
		.bg_color = {
			.x = 0.0,
			.y = 0.0,
			.z = 0.0,
			.w = 2.0
		},
	};
	t_canvas	canvas;

	if (canvas_constructor(10, 20, &canvas) == false)
	{
		printf("✗ Canvas construction test failed (returned false)\n\n");
		return ;
	}
	printf("width = %d\nheight = %d\n", canvas.width, canvas.height);
	print_vector("bg_color", canvas.bg_color)	;
	if (canvas.width == expected_canvas.width
	 	&& canvas.height == expected_canvas.height
	 	&& vectors_equal(canvas.bg_color, expected_canvas.bg_color, epsilon))
		printf("✓ Canvas construction test passed\n\n");
	else
		printf("✗ Canvas construction test failed\n\n");
}

void	test_write_pixel(void)
{
	t_canvas	canvas;
	t_vec3		red = color_constructor(1.0, 0, 0);
	t_uint		expected = 0xff0000;
	t_uint		pixel;

	if (canvas_constructor(10, 20, &canvas) == false)
	{
		printf("✗ Writing to canvas test failed (returned false)\n\n");
		return ;
	}
	write_pixel(&canvas, 2, 3, red);
	pixel = get_pixel(&canvas, 2, 3);
	printf("Pixel at x = 2, y = 3 -> %d\n", pixel);
	if (pixel == expected)
		printf("✓ Writing to canvas test passed\n\n");
	else
		printf("✗ Writing to canvas test failed\n\n");
}

// =================================== TEST PROJECTILES ===================================
struct s_projectile
{
	t_vec3	position;
	t_vec3	velocity;
};

struct s_environment
{
	t_vec3	gravity;
	t_vec3	wind;
};

struct s_projectile tick(struct s_projectile proj, struct s_environment env)
{
	t_vec3	position;
	t_vec3	velocity;

	position = vector_add(proj.position, proj.velocity);
	velocity = vector_add(proj.velocity, vector_add(env.gravity, env.wind));
	struct s_projectile projectile = {
			.velocity = velocity,
			.position = position,
	};
	return (projectile);
}

void	test_window_opening(void)
{
	t_canvas	c;
	t_vec3		red = color_constructor(1.0, 0, 0);

	if (canvas_constructor(1000, 1000, &c) == false)
	{
		printf("✗ canvas construction failed (returned false)\n\n");
		return ;
	}
	struct s_projectile proj = {
		.position = point_constructor(0, 1.0, 0),
		.velocity = vector_scale(vector_normalization(vector_constructor(2.0, 1.8, 0)), 11.25),
	};
	struct s_environment env = {
		.gravity = vector_constructor(0, -0.1, 0),
		.wind = vector_constructor(-0.01, 0, 0),
	};
	struct s_projectile p = proj;
	while (p.position.y > 0)
	{
		int x = (int)p.position.x;
		int y = c.height - (int)p.position.y;
		
		write_pixel(&c, x, y, red);
		p = tick(p, env);
	}
	void	*win = mlx_new_window(c.mlx, c.width, c.height, "Tester");
	mlx_put_image_to_window(c.mlx, win, c.img.img, 0, 0);
	mlx_loop(c.mlx);
}

void	test_ray_constructor(const double epsilon)
{
	t_vec3	origin = point_constructor(1, 2, 3);
	t_vec3	direction = vector_constructor(4, 5, 6);
	t_ray	r = ray_constructor(origin, direction);

	print_vector("r.origin", r.origin);
	print_vector("r.direction", r.direction);
	if (vectors_equal(r.origin, origin, epsilon)
		&& vectors_equal(r.direction, direction, epsilon))
		printf("✓ Ray construction test passed\n\n");
	else
		printf("✗ Ray construction test failed\n\n");
}

void	test_ray_position(const double epsilon)
{
	t_vec3	origin = point_constructor(2, 3, 4);
	t_vec3	direction = vector_constructor(1, 0, 0);
	t_ray	r = ray_constructor(origin, direction);

	t_vec3	expected1 = {
		.x = 2,
		.y = 3,
		.z = 4,
		.w = 1
	};
	t_vec3	expected2 = {
		.x = 3,
		.y = 3,
		.z = 4,
		.w = 1
	};
	t_vec3	expected3 = {
		.x = 1,
		.y = 3,
		.z = 4,
		.w = 1
	};
	t_vec3	expected4 = {
		.x = 4.5,
		.y = 3,
		.z = 4,
		.w = 1
	};
	t_vec3	p1 = ray_position(r, 0);
	t_vec3	p2 = ray_position(r, 1);
	t_vec3	p3 = ray_position(r, -1);
	t_vec3	p4 = ray_position(r, 2.5);
	print_vector("p1", p1);
	print_vector("p2", p2);
	print_vector("p3", p3);
	print_vector("p4", p4);
	if (vectors_equal(p1, expected1, epsilon)
		&& vectors_equal(p2, expected2, epsilon)
		&& vectors_equal(p3, expected3, epsilon)
		&& vectors_equal(p4, expected4, epsilon))
		printf("✓ Ray position computing test passed\n\n");
	else
		printf("✗ Ray position computing test failed\n\n");
}

int	test_sphere_intersect(t_ray r, int ex_count, double ex_t0, double ex_t1)
{
	t_sphere	s = sphere();
	t_intersect	xs = sphere_intersect(r, s);

	printf("xs.count == %d, expected %d\n", xs.count, ex_count);
	if (ex_count != 0)
	{
		printf("xs.t[0] == %f, expected %f\n", xs.t[0], ex_t0);
		printf("xs.t[1]	== %f, expected %f\n", xs.t[1], ex_t1);
	}

	if ((xs.count == ex_count
		&& xs.t[0] == ex_t0
		&& xs.t[1] == ex_t1)
		|| (xs.count == 0 && ex_count == 0))
		return (0);
	else
		return(1);
}

void	test_sphere_intersections(void)
{
	int t1 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 0, -5), vector_constructor(0, 0, 1)),
		2,
		4.0,
		6.0
	);
	int t2 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 1, -5), vector_constructor(0, 0, 1)),
		2,
		5.0,
		5.0
	);
	int t3 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 2, -5), vector_constructor(0, 0, 1)),
		0,
		0,
		0
	);
	int t4 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 0, 0), vector_constructor(0, 0, 1)),
		2,
		-1,
		1
	);
	int t5 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 0, 5), vector_constructor(0, 0, 1)),
		2,
		-6.0,
		-4.0
	);
	if (t1 == 0
		&& t2 == 0
		&& t3 == 0
		&& t4 == 0
		&& t5 == 0)
		printf("✓ Sphere intersections test passed\n\n");
	else
		printf("✗ Sphere intersections test failed\n\n");
}

int	main(void)
{
	const double EPSILON = 1e-10;
	printf("=== Vector Library Test Suite for Ray Tracing Engine ===\n\n");
	
	// Test 1: Constructor functions
	printf("1. Testing Constructor Functions:\n");
	t_vec3 point = point_constructor(1.0, 2.0, 3.0);
	t_vec3 vector = vector_constructor(4.0, 5.0, 6.0);
	
	print_vector("Point", point);
	print_vector("Vector", vector);
	
	if (point.w == 1.0 && vector.w == 0.0)
	    printf("✓ Constructor tests passed\n\n");
	else
	    printf("✗ Constructor tests failed\n\n");
	
	// Test 2: Length functions
	printf("2. Testing Length Functions:\n");
	t_vec3 unit_x = vector_constructor(1.0, 0.0, 0.0);
	t_vec3 test_vec = vector_constructor(3.0, 4.0, 0.0);
	
	print_vector("Unit X vector", unit_x);
	print_vector("Test vector (3,4,0)", test_vec);
	
	double len_sq = vector_length_squared(test_vec);
	double len = vector_length(test_vec);
	
	printf("Length squared: %.3f (expected: 25.0)\n", len_sq);
	printf("Length: %.3f (expected: 5.0)\n", len);
	
	if (doubles_equal(len_sq, 25.0, EPSILON) && doubles_equal(len, 5.0, EPSILON))
	    printf("✓ Length tests passed\n\n");
	else
	    printf("✗ Length tests failed\n\n");
	
	// Test 3: Normalization
	printf("3. Testing Normalization:\n");
	t_vec3 vec_to_normalize = vector_constructor(6.0, 8.0, 0.0);
	t_vec3 normalized = vector_normalization(vec_to_normalize);
	
	print_vector("Original vector", vec_to_normalize);
	print_vector("Normalized vector", normalized);
	
	double normalized_len = vector_length(normalized);
	printf("Length of normalized vector: %.6f (should be 1.0)\n", normalized_len);
	
	if (doubles_equal(normalized_len, 1.0, EPSILON))
	    printf("✓ Normalization test passed\n\n");
	else
	    printf("✗ Normalization test failed\n\n");
	
	// Test 4: Dot Product
	printf("4. Testing Dot Product:\n");
	t_vec3 a = vector_constructor(1.0, 2.0, 3.0);
	t_vec3 b = vector_constructor(4.0, 5.0, 6.0);
	t_vec3 c = vector_constructor(1.0, 0.0, 0.0); // Unit x
	t_vec3 d = vector_constructor(0.0, 1.0, 0.0); // Unit y
	
	print_vector("Vector A", a);
	print_vector("Vector B", b);
	print_vector("Unit X", c);
	print_vector("Unit Y", d);
	
	double dot_ab = vector_dot_product(a, b);
	double dot_xy = vector_dot_product(c, d);
	
	printf("Dot product A·B: %.3f (expected: 32.0)\n", dot_ab);
	printf("Dot product X·Y: %.3f (expected: 0.0)\n", dot_xy);
	
	if (doubles_equal(dot_ab, 32.0, EPSILON) && doubles_equal(dot_xy, 0.0, EPSILON))
		printf("✓ Dot product tests passed\n\n");
	else
		printf("✗ Dot product tests failed\n\n");
	
	// Test 5: Cross Product
	printf("5. Testing Cross Product:\n");
	t_vec3 i = vector_constructor(1.0, 0.0, 0.0); // Unit x
	t_vec3 j = vector_constructor(0.0, 1.0, 0.0); // Unit y
	t_vec3 k = vector_constructor(0.0, 0.0, 1.0); // Unit z
	
	print_vector("Unit X (i)", i);
	print_vector("Unit Y (j)", j);
	print_vector("Unit Z (k)", k);
	
	t_vec3 cross_ij = vector_cross_product(i, j);
	t_vec3 cross_jk = vector_cross_product(j, k);
	t_vec3 cross_ki = vector_cross_product(k, i);
	
	print_vector("i × j", cross_ij);
	print_vector("j × k", cross_jk);
	print_vector("k × i", cross_ki);
	
	bool cross_correct = vectors_equal(cross_ij, k, EPSILON) && 
						vectors_equal(cross_jk, i, EPSILON) && 
						vectors_equal(cross_ki, j, EPSILON);
	
	if (cross_correct)
		printf("✓ Cross product tests passed\n\n");
	else
		printf("✗ Cross product tests failed\n\n");
	
	// Test 6: Vector Addition
	printf("6. Testing Vector Addition:\n");
	addition_tester(EPSILON);

	// Test 7: Vector Subtraction
	printf("7. Testing Vector Subtraction:\n");
	subtraction_tester(EPSILON);
	
	// Test 8: Vector Scaling
	printf("8. Testing Vector Scaling:\n");
	t_vec3 scale_vec = vector_constructor(2.0, 3.0, 4.0);
	t_vec3 scaled = vector_scale(scale_vec, 2.5);
	
	print_vector("Original vector", scale_vec);
	print_vector("Scaled by 2.5", scaled);
	
	t_vec3 expected_scaled = vector_constructor(5.0, 7.5, 10.0);
	if (vectors_equal(scaled, expected_scaled, EPSILON))
	    printf("✓ Scaling test passed\n\n");
	else
	    printf("✗ Scaling test failed\n\n");
	
	// Test 9: Array access (union functionality)
	printf("9. Testing Array Access:\n");
	t_vec3 array_test = vector_constructor(10.0, 20.0, 30.0);
	printf("Vector via named fields: (%.1f, %.1f, %.1f)\n", array_test.x, array_test.y, array_test.z);
	printf("Vector via array access: (%.1f, %.1f, %.1f)\n", array_test.v[0], array_test.v[1], array_test.v[2]);
	
	bool array_access_works = (array_test.x == array_test.v[0]) && 
							(array_test.y == array_test.v[1]) && 
							(array_test.z == array_test.v[2]);
	
	if (array_access_works)
	    printf("✓ Array access test passed\n\n");
	else
	    printf("✗ Array access test failed\n\n");
	
	// Test 10: Edge cases
	printf("10. Testing Edge Cases:\n");
	t_vec3 zero_vec = vector_constructor(0.0, 0.0, 0.0);
	t_vec3 zero_normalized = vector_normalization(zero_vec);
	
	print_vector("Zero vector", zero_vec);
	print_vector("Normalized zero vector", zero_normalized);
	
	bool zero_test = (zero_normalized.x == 0.0 && zero_normalized.y == 0.0 && 
	                  zero_normalized.z == 0.0 && zero_normalized.w == 0.0);
	
	if (zero_test)
	    printf("✓ Edge case tests passed\n\n");
	else
	    printf("✗ Edge case tests failed\n\n");

	printf("11. Testing color contruction:\n");
	test_color_constructor(EPSILON);
	
	printf("12. Testing color addition:\n");
	test_color_add(EPSILON);

	printf("13. Testing color addition:\n");
	test_color_subtract(EPSILON);

	printf("14. Testing color multiplying by a scale:\n");
	test_color_scalar(EPSILON);

	printf("15. Testing color multiplying:\n");
	test_color_multiply(EPSILON);

	printf("16. Testing color conversion:\n");
	test_color_to_int();

	printf("17. Testing canvas construction:\n");
	test_canvas_constructor(EPSILON);

	printf("18. Testing writing to canvas:\n");
	test_write_pixel();

	printf("19. Testing ray construction:\n");
	test_ray_constructor(EPSILON);

	printf("20. Testing compution point from a distance:\n");
	test_ray_position(EPSILON);

	printf("20. Testing sphere intersections:\n");
	test_sphere_intersections();

	//printf("19. Testing window opening:\n");
	//test_window_opening();

	printf("=== Test Suite Complete ===\n");

	return (0);
}
