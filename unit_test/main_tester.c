#include "mlx.h"
#include "vector.h"
#include "canvas.h"
#include "matrix.h"
#include "ray.h"

// Helper to get pixel from canvas
t_uint	get_pixel(t_canvas *c, int x, int y)
{
	char	*dest;

	dest = c->img.addr + (y * c->img.line_len + x * (c->img.bpp / 8));
	return (*(t_uint *)dest);
}

/* *********************************************************************** */
/*                             HELPER FUNCTIONS                            */
/* *********************************************************************** */

// Helper function to print vectors
static
void	print_vector(const char *name, t_vec3 v)
{
	printf("%s: (%.3f, %.3f, %.3f, w=%.3f)\n", name, v.x, v.y, v.z, v.w);
}

/*
// Helper function to print matrix
static
void	print_matrix(const char *name, double *matrix, int size)
{
	int	i;
	int	j;

	printf("%s:\n", name);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%.3f ", matrix[i * size + j]);
			j++;
		}
		i++;
		printf("\n");
	}
}
*/

// Helper function to check if two vectors are equal within epsilon
static
bool	vectors_equal(t_vec3 a, t_vec3 b, double epsilon)
{
	return (fabs(a.x - b.x) < epsilon && 
			fabs(a.y - b.y) < epsilon && 
			fabs(a.z - b.z) < epsilon && 
			fabs(a.w - b.w) < epsilon);
}

/*
// Helper function to check if two doubles are equal within epsilon
static
bool	doubles_equal(double a, double b, double epsilon)
{
	return fabs(a - b) < epsilon;
}

// Helper function to check if two matrices are equal within epsilon
static
bool	matrices_equal(double *a, double *b, int size, double epsilon)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!doubles_equal(a[i], b[i], epsilon))
			return (false);
		i++;
	}
	return (true);
}
*/

/* *********************************************************************** */
/*                             VECOTR TESTS                                */
/* *********************************************************************** */

/*
static
void	test_vector_point_constructor(void)
{
	t_vec3 point = point_constructor(1.0, 2.0, 3.0);
	t_vec3 vector = vector_constructor(4.0, 5.0, 6.0);
	
	print_vector("Point", point);
	print_vector("Vector", vector);
	
	if (point.w == 1.0 && vector.w == 0.0)
		printf("✓ Constructor tests passed\n\n");
	else
		printf("✗ Constructor tests failed\n\n");
}

static
void	test_vector_length(const double epsilon)
{
	t_vec3 unit_x = vector_constructor(1.0, 0.0, 0.0);
	t_vec3 test_vec = vector_constructor(3.0, 4.0, 0.0);
	
	print_vector("Unit X vector", unit_x);
	print_vector("Test vector (3,4,0)", test_vec);
	
	double len_sq = vector_length_squared(test_vec);
	double len = vector_length(test_vec);
	
	printf("Length squared: %.3f (expected: 25.0)\n", len_sq);
	printf("Length: %.3f (expected: 5.0)\n", len);
	
	if (doubles_equal(len_sq, 25.0, epsilon) && doubles_equal(len, 5.0, epsilon))
		printf("✓ Length tests passed\n\n");
	else
		printf("✗ Length tests failed\n\n");
}

static
void	test_vector_normalization(const double epsilon)
{
	t_vec3 vec_to_normalize = vector_constructor(6.0, 8.0, 0.0);
	t_vec3 normalized = vector_normalization(vec_to_normalize);
	
	print_vector("Original vector", vec_to_normalize);
	print_vector("Normalized vector", normalized);
	
	double normalized_len = vector_length(normalized);
	printf("Length of normalized vector: %.6f (should be 1.0)\n", normalized_len);
	
	if (doubles_equal(normalized_len, 1.0, epsilon))
		printf("✓ Normalization test passed\n\n");
	else
		printf("✗ Normalization test failed\n\n");
}

static
void	test_dot_product(const double epsilon)
{
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
	
	if (doubles_equal(dot_ab, 32.0, epsilon) && doubles_equal(dot_xy, 0.0, epsilon))
		printf("✓ Dot product tests passed\n\n");
	else
		printf("✗ Dot product tests failed\n\n");
}

static
void	test_cross_product(const double epsilon)
{
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
	
	bool cross_correct = vectors_equal(cross_ij, k, epsilon) && 
						vectors_equal(cross_jk, i, epsilon) && 
						vectors_equal(cross_ki, j, epsilon);
	
	if (cross_correct)
		printf("✓ Cross product tests passed\n\n");
	else
		printf("✗ Cross product tests failed\n\n");
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

static
void	test_vector_scaling(const double epsilon)
{
	t_vec3 scale_vec = vector_constructor(2.0, 3.0, 4.0);
	t_vec3 scaled = vector_scale(scale_vec, 2.5);
	
	print_vector("Original vector", scale_vec);
	print_vector("Scaled by 2.5", scaled);
	
	t_vec3 expected_scaled = vector_constructor(5.0, 7.5, 10.0);
	if (vectors_equal(scaled, expected_scaled, epsilon))
	    printf("✓ Scaling test passed\n\n");
	else
	    printf("✗ Scaling test failed\n\n");
}

static
void	test_array_access(void)
{
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
}

void	test_edge_cases()
{
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
}
*/

/* *********************************************************************** */
/*                             COLOR TESTS                                 */
/* *********************************************************************** */

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

/* *********************************************************************** */
/*                             MATRIX FUNCTIONS                            */
/* *********************************************************************** */

/*
static
void	test_identity_matrix_constructor(const double epsilon)
{
	double	matrix[16];
	bool	is_identity;

	is_identity = true;
	identity_matrix_constructor(matrix);
	print_matrix("Identity Matrix", matrix, 4);

	for (int i = 0; i < DIM4; i++)
	{
		for (int j = 0; j < DIM4; j++)
		{
			double	expected = (i == j) ? 1.0:0.0;
			if (!doubles_equal(matrix[i * DIM4 + j], expected, epsilon))
			{
				is_identity = false;
				break ;
			}
		}
		if (!is_identity) break;
	}
	if (is_identity)
		printf("✓ Identity matrix constructor test passed\n\n");
	else
		printf("✗ Identity matrix constructor test failed\n\n");
}

static
void	test_matrix_transpose(const double epsilon)
{
	double matrix[16] = {
		1.0, 2.0, 3.0, 4.0,
		5.0, 6.0, 7.0, 8.0,
		9.0, 10.0, 11.0, 12.0,
		13.0, 14.0, 15.0, 16.0
	};
	
	print_matrix("Original Matrix", matrix, 4);
	
	matrix_transpose(matrix);
	
	print_matrix("Transposed Matrix", matrix, 4);
	
	double expected[16] = {
		1.0, 5.0, 9.0, 13.0,
		2.0, 6.0, 10.0, 14.0,
		3.0, 7.0, 11.0, 15.0,
		4.0, 8.0, 12.0, 16.0
	};
	
	if (matrices_equal(matrix, expected, 4, epsilon))
		printf("✓ Matrix transpose test passed\n\n");
	else
		printf("✗ Matrix transpose test failed\n\n");
}

static
void	test_matrix_multiply(const double epsilon)
{
	double m1[16] = {
		1.0, 2.0, 3.0, 4.0,
		5.0, 6.0, 7.0, 8.0,
		9.0, 10.0, 11.0, 12.0,
		13.0, 14.0, 15.0, 16.0
	};
	
	double m2[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	
	double result[16];
	matrix_multiply(m1, m2, result);
	
	print_matrix("Matrix 1", m1, 4);
	print_matrix("Matrix 2 (Identity)", m2, 4);
	print_matrix("Result", result, 4);
	
	if (matrices_equal(result, m1, 4, epsilon))
		printf("✓ Matrix multiply test passed\n\n");
	else
		printf("✗ Matrix multiply test failed\n\n");
}

static
void	test_matrix_row_constructor(const double epsilon)
{
	double matrix[16] = {0}; // Initialize to zeros
	t_vec3 row_data = vector_constructor(1.0, 2.0, 3.0);
	
	matrix_row_constructor(matrix, row_data, 2); // Insert into row 2
	
	print_matrix("Matrix after inserting row", matrix, 4);
	
	bool row_inserted_correctly = true;
	for (int j = 0; j < 4; j++)
	{
		if (!doubles_equal(matrix[2 * 4 + j], row_data.v[j], epsilon))
		{
			row_inserted_correctly = false;
			break;
		}
	}
	
	// Check that other rows are still zeros
	for (int i = 0; i < 4; i++)
	{
		if (i != 2)
		{
			for (int j = 0; j < 4; j++)
			{
				if (!doubles_equal(matrix[i * 4 + j], 0.0, epsilon))
				{
					row_inserted_correctly = false;
					break;
				}
			}
		}
	}
	
	if (row_inserted_correctly)
		printf("✓ Matrix row constructor test passed\n\n");
	else
		printf("✗ Matrix row constructor test failed\n\n");
}

static
void	test_matrix_vector_multiply(const double epsilon)
{
	double matrix[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	
	t_vec3 input = point_constructor(1.0, 2.0, 3.0);
	t_vec3 result = matrix_vector_multiply(matrix, input);
	
	print_vector("Input vector", input);
	print_vector("Result vector", result);
	
	if (vectors_equal(input, result, epsilon))
		printf("✓ Matrix-vector multiply test passed\n\n");
	else
		printf("✗ Matrix-vector multiply test failed\n\n");
}

static
void	test_matrix_determinant_2x2(const double epsilon)
{
	double matrix[4] = {1.0, 2.0, 3.0, 4.0};
	double det = matrix_determinant_2x2(matrix);
	
	printf("2x2 Matrix:\n%.3f %.3f\n%.3f %.3f\n", matrix[0], matrix[1], matrix[2], matrix[3]);
	printf("Determinant: %.3f (expected: -2.0)\n", det);
	
	if (doubles_equal(det, -2.0, epsilon))
		printf("✓ 2x2 determinant test passed\n\n");
	else
		printf("✗ 2x2 determinant test failed\n\n");
}

static
void	test_matrix_determinant_3x3(const double epsilon)
{
	double matrix[9] = {1.0, 2.0, 3.0, 0.0, 1.0, 4.0, 5.0, 6.0, 0.0};
	double det = matrix_determinant_3x3(matrix);
	
	printf("3x3 Matrix:\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n",
		   matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7], matrix[8]);
	printf("Determinant: %.3f (expected: 1.0)\n", det);
	
	if (doubles_equal(det, 1.0, epsilon))
		printf("✓ 3x3 determinant test passed\n\n");
	else
		printf("✗ 3x3 determinant test failed\n\n");
}

static
void	test_submatrix_constructor_3x3(const double epsilon)
{
	double original[9] = {1.0, 5.0, 0.0, -3.0, 2.0, 7.0, 0.0, 6.0, -3.0};
	double result[4];
	
	submatrix_constructor_3x3(original, result, 0, 2);
	
	print_matrix("Original 3x3", original, 3);
	print_matrix("Submatrix (remove row 0, col 2)", result, 2);
	
	double expected[4] = {-3.0, 2.0, 0.0, 6.0}; // Should be {{-3, 2}, {0, 6}}
	
	if (matrices_equal(result, expected, 2, epsilon))
		printf("✓ 3x3 submatrix constructor test passed\n\n");
	else
		printf("✗ 3x3 submatrix constructor test failed\n\n");
}

static
void	test_submatrix_constructor_4x4(const double epsilon)
{
	double original[16] = {
		1.0, 5.0, 0.0, 2.0,
		-3.0, 2.0, 7.0, 1.0,
		0.0, 6.0, -3.0, 4.0,
		1.0, 1.0, 1.0, 1.0
	};
	double result[9];
	
	submatrix_constructor_4x4(original, result, 0, 1);
	
	print_matrix("Original 4x4", original, 4);
	print_matrix("Submatrix (remove row 0, col 1)", result, 3);
	
	double expected[9] = {
		-3.0, 7.0, 1.0,
		0.0, -3.0, 4.0,
		1.0, 1.0, 1.0
	};
	
	if (matrices_equal(result, expected, 3, epsilon))
		printf("✓ 4x4 submatrix constructor test passed\n\n");
	else
		printf("✗ 4x4 submatrix constructor test failed\n\n");
}

static
void	test_minor_matrix_3x3(const double epsilon)
{
	double matrix[9] = {1.0, 5.0, 0.0, -3.0, 2.0, 7.0, 0.0, 6.0, -3.0};
	double expected = -18.0;
	double minor = minor_matrix_3x3(matrix, 0, 2);
	
	print_matrix("Original 3x3", matrix, 3);
	printf("Minor M(0,2): %.3f (expected: %.3f)\n", minor, (-3.0 * (-3.0) - 2.0 * 0.0));
	
	if (doubles_equal(minor, expected, epsilon))
		printf("✓ Minor matrix test passed\n\n");
	else
		printf("✗ Minor matrix test failed\n\n");
}

static
void	test_cofactor_compute_3x3(const double epsilon)
{
	double matrix[9] = {1.0, 5.0, 0.0, -3.0, 2.0, 7.0, 0.0, 6.0, -3.0};
	double cofactor = cofactor_compute_3x3(matrix, 0, 2);
	double expected = -18.0;
	
	print_matrix("Original 3x3", matrix, 3);
	printf("Cofactor C(0,2): %.3f (expected: %.3f)\n", cofactor, expected);
	
	if (doubles_equal(cofactor, expected, epsilon))
		printf("✓ Cofactor compute test passed\n\n");
	else
		printf("✗ Cofactor compute test failed\n\n");
}

static
void	test_determinant_function(const double epsilon)
{
	// Test 2x2
	double mat2[4] = {1.0, 2.0, 3.0, 4.0};
	double det2 = determinant(mat2, 2);
	
	// Test 3x3
	double mat3[9] = {1.0, 2.0, 3.0, 0.0, 1.0, 4.0, 5.0, 6.0, 0.0};
	double det3 = determinant(mat3, 3);
	
	// Test 4x4 (simple identity)
	double mat4[16] = {0};
	identity_matrix_constructor(mat4);
	double det4 = determinant(mat4, 4);
	
	printf("2x2 Determinant: %.3f (expected: -2.0)\n", det2);
	printf("3x3 Determinant: %.3f (expected: 1.0)\n", det3);
	printf("4x4 Identity Determinant: %.3f (expected: 1.0)\n", det4);
	
	if (doubles_equal(det2, -2.0, epsilon) && 
		doubles_equal(det3, 1.0, epsilon) && 
		doubles_equal(det4, 1.0, epsilon))
		printf("✓ General determinant function test passed\n\n");
	else
		printf("✗ General determinant function test failed\n\n");
}

static
void	test_invertability(void)
{
	double	matrix_a[16] = {6.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 6.0, 4.0, -9.0, 3.0, -7.0, 9.0, 1.0, 7.0, -6.0};
	double	matrix_b[16] = {-4.0, 2.0, -2.0, -3.0, 9.0, 6.0, 2.0, 6.0, 0.0, -5.0, 1.0, -5.0, 0.0, 0.0, 0.0, 0.0};

	if (matrix_invertability(matrix_a) == 1 && matrix_invertability(matrix_b) == 0)
		printf("✓ Invertability compute test passed\n\n");
	else
		printf("✗ Invertability compute test failed\n\n");
}

static
void	test_matrix_inverse(const double epsilon)
{
	double	matrix_a[16] = {8.0, -5.0, 9.0, 2.0, \
							7.0, 5.0, 6.0, 1.0, \
							-6.0, 0.0, 9.0, 6.0, \
							-3.0, 0.0, -9.0, -4.0};
	double	matrix_b[16] = {9.0, 3.0, 0.0, 9.0, \
							-5.0, -2.0, -6.0, -3.0, \
							-4.0, 9.0, 6.0, 4.0, \
							-7.0, 6.0, 6.0, 2.0};
	matrix_inverse(matrix_a);
	matrix_inverse(matrix_b);
	double	expected_a[16] = {-0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308};
	double	expected_b[16] = {-0.04074 , -0.07778 , 0.14444 , -0.22222 ,
-0.07778 , 0.03333 , 0.36667 , -0.33333 ,
-0.02901 , -0.14630 , -0.10926 , 0.12963 ,
0.17778 , 0.06667 , -0.26667 , 0.33333};

	if (matrices_equal(matrix_a, expected_a, 4, epsilon) && matrices_equal(matrix_b, expected_b, 4, epsilon))
		printf("✓ Inverse compute test passed\n\n");
	else
		printf("✗ Inverse compute test failed\n\n");
}
*/

/* *********************************************************************** */
/*                             TRANSFORMS FUNCTIONS                         */
/* *********************************************************************** */

/*
static
void	test_translation_matrix(const double epsilon)
{
	double translation_matrix[16];
	t_vec3 point_a;
	t_vec3 result;
	t_vec3 expected;
	
	expected = point_constructor(2.0, 1.0, 7.0);
	point_a = point_constructor(-3.0, 4.0, 5.0);
	matrix_translation_constructor(translation_matrix, 5.0, -3.0, 2.0);
	print_matrix("Translation matrix", translation_matrix, 4);
	result = matrix_vector_multiply(translation_matrix, point_a);
	if (vectors_equal(result, expected, epsilon))
		printf("✓ Matrix translation (point) test passed\n\n");
	else
		printf("✗ Matrix translation (point) test failed\n\n");
}

static
void	test_translation_matrix_inverse(const double epsilon)
{
	double translation_matrix[16];
	t_vec3 point_a;
	t_vec3 result;
	t_vec3 expected;
	
	expected = point_constructor(-8.0, 7.0, 3.0);
	point_a = point_constructor(-3.0, 4.0, 5.0);
	matrix_translation_constructor(translation_matrix, 5.0, -3.0, 2.0);
	matrix_inverse(translation_matrix);
	print_matrix("Inverse matrix", translation_matrix, 4);
	result = matrix_vector_multiply(translation_matrix, point_a);
	if (vectors_equal(result, expected, epsilon))
		printf("✓ Inverse matrix translation test passed\n\n");
	else
		printf("✗ Inverse matrix translation test failed\n\n");
}

static
void	test_translation_matrix_vector(const double epsilon)
{
	double translation_matrix[16];
	t_vec3 vector_a;
	t_vec3 result;
	t_vec3 expected;
	
	expected = vector_constructor(-3.0, 4.0, 5.0);
	vector_a = vector_constructor(-3.0, 4.0, 5.0);
	matrix_translation_constructor(translation_matrix, 5.0, -3.0, 2.0);
	print_matrix("Translation matrix", translation_matrix, 4);
	result = matrix_vector_multiply(translation_matrix, vector_a);
	if (vectors_equal(result, expected, epsilon))
		printf("✓ Translation matrix (vector) test passed\n\n");
	else
		printf("✗ Translation matrix (vector) test failed\n\n");
}

static
void	test_scale_point(const double epsilon)
{
	double scale_matrix[16];
	t_vec3 point_a;
	t_vec3 result;
	t_vec3 expected;
	
	expected = point_constructor(-8.0, 18.0, 32.0);
	point_a = point_constructor(-4.0, 6.0, 8.0);
	print_matrix("Scale matrix", scale_matrix, 4);
	result = matrix_scale(scale_matrix, point_constructor(2.0, 3.0, 4.0), point_a);
	if (vectors_equal(result, expected, epsilon))
		printf("✓ Matrix scale point test passed\n\n");
	else
		printf("✗ Matrix scale point test failed\n\n");
}

static
void	test_scale_vector(const double epsilon)
{
	double scale_matrix[16];
	t_vec3 result;
	t_vec3 expected;
	
	expected = vector_constructor(-8.0, 18.0, 32.0);
	print_matrix("Scale matrix", scale_matrix, 4);
	result = matrix_scale(scale_matrix, point_constructor(2.0, 3.0, 4.0), vector_constructor(-4.0, 6.0, 8.0));
	if (vectors_equal(result, expected, epsilon))
		printf("✓ Matrix scale vector test passed\n\n");
	else
		printf("✗ Matrix scale vector test failed\n\n");
}

static
void	test_scale_inverse(const double epsilon)
{
	double scale_matrix[16];
	t_vec3 result;
	t_vec3 expected;
	
	expected = vector_constructor(-2.0, 2.0, 2.0);
	print_matrix("Scale matrix", scale_matrix, 4);
	result = matrix_scale_inverse(scale_matrix, point_constructor(2.0, 3.0, 4.0), vector_constructor(-4.0, 6.0, 8.0));
	if (vectors_equal(result, expected, epsilon))
		printf("✓ Matrix scale inverse test passed\n\n");
	else
		printf("✗ Matrix scale inverse test failed\n\n");
}

static
void	test_rotation_x(const double epsilon)
{
	double rotation_matrix[16];
	t_vec3 result1;
	t_vec3 result2;
	t_vec3 expected;
	
	print_matrix("Rotation matrix", rotation_matrix, 4);
	result1 = matrix_rotation(point_constructor(0.0, 1.0, 0.0), M_PI / 4, rotation_x_constructor);

	if (vectors_equal(result1, point_constructor(0.0, 0.707106781187, 0.707106781187), epsilon))
		printf("✓ Matrix rotation around x test passed\n\n");
	else
		printf("✗ Matrix rotation around x test failed\n\n");

	result2 = matrix_rotation(point_constructor(0.0, 1.0, 0.0), M_PI / 2, rotation_x_constructor);
	expected = point_constructor(0.0, 0.0, 1.0);
	if (vectors_equal(result2, expected, epsilon))
		printf("✓ Matrix rotation around x test passed\n\n");
	else
		printf("✗ Matrix rotation around x test failed\n\n");
}

static
void	test_rotation_y(const double epsilon)
{
	double rotation_matrix[16];
	t_vec3 result1;
	t_vec3 result2;
	t_vec3 expected;
	
	print_matrix("Rotation matrix", rotation_matrix, 4);
	result1 = matrix_rotation(point_constructor(0.0, 0.0, 1.0), M_PI / 4, rotation_y_constructor);

	if (vectors_equal(result1, point_constructor(0.707106781187, 0.0, 0.707106781187), epsilon))
		printf("✓ Matrix rotation around y test passed\n\n");
	else
		printf("✗ Matrix rotation around y test failed\n\n");

	result2 = matrix_rotation(point_constructor(0.0, 0.0, 1.0), M_PI / 2, rotation_y_constructor);
	expected = point_constructor(1.0, 0.0, 0.0);
	if (vectors_equal(result2, expected, epsilon))
		printf("✓ Matrix rotation around y test passed\n\n");
	else
		printf("✗ Matrix rotation around y test failed\n\n");
}

static
void	test_rotation_z(const double epsilon)
{
	double rotation_matrix[16];
	t_vec3 result1;
	t_vec3 result2;
	t_vec3 expected;
	
	print_matrix("Rotation matrix", rotation_matrix, 4);
	result1 = matrix_rotation(point_constructor(0.0, 1.0, 0.0), M_PI / 4, rotation_z_constructor);

	if (vectors_equal(result1, point_constructor(-0.707106781187, 0.707106781187, 0.0), epsilon))
		printf("✓ Matrix rotation around z test passed\n\n");
	else
		printf("✗ Matrix rotation around z test failed\n\n");

	result2 = matrix_rotation(point_constructor(0.0, 1.0, 0.0), M_PI / 2, rotation_z_constructor);
	expected = point_constructor(-1.0, 0.0, 0.0);
	if (vectors_equal(result2, expected, epsilon))
		printf("✓ Matrix rotation around z test passed\n\n");
	else
		printf("✗ Matrix rotation around z test failed\n\n");
}
*/

/* *********************************************************************** */
/*                             MAIN TESTER                                 */
/* *********************************************************************** */

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
		printf("xs.t[0] == %f, expected %f\n", xs.i[0].t, ex_t0);
		printf("xs.t[1]	== %f, expected %f\n", xs.i[1].t, ex_t1);
	}

	if ((xs.count == ex_count
		&& xs.i[0].t == ex_t0
		&& xs.i[1].t == ex_t1)
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

void	test_intersection(void)
{
	t_object	o =	{.sp = sphere()};
	t_intersection	i = intersection(3.5, o);

	printf("i.t == %f\n", i.t);
	printf("i.object.sp.id == %d\n", i.object.sp.id);

	if (i.t == 3.5 && i.object.sp.id == o.sp.id)
		printf("✓ Intersection test passed\n\n");
	else
		printf("✗ Intersection test failed\n\n");
}

bool	helper_test_hit(t_intersection *items, int items_size, t_intersection *expected)
{
	t_intersect xs;
	t_intersection	result;
	t_intersection *ret_val;

	intersections(items, &xs, items_size);
	ret_val = hit(&xs, &result, items_size);
	if (ret_val == NULL && expected == NULL)
		return (true);
	else if (ret_val == NULL && expected != NULL)
		return (false);
	printf("result.t == %f, expected %f\n", result.t, expected->t);
	printf("result.object.sp.id == %d, expected %d\n", result.object.sp.id, expected->object.sp.id);
	if (result.t != expected->t
		|| result.object.sp.id != expected->object.sp.id)
		return (false);
	return (true);
}

void	test_hit(void)
{
	t_object object = {.sp = sphere()};
	t_intersection items1[MAX_INTERSECTION] = {
		{.t = 1, .object = object},
		{.t = 2, .object = object},
	};
	t_intersection items2[MAX_INTERSECTION] = {
		{.t = -1, .object = object},
		{.t = 1, .object = object},
	};
	t_intersection items3[MAX_INTERSECTION] = {
		{.t = -2, .object = object},
		{.t = -1, .object = object},
	};
	t_intersection items4[MAX_INTERSECTION] = {
		{.t = 5, .object = object},
		{.t = 7, .object = object},
		{.t = -3, .object = object},
		{.t = 2, .object = object},
	};
	if (helper_test_hit(items1, 2, &items1[0]) == true
		&& helper_test_hit(items2, 2, &items2[1]) == true
		&& helper_test_hit(items4, 4, &items4[3]) == true
		&& helper_test_hit(items3, 2, NULL) == true)
		printf("✓ Hit test passed\n\n");
	else
		printf("✗ Hit test failed\n\n");

}

void	test_plot_circle_on_canvas()
{
	t_vec3	ray_origin = point_constructor(0, 0, -5);
	double	wall_z = 10;
	double	wall_size = 7.0;
	int		canvas_pixels = 1000;
	double	pixel_size = wall_size / canvas_pixels;
	double	half = wall_size / 2;
	t_canvas canvas;

	canvas_constructor(canvas_pixels, canvas_pixels, &canvas);
	t_vec3 color = color_constructor(1, 0, 0);
	t_object shape = {.sp = sphere()};

	for (int y = 0; y < canvas_pixels - 1; y++)
	{
		double world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels - 1; x++)
		{
			double world_x = -half + pixel_size * x;
			t_vec3 position = point_constructor(world_x, world_y, wall_z);
			t_ray r = ray_constructor(ray_origin, vector_normalization(vector_sub(position, ray_origin)));
			t_intersect xs = sphere_intersect(r, shape.sp);
			t_intersection smallest;
			if (hit(&xs, &smallest, xs.count) != NULL)
				write_pixel(&canvas, x, y, color);
		}
	}
	void	*win = mlx_new_window(canvas.mlx, canvas.width, canvas.height, "Tester");
	mlx_put_image_to_window(canvas.mlx, win, canvas.img.img, 0, 0);
	mlx_loop(canvas.mlx);
}

int	main(void)
{
	const double EPSILON = 1e-10;
	printf("=== Vector Library Test Suite for Ray Tracing Engine ===\n\n");
	
	/*
	// Test 1: Constructor functions
	printf("1. Testing Constructor Functions:\n");
	test_vector_point_constructor();
	
	// Test 2: Length functions
	printf("2. Testing Length Functions:\n");
	test_vector_length(EPSILON);
	
	// Test 3: Normalization
	printf("3. Testing Normalization:\n");
	test_vector_normalization(EPSILON);
	
	// Test 4: Dot Product
	printf("4. Testing Dot Product:\n");
	test_dot_product(EPSILON);
	
	// Test 5: Cross Product
	printf("5. Testing Cross Product:\n");
	test_cross_product(EPSILON);
	
	// Test 6: Vector Addition
	printf("6. Testing Vector Addition:\n");
	addition_tester(EPSILON);

	// Test 7: Vector Subtraction
	printf("7. Testing Vector Subtraction:\n");
	subtraction_tester(EPSILON);
	
	// Test 8: Vector Scaling
	printf("8. Testing Vector Scaling:\n");
	test_vector_scaling(EPSILON);
	
	// Test 9: Array access (union functionality)
	printf("9. Testing Array Access:\n");
	test_array_access();
	
	// Test 10: Edge cases
	printf("10. Testing Edge Cases:\n");
	test_edge_cases();
	*/

	// Color tests
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

	//printf("19. Testing window opening:\n");
	//test_window_opening();

	/*
	// Matrix Tests
	printf("20. Testing identity matrix constructor:\n");
	test_identity_matrix_constructor(EPSILON);
	
	printf("21. Testing matrix transpose:\n");
	test_matrix_transpose(EPSILON);
	
	printf("22. Testing matrix multiply:\n");
	test_matrix_multiply(EPSILON);
	
	printf("23. Testing matrix row constructor:\n");
	test_matrix_row_constructor(EPSILON);
	
	printf("24. Testing matrix-vector multiply:\n");
	test_matrix_vector_multiply(EPSILON);
	
	printf("25. Testing 2x2 determinant:\n");
	test_matrix_determinant_2x2(EPSILON);
	
	printf("26. Testing 3x3 determinant:\n");
	test_matrix_determinant_3x3(EPSILON);
	
	printf("27. Testing 3x3 submatrix constructor:\n");
	test_submatrix_constructor_3x3(EPSILON);
	
	printf("28. Testing 4x4 submatrix constructor:\n");
	test_submatrix_constructor_4x4(EPSILON);
	
	printf("29. Testing minor matrix:\n");
	test_minor_matrix_3x3(EPSILON);
	
	printf("30. Testing cofactor compute:\n");
	test_cofactor_compute_3x3(EPSILON);
	
	printf("31. Testing general determinant function:\n");
	test_determinant_function(EPSILON);

	printf("32. Testing invertability function:\n");
	test_invertability();

	printf("33. Testing matrix inverse function:\n");
	test_matrix_inverse(1e-4);

	// Transformations Tests
	printf("34. Testing matrix translation function:\n");
	test_translation_matrix(EPSILON);

	printf("35. Testing inverse matrix translation function:\n");
	test_translation_matrix_inverse(EPSILON);

	printf("36. Testing matrix translation function applied to vector:\n");
	test_translation_matrix_vector(EPSILON);

	printf("37. Testing matrix scale function applied to point:\n");
	test_scale_point(EPSILON);

	printf("38. Testing matrix scale function applied to vector:\n");
	test_scale_vector(EPSILON);

	printf("39. Testing matrix scale function applied to inverse:\n");
	test_scale_inverse(EPSILON);

	printf("40. Testing matrix rotaion function applied to x axis:\n");
	test_rotation_x(EPSILON);

	printf("41. Testing matrix rotaion function applied to y axis:\n");
	test_rotation_y(EPSILON);

	printf("42. Testing matrix rotaion function applied to z axis:\n");
	test_rotation_z(EPSILON);

	printf("43. Testing compution point from a distance:\n");
	test_ray_position(EPSILON);
	*/

	printf("44. Testing sphere intersections:\n");
	test_sphere_intersections();

	printf("45. Testing intersections:\n");
	test_intersection();

	printf("46. Testing hits:\n");
	test_hit();

	//printf("47. Testing plotting circle:\n");
	//test_plot_circle_on_canvas();

	printf("=== Test Suite Complete ===\n");

	return (0);
}
