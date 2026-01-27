#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "matrix.h"
#include "scene.h"

#define EPSILON 0.00001
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

static int g_tests_run = 0;
static int g_tests_passed = 0;

bool assert_float_eq(float actual, float expected, const char *msg)
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

bool assert_int_eq(int actual, int expected, const char *msg)
{
	g_tests_run++;
	if (actual == expected)
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s (Exp: %d, Got: %d)\n", RED, RESET, msg, expected, actual);
	return (false);
}

bool assert_ptr_eq(void *actual, void *expected, const char *msg)
{
	g_tests_run++;
	if (actual == expected)
	{
		g_tests_passed++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
		return (true);
	}
	printf("%s[FAIL]%s %s (Exp: %p, Got: %p)\n", RED, RESET, msg, expected, actual);
	return (false);
}

bool assert_vec3_eq(t_vec3 actual, t_vec3 expected, const char *msg)
{
    g_tests_run++;
    if (fabs(actual.x - expected.x) < EPSILON &&
        fabs(actual.y - expected.y) < EPSILON &&
        fabs(actual.z - expected.z) < EPSILON)
    {
        g_tests_passed++;
        printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
        return (true);
    }
    printf("%s[FAIL]%s %s\n", RED, RESET, msg);
    printf("\tExpected: (%.3f, %.3f, %.3f)\n", expected.x, expected.y, expected.z);
    printf("\tActual:   (%.3f, %.3f, %.3f)\n", actual.x, actual.y, actual.z);
    return (false);
}

bool assert_bool_eq(bool actual, bool expected, const char *msg)
{
    g_tests_run++;
    if (actual == expected)
    {
        g_tests_passed++;
        printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
        return (true);
    }
    printf("%s[FAIL]%s %s (Exp: %d, Got: %d)\n", RED, RESET, msg, expected, actual);
    return (false);
}

void test_default_world(void)
{
    t_world         w;
    t_point_light   expected_light;
    t_vec3          expected_color;
    
    printf("\n--- The default world ---\n");
    
    // Given: Expected light
    expected_light = point_light(point_constructor(-10, 10, -10),
                                color_constructor(1, 1, 1));
    
    // When: Create default world
    w = default_world();
    
    // Then: World light matches expected
    assert_vec3_eq(w.light.position, expected_light.position, 
                   "Default world light position");
    assert_vec3_eq(w.light.intensity, expected_light.intensity,
                   "Default world light intensity");
    
    // And: World contains 2 objects
    assert_int_eq(w.object_count, 2, "Default world has 2 objects");
    
    // And: First sphere (s1) has correct properties
    assert_int_eq(w.objects[0].type, SPHERE, "First object is a sphere");
    expected_color = color_constructor(0.8, 1.0, 0.6);
    assert_vec3_eq(w.objects[0].object.sp.material.color, expected_color,
                   "First sphere color is (0.8, 1.0, 0.6)");
    assert_float_eq(w.objects[0].object.sp.material.diffuse, 0.7f,
                    "First sphere diffuse is 0.7");
    assert_float_eq(w.objects[0].object.sp.material.specular, 0.2f,
                    "First sphere specular is 0.2");
    
    // And: Second sphere (s2) exists and has scaling transform
    assert_int_eq(w.objects[1].type, SPHERE, "Second object is a sphere");
    // Check that transform is a scaling matrix
    // A scaled sphere will have transform.m[0] = 0.5, m[5] = 0.5, m[10] = 0.5
    assert_float_eq(w.objects[1].object.sp.transform.m[0], 0.5f,
                    "Second sphere has scale 0.5 on X");
    assert_float_eq(w.objects[1].object.sp.transform.m[5], 0.5f,
                    "Second sphere has scale 0.5 on Y");
    assert_float_eq(w.objects[1].object.sp.transform.m[10], 0.5f,
                    "Second sphere has scale 0.5 on Z");
}

/* ************************************************************************** */
/* MAIN                                     */
/* ************************************************************************** */

int main(void)
{
	printf("===============================================================\n");
	printf("                MINIRT SCENE UTILS TESTER                    \n");
	printf("===============================================================\n");

	
	test_default_world();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");
	
	return (g_tests_passed != g_tests_run);
}