#include "ray.h"

#define EPSILON 0.00001
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

/* ************************************************************************** */
/*                              HELPER FOR TESTS                              */
/* ************************************************************************** */

static	int	g_tests_run = 0;
static	int g_tests_passed = 0;

static
bool	assert_float_eq(double actual, double expected, const char *msg)
{
	g_tests_run++;
	if (fabs(actual - expected) < EPSILON)
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tExpected: %.5f\n\tActual: %.5f\n", expected, actual);
	return (false);
}

static
bool	assert_vec3_eq(t_vec3 a, t_vec3 b, const char *msg)
{
	g_tests_run++;
	if (fabs(a.x - b.x) < EPSILON && \
		fabs(a.y - b.y) < EPSILON && \
		fabs(a.z - b.z) < EPSILON && \
		fabs(a.w - b.w) < EPSILON)
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tExpected: (%.2f, %.2f, %.2f, %.0f)\n", b.x, b.y, b.z, b.w);
	printf("\tActual:   (%.2f, %.2f, %.2f, %.0f)\n", a.x, a.y, a.z, a.w);
	return (false);
}

static
bool	assert_mat4_eq(t_mat4 a, t_mat4 b, const char *msg)
{
	int	i;
	g_tests_run++;

	i = 0;
	while (i < 16)
	{
		if (fabsf(a.m[i] - b.m[i]) > EPSILON)
		{
			printf("%s[FAIL]%s %s (Mismatch at index %d)\n", RED, RESET, msg, i);
			printf("   Expected: %.4f | Actual: %.4f\n", b.m[i], a.m[i]);
			return (false);
		}
		i++;
	}
	g_tests_passed++;
	printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
	return (true);
}

/* ************************************************************************** */
/*                            VECTOR BASIC TESTS                              */
/* ************************************************************************** */

void test_constructors(void)
{
	printf("\n--- 1. Constructors ---\n");

	// Test Point (w should be 1.0)
	t_vec3 p = point_constructor(10.5f, -2.0f, 0.0f);
	t_vec3 exp_p = { .x=10.5f, .y=-2.0f, .z=0.0f, .w=1.0f };
	assert_vec3_eq(p, exp_p, "point_constructor sets w=1.0");

	// Test Vector (w should be 0.0)
	t_vec3 v = vector_constructor(10.5f, -2.0f, 0.0f);
	t_vec3 exp_v = { .x=10.5f, .y=-2.0f, .z=0.0f, .w=0.0f };
	assert_vec3_eq(v, exp_v, "vector_constructor sets w=0.0");
}

void test_length(void)
{
	printf("\n--- 2. Length & Magnitude ---\n");

	t_vec3 v = vector_constructor(1.0f, 2.0f, 3.0f);
	
	// Squared Length: 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
	float sq = vector_length_squared(v);
	assert_float_eq(sq, 14.0f, "vector_length_squared (1,2,3)");

	// Actual Length: sqrt(14) ~= 3.741657
	float len = vector_length(v);
	assert_float_eq(len, sqrtf(14.0f), "vector_length (1,2,3)");

	// Test Unit Vector Length
	t_vec3 unit = vector_constructor(1, 0, 0);
	assert_float_eq(vector_length(unit), 1.0f, "vector_length of unit vector");

	// Test Zero Vector
	t_vec3 zero = vector_constructor(0, 0, 0);
	assert_float_eq(vector_length(zero), 0.0f, "vector_length of zero vector");
}

void test_normalization(void)
{
	printf("\n--- 3. Normalization ---\n");

	// Case 1: Standard Vector (4, 0, 0) -> (1, 0, 0)
	t_vec3 v = vector_constructor(4.0f, 0.0f, 0.0f);
	t_vec3 norm = vector_normalization(v);
	t_vec3 exp = vector_constructor(1.0f, 0.0f, 0.0f);
	assert_vec3_eq(norm, exp, "Normalize (4,0,0) -> (1,0,0)");

	// Case 2: Arbitrary Vector (1, 2, 3)
	t_vec3 v2 = vector_constructor(1.0f, 2.0f, 3.0f);
	t_vec3 n2 = vector_normalization(v2);
	assert_float_eq(vector_length(n2), 1.0f, "Magnitude of normalized vector is 1.0");

	// Case 3: Zero Vector (Edge Case) - Should return 0 without crashing/NaN
	t_vec3 zero = vector_constructor(0.0f, 0.0f, 0.0f);
	t_vec3 n_zero = vector_normalization(zero);
	assert_vec3_eq(n_zero, zero, "Normalize (0,0,0) handles safely");
}

void test_dot_product(void)
{
	printf("\n--- 4. Dot Product ---\n");

	t_vec3 a = vector_constructor(1.0f, 2.0f, 3.0f);
	t_vec3 b = vector_constructor(2.0f, 3.0f, 4.0f);

	// Calculation: (1*2) + (2*3) + (3*4) = 2 + 6 + 12 = 20
	float res = vector_dot_product(a, b);
	assert_float_eq(res, 20.0f, "Dot Product (1,2,3) . (2,3,4)");

	// Orthogonal Vectors (Dot product should be 0)
	t_vec3 x = vector_constructor(1, 0, 0);
	t_vec3 y = vector_constructor(0, 1, 0);
	assert_float_eq(vector_dot_product(x, y), 0.0f, "Dot Product of Orthogonal Vectors (X . Y)");
}

void test_cross_product(void)
{
	printf("\n--- 5. Cross Product ---\n");

	t_vec3 x = vector_constructor(1, 0, 0);
	t_vec3 y = vector_constructor(0, 1, 0);
	t_vec3 z = vector_constructor(0, 0, 1);

	// X x Y = Z
	t_vec3 res1 = vector_cross_product(x, y);
	assert_vec3_eq(res1, z, "Cross Product X x Y = Z");

	// Y x X = -Z
	t_vec3 neg_z = vector_constructor(0, 0, -1);
	t_vec3 res2 = vector_cross_product(y, x);
	assert_vec3_eq(res2, neg_z, "Cross Product Y x X = -Z");

	// X x X = 0
	t_vec3 zero = vector_constructor(0, 0, 0);
	t_vec3 res3 = vector_cross_product(x, x);
	assert_vec3_eq(res3, zero, "Cross Product Self (X x X) = 0");
}

void test_arithmetic(void)
{
	printf("\n--- 6. Arithmetic Operations ---\n");

	t_vec3 v1 = vector_constructor(3.0f, 2.0f, 1.0f);
	t_vec3 v2 = vector_constructor(1.0f, 2.0f, 3.0f);

	// ADDITION
	t_vec3 sum = vector_add(v1, v2);
	t_vec3 exp_sum = vector_constructor(4.0f, 4.0f, 4.0f);
	assert_vec3_eq(sum, exp_sum, "Vector Add (3,2,1) + (1,2,3)");

	// SUBTRACTION
	t_vec3 sub = vector_sub(v1, v2);
	t_vec3 exp_sub = vector_constructor(2.0f, 0.0f, -2.0f);
	assert_vec3_eq(sub, exp_sub, "Vector Sub (3,2,1) - (1,2,3)");

	// SCALING
	t_vec3 scaled = vector_scale(v1, 2.5f);
	t_vec3 exp_scale = vector_constructor(7.5f, 5.0f, 2.5f);
	assert_vec3_eq(scaled, exp_scale, "Vector Scale (3,2,1) * 2.5");
	
	// POINT ARITHMETIC (Substracting two points = vector)
	t_vec3 p1 = point_constructor(10, 10, 10);
	t_vec3 p2 = point_constructor(5, 5, 5);
	t_vec3 vec_diff = vector_sub(p1, p2);
	
	// Result should have w = 1 - 1 = 0 (Vector)
	t_vec3 exp_diff = { .x=5, .y=5, .z=5, .w=0 }; 
	assert_vec3_eq(vec_diff, exp_diff, "Point - Point = Vector (w=0 check)");
}

/* ************************************************************************** */
/*                            MATRIX BASIC TESTS                              */
/* ************************************************************************** */

void test_matrix_mult(void)
{
	printf("\n--- Matrix Multiplication ---\n");

	t_mat4 a, b, expected, result;

	// Initialize A (Linear values 1-16)
	// 1  2  3  4
	// 5  6  7  8
	// 9  10 11 12
	// 13 14 15 16
	for(int i=0; i<16; i++) a.m[i] = (float)(i + 1);

	// Initialize B (Identity-like)
	// -2  1  2  3
	//  3  2  1 -1
	//  4  3  6  5
	//  1  2  7  8
	float vals_b[] = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
	for(int i=0; i<16; i++) b.m[i] = vals_b[i];

	// Expected Result
	float vals_exp[] = {20, 22, 50, 48, 44, 54, 114, 108, 68, 86, 178, 168, 92, 118, 242, 228};
	for(int i=0; i<16; i++) expected.m[i] = vals_exp[i];

	result = matrix_multiply(a, b);
	assert_mat4_eq(result, expected, "4x4 Multiplication");
}

void test_matrix_vector_multiplyt(void)
{
	printf("\n--- Matrix x Vector ---\n");
	
	t_mat4 A;
	// 1 2 3 4
	// 2 4 4 2
	// 8 6 4 1
	// 0 0 0 1
	float vals[] = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
	for(int i=0; i<16; i++) A.m[i] = vals[i];

	t_vec3 b = point_constructor(1, 2, 3); // w=1
	
	// Calc: 
	// x = 1*1 + 2*2 + 3*3 + 4*1 = 18
	// y = 2*1 + 4*2 + 4*3 + 2*1 = 24
	// z = 8*1 + 6*2 + 4*3 + 1*1 = 33
	// w = 1
	t_vec3 expected = point_constructor(18, 24, 33);
	t_vec3 result = matrix_vector_multiply(A, b);

	assert_vec3_eq(result, expected, "Matrix * Point");
}

void test_transpose(void)
{
	printf("\n--- Matrix Transpose ---\n");
	t_mat4 m;
	// 0 9 3 0
	// 9 8 0 8
	// 1 8 5 3
	// 0 0 5 8
	float vals[] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
	for(int i=0; i<16; i++) m.m[i] = vals[i];

	// Expected Transpose
	// 0 9 1 0
	// 9 8 8 0
	// 3 0 5 5
	// 0 8 3 8
	float vals_t[] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
	t_mat4 expected;
	for(int i=0; i<16; i++) expected.m[i] = vals_t[i];

	t_mat4 result = matrix_transpose(m);
	assert_mat4_eq(result, expected, "Transpose Matrix");
}

void test_determinant_inverse(void)
{
	printf("\n--- Determinant & Inverse ---\n");
	t_mat4 m;
	// -5 2 6 -8
	// 1 -5 1 8
	// 7 7 -6 -7
	// 1 -3 7 4
	float vals[] = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
	for(int i=0; i<16; i++) m.m[i] = vals[i];

	float det = matrix_determinant(m);
	assert_float_eq(det, 532.0f, "Determinant Calculation");

	t_mat4 inv = matrix_inverse(m);
	t_mat4 m_x_inv = matrix_multiply(m, inv);
	
	t_mat4 id; 
	matrix_identity(&id);

	assert_mat4_eq(m_x_inv, id, "M * M_inverse == Identity");
}

/* ************************************************************************** */
/*                          TRANSFORMATION TESTS                              */
/* ************************************************************************** */

void test_translation(void)
{
	printf("\n--- Translation ---\n");
	t_mat4 transform = matrix_translation(5, -3, 2);
	t_vec3 p = point_constructor(-3, 4, 5);
	
	t_vec3 expected = point_constructor(2, 1, 7);
	t_vec3 result = matrix_vector_multiply(transform, p);
	
	assert_vec3_eq(result, expected, "Translate Point (-3,4,5) by (5,-3,2)");
	
	// Inverse Translation
	t_mat4 inv = matrix_inverse(transform);
	t_vec3 orig = matrix_vector_multiply(inv, result);
	assert_vec3_eq(orig, p, "Inverse Translation restores point");
}

void test_scaling(void)
{
	printf("\n--- Scaling ---\n");
	t_mat4 transform = matrix_scale(2, 3, 4);
	t_vec3 v = vector_constructor(-4, 6, 8);
	
	t_vec3 expected = vector_constructor(-8, 18, 32);
	t_vec3 result = matrix_vector_multiply(transform, v);
	
	assert_vec3_eq(result, expected, "Scale Vector (-4,6,8) by (2,3,4)");
}

void test_rotation(void)
{
	printf("\n--- Rotation ---\n");
	t_vec3 p = point_constructor(0, 1, 0);
	
	// Rotate X 90 degrees (half pi)
	t_mat4 rot_x = matrix_rot_x(M_PI / 2.0f);
	// (0, 1, 0) -> (0, 0, 1)
	t_vec3 res_x = matrix_vector_multiply(rot_x, p);
	assert_vec3_eq(res_x, point_constructor(0, 0, 1), "Rotate X (90 deg)");

	// Rotate Y 90 degrees
	t_vec3 p2 = point_constructor(0, 0, 1);
	t_mat4 rot_y = matrix_rot_y(M_PI / 2.0f);
	// (0, 0, 1) -> (1, 0, 0)
	t_vec3 res_y = matrix_vector_multiply(rot_y, p2);
	assert_vec3_eq(res_y, point_constructor(1, 0, 0), "Rotate Y (90 deg)");

	// Rotate Z 90 degrees
	t_vec3 p3 = point_constructor(0, 1, 0);
	t_mat4 rot_z = matrix_rot_z(M_PI / 2.0f);
	// (0, 1, 0) -> (-1, 0, 0)
	t_vec3 res_z = matrix_vector_multiply(rot_z, p3);
	assert_vec3_eq(res_z, point_constructor(-1, 0, 0), "Rotate Z (90 deg)");
}

void test_chaining(void)
{
	printf("\n--- Chaining Transformations ---\n");
	t_vec3 p = point_constructor(1, 0, 1);
	t_mat4 A = matrix_rot_x(M_PI / 2.0f);
	t_mat4 B = matrix_scale(5, 5, 5);
	t_mat4 C = matrix_translation(10, 5, 7);

	// Apply: Rotate, then Scale, then Translate
	// T = C * B * A
	t_mat4 T = matrix_multiply(C, matrix_multiply(B, A));
	
	t_vec3 result = matrix_vector_multiply(T, p);
	// 1. RotX(1,0,1) -> (1, -1, 0)
	// 2. Scale(5,5,5) -> (5, -5, 0)
	// 3. Trans(10,5,7) -> (15, 0, 7)
	
	assert_vec3_eq(result, point_constructor(15, 0, 7), "Chained Transform (Rot->Scale->Trans)");
}

/* ************************************************************************** */
/*                                   RAY TRANSFORM                            */
/* ************************************************************************** */

void	test_ray_translate(void)
{
	printf("\n--- Ray Transform ---\n");

	// Given r <- ray(point(1, 2, 3), vector(0, 1, 0))
	t_vec3	origin = point_constructor(1.0, 2.0, 3.0);
	t_vec3	direction = vector_constructor(0.0, 1.0, 0.0);
	t_ray	r = ray_constructor(origin, direction);
	
	// And m <- scaling(3, 4, 5)
	t_mat4	trans = matrix_translation(3.0, 4.0, 5.0);

	// When r2 <- transform(r, m)
	t_ray	r2 = ray_transform(r, trans);

	// Then r2.origin = point(4, 6, 8)
	assert_vec3_eq(r2.origin, point_constructor(4.0, 6.0, 8.0), "Translate Transform Point(1, 2, 3) to (4, 6, 8)");
	// And r2.direction = vector(0, 1, 0)
	// Note: does not change the direction of the ray
	assert_vec3_eq(r2.direction, vector_constructor(0.0, 1.0, 0.0), "Translate Transform Direction (Unchanged)");
}
void test_ray_scaling(void)
{
	printf("\n--- Ray Scaling ---\n");
	
	// Given r <- ray(point(1, 2, 3), vector(0, 1, 0))
	t_vec3 origin = point_constructor(1, 2, 3);
	t_vec3 direction = vector_constructor(0, 1, 0);
	t_ray r = ray_constructor(origin, direction);
	
	// And m <- scaling(2, 3, 4)
	t_mat4 m = matrix_scale(2, 3, 4);
	
	// When r2 <- transform(r, m)
	t_ray r2 = ray_transform(r, m);
	
	// Then r2.origin = point(2, 6, 12)
	// (1*2, 2*3, 3*4)
	t_vec3 expected_origin = point_constructor(2, 6, 12);
	assert_vec3_eq(r2.origin, expected_origin, "Scaled Ray Origin");
	
	// And r2.direction = vector(0, 3, 0)
	// (0*2, 1*3, 0*4) -> Note: It is NOT normalized, as per scenario
	t_vec3 expected_direction = vector_constructor(0, 3, 0);
	assert_vec3_eq(r2.direction, expected_direction, "Scaled Ray Direction");
}
/* ************************************************************************** */
/*                                   MAIN                                     */
/* ************************************************************************** */

int main(void)
{
	printf("===============================================================\n");
	printf("       HIGH-PERFORMANCE MATRIX AND VECTOR LIBRARIES TESTER     \n");
	printf("===============================================================\n");

	test_constructors();
	test_length();
	test_normalization();
	test_dot_product();
	test_cross_product();
	test_arithmetic();

	test_matrix_mult();
	test_matrix_vector_multiplyt();
	test_transpose();
	test_determinant_inverse();
	
	test_translation();
	test_scaling();
	test_rotation();
	test_chaining();

	test_ray_translate();
	test_ray_scaling();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");
	
	return (g_tests_passed != g_tests_run);
}
