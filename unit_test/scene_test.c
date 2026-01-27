#include <stdio.h>
#include <math.h>
#include "canvas.h"
#include "vector.h"
#include "matrix.h"
#include "scene.h"
#include "ray.h"

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

void test_intersect_world(void)
{
    t_world     w;
    t_ray       r;
    t_intersect xs;

    printf("\n--- Intersecting a world with a ray ---\n");

    w = default_world();
    r = ray_constructor(point_constructor(0, 0, -5),
                        vector_constructor(0, 0, 1));
    xs = intersect_world(&w, r);

    assert_int_eq(xs.count, 4, "intersect_world returns 4 intersections");
    assert_float_eq(xs.i[0].t, 4.0f, "xs[0].t equals 4.0");
    assert_float_eq(xs.i[1].t, 4.5f, "xs[1].t equals 4.5");
    assert_float_eq(xs.i[2].t, 5.5f, "xs[2].t equals 5.5");
    assert_float_eq(xs.i[3].t, 6.0f, "xs[3].t equals 6.0");
}

void test_prepare_computations(void)
{
    t_ray           r;
    t_object        shape;
    t_intersection  i;
    t_computation   comps;

    printf("\n--- Precomputing the state of an intersection ---\n");

    r = ray_constructor(point_constructor(0, 0, -5),
                        vector_constructor(0, 0, 1));
    shape.sp = sphere();
    i = intersection(4.0f, shape);
    comps = prepare_computations(i, r);

    assert_float_eq(comps.t, i.t, "comps.t equals intersection t");
    assert_int_eq(comps.object.sp.id, i.object.sp.id,
                  "comps.object matches intersection object");
    assert_vec3_eq(comps.point, point_constructor(0, 0, -1),
                   "comps.point is correct");
    assert_vec3_eq(comps.eyev, vector_constructor(0, 0, -1),
                   "comps.eyev is correct");
    assert_vec3_eq(comps.normalv, vector_constructor(0, 0, -1),
                   "comps.normalv is correct");
}

void test_prepare_computations_outside(void)
{
    t_ray           r;
    t_object        shape;
    t_intersection  i;
    t_computation   comps;

    printf("\n--- The hit, when an intersection occurs on the outside ---\n");

    r = ray_constructor(point_constructor(0, 0, -5),
                        vector_constructor(0, 0, 1));
    shape.sp = sphere();
    i = intersection(4.0f, shape);
    comps = prepare_computations(i, r);

    assert_bool_eq(comps.inside, false, "comps.inside is false");
}

void test_prepare_computations_inside(void)
{
    t_ray           r;
    t_object        shape;
    t_intersection  i;
    t_computation   comps;

    printf("\n--- The hit, when an intersection occurs on the inside ---\n");

    r = ray_constructor(point_constructor(0, 0, 0),
                        vector_constructor(0, 0, 1));
    shape.sp = sphere();
    i = intersection(1.0f, shape);
    comps = prepare_computations(i, r);

    assert_vec3_eq(comps.point, point_constructor(0, 0, 1),
                   "comps.point is correct");
    assert_vec3_eq(comps.eyev, vector_constructor(0, 0, -1),
                   "comps.eyev is correct");
    assert_bool_eq(comps.inside, true, "comps.inside is true");
    assert_vec3_eq(comps.normalv, vector_constructor(0, 0, -1),
                   "comps.normalv is inverted");
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
    test_intersect_world();
    test_prepare_computations();
    test_prepare_computations_outside();
    test_prepare_computations_inside();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");
	
	return (g_tests_passed != g_tests_run);
}