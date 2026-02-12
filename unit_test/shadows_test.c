#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "canvas.h"
#include "vector.h"
#include "shades.h"
#include "scene.h"
#include "shadows.h"
#include "ray.h"
#include "matrix.h"

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

static bool assert_bool_eq(bool actual, bool expected, const char *msg)
{
    g_tests_run++;
    if (actual == expected)
    {
        g_tests_passed++;
        printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
        return (true);
    }
    printf("%s[FAIL]%s %s (Exp: %d, Got: %d)\n",
        RED, RESET, msg, expected, actual);
    return (false);
}

static bool assert_vec3_eq(t_vec3 actual, t_vec3 expected, const char *msg)
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
    m = new_material(0.1, 0.9, 0.9, 200.0, 0.0);
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

void test_shadow_when_nothing_collinear(void)
{
    t_world	w;
    t_vec3	p;
    bool	shadowed;

    printf("\n--- There is no shadow when nothing is collinear ---\n");

    w = default_world();
    p = point_constructor(0, 10, 0);
    shadowed = is_shadowed(w, p);

    assert_bool_eq(shadowed, false,
        "No shadow when nothing is collinear with point and light");
}

void test_shadow_when_object_between_point_and_light(void)
{
    t_world	w;
    t_vec3	p;
    bool	shadowed;

    printf("\n--- The shadow when an object is between the point and the light ---\n");

    w = default_world();
    p = point_constructor(10, -10, 10);
    shadowed = is_shadowed(w, p);

    assert_bool_eq(shadowed, true,
        "Shadow when object is between point and light");
}

void test_shadow_when_object_behind_light(void)
{
    t_world	w;
    t_vec3	p;
    bool	shadowed;

    printf("\n--- There is no shadow when an object is behind the light ---\n");

    w = default_world();
    p = point_constructor(-20, 20, -20);
    shadowed = is_shadowed(w, p);

    assert_bool_eq(shadowed, false,
        "No shadow when object is behind the light");
}

void test_shadow_when_object_behind_point(void)
{
    t_world	w;
    t_vec3	p;
    bool	shadowed;

    printf("\n--- There is no shadow when an object is behind the point ---\n");

    w = default_world();
    p = point_constructor(-2, 2, -2);
    shadowed = is_shadowed(w, p);

    assert_bool_eq(shadowed, false,
        "No shadow when object is behind the point");
}

void test_shade_hit_in_shadow(void)
{
    t_world         w;
    t_object        s1;
    t_object        s2;
    t_ray           r;
    t_intersection  i;
    t_computation   comps;
    t_vec3          c;
    t_vec3          expected;

    printf("\n--- shade_hit() is given an intersection in shadow ---\n");

    // Given: world with light at (0, 0, -10)
    w.object_count = 0;
    w.light = point_light(point_constructor(0, 0, -10),
                          color_constructor(1, 1, 1));

    // And: s1 is added to w (default sphere at origin)
    s1.sp = sphere();
    w.objects[w.object_count].object = s1;
    w.objects[w.object_count++].type = SPHERE;

    // And: s2 with translation(0, 0, 10) added to w
    s2.sp = sphere();
    sphere_set_transform(&s2.sp, matrix_translation(0, 0, 10));
    w.objects[w.object_count].object = s2;
    w.objects[w.object_count++].type = SPHERE;

    // And: ray from (0, 0, 5) in direction (0, 0, 1)
    r = ray_constructor(point_constructor(0, 0, 5),
                        vector_constructor(0, 0, 1));

    // And: intersection at t=4 with s2
    i = intersection(4.0f, s2);

    // When: prepare computations
    comps = prepare_computations(i, r);

    // And: shade_hit
    c = shade_hit(w, comps);

    // Then: result should be ambient only (0.1, 0.1, 0.1)
    expected = color_constructor(0.1, 0.1, 0.1);
    assert_vec3_eq(c, expected, "shade_hit in shadow returns ambient color");
}

void test_hit_offset_point(void)
{
    t_ray           r;
    t_object        shape;
    t_intersection  i;
    t_computation   comps;

    printf("\n--- The hit should offset the point ---\n");

    // Given: ray from (0, 0, -5) in direction (0, 0, 1)
    r = ray_constructor(point_constructor(0, 0, -5),
                        vector_constructor(0, 0, 1));

    // And: sphere with translation(0, 0, 1)
    shape.sp = sphere();
    sphere_set_transform(&shape.sp, matrix_translation(0, 0, 1));

    // And: intersection at t=5
    i = intersection(5.0f, shape);

    // When: prepare computations
    comps = prepare_computations(i, r);

    // Then: over_point.z < -EPSILON/2
    assert_float_eq(comps.over_point.z < -EPSILON / 2 ? 1.0f : 0.0f, 1.0f,
                    "over_point.z is offset below surface");

    // And: point.z > over_point.z
    assert_float_eq(comps.point.z > comps.over_point.z ? 1.0f : 0.0f, 1.0f,
                    "point is farther from eye than over_point");
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
    test_shadow_when_nothing_collinear();
    test_shadow_when_object_between_point_and_light();
    test_shadow_when_object_behind_light();
    test_shadow_when_object_behind_point();
    test_shade_hit_in_shadow();
    test_hit_offset_point();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");
	
	return (g_tests_passed != g_tests_run);
}
