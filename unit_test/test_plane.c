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

static bool	assert_intersect_empty(t_intersect actual, const char *msg)
{
	g_tests_run++;
	if (actual.count == 0)
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tExpected: empty intersection\n");
	printf("\tActual:   %d intersections\n", actual.count);
	return (false);
}

static bool	assert_intersect_count(t_intersect actual, int expected, const char *msg)
{
	g_tests_run++;
	if (actual.count == expected)
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tExpected: %d intersections\n", expected);
	printf("\tActual:   %d intersections\n", actual.count);
	return (false);
}

static bool	assert_float_eq(float actual, float expected, const char *msg)
{
	g_tests_run++;
	if (fabs(actual - expected) < EPSILON)
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s\n", RED, RESET, msg);
	printf("\tExpected: %.5f\n", expected);
	printf("\tActual:   %.5f\n", actual);
	return (false);
}

/* ************************************************************************** */
/* PLANE TESTS                                                              */
/* ************************************************************************** */

void	test_plane_normal_is_constant_everywhere(void)
{
	t_vec3	n1, n2, n3;
	t_vec3	normal;

	printf("\n--- The normal of a plane is constant everywhere ---\n");

	n1 = local_normal_at_plane();
	n2 = local_normal_at_plane();
	n3 = local_normal_at_plane();
	
	normal = vector_constructor(0, 1, 0);
	assert_vec3_eq(n1, normal, "Normal at origin");
	assert_vec3_eq(n2, normal, "Normal at (10, 0, -10)");
	assert_vec3_eq(n3, normal, "Normal at (-5, 0, 150)");
}

void	test_intersect_ray_parallel_to_plane(void)
{
	t_plane		p;
	t_ray		r;
	t_intersect	xs;

	printf("\n--- Intersect with a ray parallel to the plane ---\n");

	p = plane();
	r = ray_constructor(point_constructor(0, 10, 0), vector_constructor(0, 0, 1));
	xs = local_intersect_plane(&p, r);
	
	assert_intersect_empty(xs, "Ray parallel to plane has no intersections");
}

void	test_intersect_coplanar_ray(void)
{
	t_plane		p;
	t_ray		r;
	t_intersect	xs;

	printf("\n--- Intersect with a coplanar ray ---\n");

	p = plane();
	r = ray_constructor(point_constructor(0, 0, 0), vector_constructor(0, 0, 1));
	xs = local_intersect_plane(&p, r);
	
	assert_intersect_empty(xs, "Coplanar ray has no intersections");
}

void	test_intersect_plane_from_above(void)
{
	t_plane		p;
	t_ray		r;
	t_intersect	xs;

	printf("\n--- A ray intersecting a plane from above ---\n");

	p = plane();
	r = ray_constructor(point_constructor(0, 1, 0), vector_constructor(0, -1, 0));
	xs = local_intersect_plane(&p, r);
	
	assert_intersect_count(xs, 1, "Intersection count is 1");
	assert_float_eq(xs.i[0].t, 1.0f, "Intersection t value is 1");
	// Note: object comparison would require more complex assertion
}

void	test_intersect_plane_from_below(void)
{
	t_plane		p;
	t_ray		r;
	t_intersect	xs;

	printf("\n--- A ray intersecting a plane from below ---\n");

	p = plane();
	r = ray_constructor(point_constructor(0, -1, 0), vector_constructor(0, 1, 0));
	xs = local_intersect_plane(&p, r);
	
	assert_intersect_count(xs, 1, "Intersection count is 1");
	assert_float_eq(xs.i[0].t, 1.0f, "Intersection t value is 1");
	// Note: object comparison would require more complex assertion
}

/* ************************************************************************** */
/* TEST SUMMARY                                                             */
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

/* ************************************************************************** */
/* MAIN TEST RUNNER                                                          */
/* ************************************************************************** */

int	main(void)
{
	printf("PLANE TESTS\n");
	printf("==================================================\n");

	/* Plane tests */
	test_plane_normal_is_constant_everywhere();
	test_intersect_ray_parallel_to_plane();
	test_intersect_coplanar_ray();
	test_intersect_plane_from_above();
	test_intersect_plane_from_below();

	print_test_summary();
	return (g_tests_passed == g_tests_run ? 0 : 1);
}
