#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "vector.h"
#include "matrix.h"
#include "ray.h"
#include "shades.h"

#define EPSILON 0.00001
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

static int g_tests_run = 0;
static int g_tests_passed = 0;

/* ************************************************************************** */
/* TEST HELPER FUNCTIONS                                                     */
/* ************************************************************************** */

static bool	vectors_equal(t_vec3 a, t_vec3 b, double epsilon)
{
	return (fabs(a.x - b.x) < epsilon && 
			fabs(a.y - b.y) < epsilon && 
			fabs(a.z - b.z) < epsilon);
}

static bool	materials_equal(t_material a, t_material b, double epsilon)
{
	return (vectors_equal(a.color, b.color, epsilon) &&
			fabs(a.ambient - b.ambient) < epsilon &&
			fabs(a.diffuse - b.diffuse) < epsilon &&
			fabs(a.specular - b.specular) < epsilon &&
			fabs(a.shininess - b.shininess) < epsilon);
}

static bool	matrices_equal(t_mat4 a, t_mat4 b, double epsilon)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (fabs(a.m[i] - b.m[i]) > epsilon)
			return (false);
		i++;
	}
	return (true);
}

static bool	assert_vec3_eq(t_vec3 actual, t_vec3 expected, const char *msg)
{
	g_tests_run++;
	if (vectors_equal(actual, expected, EPSILON))
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tExpected: (%.5f, %.5f, %.5f)\n", expected.x, expected.y, expected.z);
	printf("\tActual:   (%.5f, %.5f, %.5f)\n", actual.x, actual.y, actual.z);
	return (false);
}

static bool	assert_material_eq(t_material actual, t_material expected, const char *msg)
{
	g_tests_run++;
	if (materials_equal(actual, expected, EPSILON))
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tExpected: color(%.3f, %.3f, %.3f), amb:%.3f, diff:%.3f, spec:%.3f, shin:%.3f\n",
		expected.color.x, expected.color.y, expected.color.z, 
		expected.ambient, expected.diffuse, expected.specular, expected.shininess);
	printf("\tActual:   color(%.3f, %.3f, %.3f), amb:%.3f, diff:%.3f, spec:%.3f, shin:%.3f\n",
		actual.color.x, actual.color.y, actual.color.z,
		actual.ambient, actual.diffuse, actual.specular, actual.shininess);
	return (false);
}

static bool	assert_matrix_eq(t_mat4 actual, t_mat4 expected, const char *msg)
{
	g_tests_run++;
	if (matrices_equal(actual, expected, EPSILON))
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tMatrices don't match\n");
	return (false);
}

/* ************************************************************************** */
/* TEST SHAPE WITH SAVED RAY (FOR INTERSECTION TESTING)                     */
/* ************************************************************************** */

typedef struct s_test_shape
{
	t_shape		shape;
	t_ray		saved_ray;
}	t_test_shape;

/* Test shape that saves the ray passed to it for testing purposes */
t_test_shape *test_shape_with_saved_ray(void)
{
	static t_test_shape ts;
	
	ts.shape.type = SHAPE_TEST;
	ts.shape.id = get_shape_id();
	matrix_identity(&ts.shape.transform);
	matrix_identity(&ts.shape.transform_inv);
	ts.shape.material = material_default();
	ts.saved_ray = ray_constructor(vector_constructor(0, 0, 0), vector_constructor(0, 0, 0));
	return (&ts);
}

/* Override intersect function for test shape to save the ray */
t_intersect	intersect_test_shape(t_ray ray, t_test_shape *shape)
{
	t_ray		local_ray;
	t_intersect	result;

	local_ray = ray_transform(ray, shape->shape.transform_inv);
	shape->saved_ray = local_ray; // Save the transformed ray for testing
	result.count = 0; // Test shape doesn't produce intersections
	return (result);
}

/* ************************************************************************** */
/* HELPER FUNCTIONS (ALIASES FOR CONVENIENCE)                              */
/* ************************************************************************** */

t_vec3	point(float x, float y, float z)
{
	return (point_constructor(x, y, z));
}

t_vec3	vector(float x, float y, float z)
{
	return (vector_constructor(x, y, z));
}

t_ray ray(t_vec3 origin, t_vec3 direction)
{
	return (ray_constructor(origin, direction));
}

t_mat4	identity_matrix(void)
{
	t_mat4 m;
	matrix_identity(&m);
	return (m);
}

t_mat4	translation(float x, float y, float z)
{
	return (matrix_translation(x, y, z));
}

t_mat4	scaling(float x, float y, float z)
{
	return (matrix_scale(x, y, z));
}

t_mat4	rotation_z(float angle)
{
	return (matrix_rot_z(angle));
}

/* ************************************************************************** */
/* TRANSFORMATION TESTS                                                      */
/* ************************************************************************** */

void	test_default_transformation(void)
{
	t_shape	s;
	t_mat4	expected;

	printf("\n--- The default transformation ---\n");

	s = test_shape();
	expected = identity_matrix();
	assert_matrix_eq(s.transform, expected, "Shape has identity matrix as default transform");
}

void	test_assigning_transformation(void)
{
	t_shape	s;
	t_mat4	t;

	printf("\n--- Assigning a transformation ---\n");

	s = test_shape();
	t = translation(2, 3, 4);
	set_transform(&s, t);
	assert_matrix_eq(s.transform, t, "Shape transform set correctly");
}

/* ************************************************************************** */
/* MATERIAL TESTS                                                            */
/* ************************************************************************** */

void	test_default_material(void)
{
	t_shape		s;
	t_material	m;
	t_material	expected;

	printf("\n--- The default material ---\n");

	s = test_shape();
	m = s.material;
	expected = material_default();
	assert_material_eq(m, expected, "Shape has default material");
}

void	test_assigning_material(void)
{
	t_shape		s;
	t_material	m;

	printf("\n--- Assigning a material ---\n");

	s = test_shape();
	m = material_default();
	m.ambient = 1.0f;
	s.material = m;
	assert_material_eq(s.material, m, "Shape material assigned correctly");
}

/* ************************************************************************** */
/* INTERSECTION TESTS                                                        */
/* ************************************************************************** */

void	test_intersecting_scaled_shape_with_ray(void)
{
	t_ray			r;
	t_test_shape	*s;

	printf("\n--- Intersecting a scaled shape with a ray ---\n");

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = test_shape_with_saved_ray();
	set_transform(&s->shape, scaling(2, 2, 2));
	(void)intersect_test_shape(r, s);
	
	assert_vec3_eq(s->saved_ray.origin, point(0, 0, -2.5), "Scaled shape saved ray origin");
	assert_vec3_eq(s->saved_ray.direction, vector(0, 0, 0.5), "Scaled shape saved ray direction");
}

void	test_intersecting_translated_shape_with_ray(void)
{
	t_ray			r;
	t_test_shape	*s;

	printf("\n--- Intersecting a translated shape with a ray ---\n");

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = test_shape_with_saved_ray();
	set_transform(&s->shape, translation(5, 0, 0));
	(void)intersect_test_shape(r, s);
	
	assert_vec3_eq(s->saved_ray.origin, point(-5, 0, -5), "Translated shape saved ray origin");
	assert_vec3_eq(s->saved_ray.direction, vector(0, 0, 1), "Translated shape saved ray direction");
}

/* ************************************************************************** */
/* NORMAL COMPUTATION TESTS                                                  */
/* ************************************************************************** */

void	test_computing_normal_on_translated_shape(void)
{
	t_shape	s;
	t_vec3	n;

	printf("\n--- Computing the normal on a translated shape ---\n");

	s = test_shape();
	set_transform(&s, translation(0, 1, 0));
	n = normal_at(&s, point(0, 1.70711, -0.70711));
	assert_vec3_eq(n, vector(0, 0.70711, -0.70711), "Normal on translated shape");
}

void	test_computing_normal_on_transformed_shape(void)
{
	t_shape	s;
	t_mat4	m;
	t_vec3	n;
	float	sqrt2_over_2;

	printf("\n--- Computing the normal on a transformed shape ---\n");

	sqrt2_over_2 = sqrtf(2.0f) / 2.0f;
	s = test_shape();
	m = matrix_multiply(scaling(1, 0.5, 1), rotation_z(M_PI / 5.0f));
	set_transform(&s, m);
	n = normal_at(&s, point(0, sqrt2_over_2, -sqrt2_over_2));
	assert_vec3_eq(n, vector(0, 0.97014, -0.24254), "Normal on transformed shape");
}

/* ************************************************************************** */
/* MAIN TEST RUNNER                                                          */
/* ************************************************************************** */

void	print_test_summary(void)
{
	printf("\n==================================================\n");
	printf("TEST SUMMARY\n");
	printf("==================================================\n");
	printf("Tests run: %d\n", g_tests_run);
	printf("Tests passed: %d\n", g_tests_passed);
	printf("Tests failed: %d\n", g_tests_run - g_tests_passed);
	
	if (g_tests_passed == g_tests_run)
		printf("%sAll tests passed!%s\n", GREEN, RESET);
	else
		printf("%s%d test(s) failed!%s\n", RED, g_tests_run - g_tests_passed, RESET);
}

int	main(void)
{
	printf("SHAPE REFACTOR TESTS\n");
	printf("==================================================\n");

	/* Transformation tests */
	test_default_transformation();
	test_assigning_transformation();

	/* Material tests */
	test_default_material();
	test_assigning_material();

	/* Intersection tests */
	test_intersecting_scaled_shape_with_ray();
	test_intersecting_translated_shape_with_ray();

	/* Normal computation tests */
	test_computing_normal_on_translated_shape();
	test_computing_normal_on_transformed_shape();

	print_test_summary();
	return (g_tests_passed == g_tests_run ? 0 : 1);
}
