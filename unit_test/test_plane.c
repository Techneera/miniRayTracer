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

/* ************************************************************************** */
/* PLANE TESTS                                                              */
/* ************************************************************************** */

void	test_plane_normal_is_constant_everywhere(void)
{
	t_plane	p;
	t_vec3	n1, n2, n3;

	printf("\n--- The normal of a plane is constant everywhere ---\n");

	p = plane();
	n1 = local_normal_at(&p, point(0, 0, 0));
	n2 = local_normal_at(&p, point(10, 0, -10));
	n3 = local_normal_at(&p, point(-5, 0, 150));
	
	assert_vec3_eq(n1, vector(0, 1, 0), "Normal at origin");
	assert_vec3_eq(n2, vector(0, 1, 0), "Normal at (10, 0, -10)");
	assert_vec3_eq(n3, vector(0, 1, 0), "Normal at (-5, 0, 150)");
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

	print_test_summary();
	return (g_tests_passed == g_tests_run ? 0 : 1);
}