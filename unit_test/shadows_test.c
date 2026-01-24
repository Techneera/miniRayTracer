#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "canvas.h"
#include "vector.h"
#include "shades.h"

#define EPSILON 0.00001
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

static int g_tests_run = 0;
static int g_tests_passed = 0;

static bool assert_float_eq(float actual, float expected, const char *msg)
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

void test_lighting_with_surface_in_shadow(void)
{
    t_material      m;
    t_point_light   light;
    t_vec3          position;
    t_vec3          eyev;
    t_vec3          normalv;
    t_vec3          result;
    bool            in_shadow;

    printf("\n--- Lighting with the surface in shadow ---\n");

    // Setup: Material with default values
    m = new_material(0.1, 0.9, 0.9, 200.0);
    m.color = color_constructor(1, 1, 1);
    
    // Position at origin
    position = point_constructor(0, 0, 0);
    
    // Eye vector pointing back along z-axis
    eyev = vector_constructor(0, 0, -1);
    
    // Normal vector pointing back along z-axis
    normalv = vector_constructor(0, 0, -1);
    
    // Light behind the eye
    light = point_light(point_constructor(0, 0, -10), 
                        color_constructor(1, 1, 1));
    
    // Surface is in shadow
    in_shadow = true;
    
    // When: Calculate lighting
    result = lighting(m, light, position, eyev, normalv, in_shadow);
    
    // Then: Result should be only ambient component (0.1, 0.1, 0.1)
    assert_float_eq(result.x, 0.1f, "Lighting in shadow - Red component");
    assert_float_eq(result.y, 0.1f, "Lighting in shadow - Green component");
    assert_float_eq(result.z, 0.1f, "Lighting in shadow - Blue component");
}

/* ************************************************************************** */
/* MAIN                                     */
/* ************************************************************************** */

int main(void)
{
	printf("===============================================================\n");
	printf("                MINIRT SHADOWS UTILS TESTER                    \n");
	printf("===============================================================\n");

	test_lighting_with_surface_in_shadow();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");
	
	return (g_tests_passed != g_tests_run);
}
