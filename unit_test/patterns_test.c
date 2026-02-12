#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "canvas.h"
#include "patterns.h"
#include "vector.h"
#include "shades.h"

#define EPSILON 0.00001
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

static int g_tests_run = 0;
static int g_tests_passed = 0;

// Color constants
static t_vec3 black;
static t_vec3 white;

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

void test_creating_stripe_pattern(void)
{
    t_pattern pattern;

    printf("\n--- Creating a stripe pattern ---\n");

    // Given pattern ← stripe_pattern(white, black)
    pattern = pattern_stripe(white, black);
    
    // Then pattern.a = white
    assert_vec3_eq(pattern.a, white, "pattern.a should equal white");
    
    // And pattern.b = black
    assert_vec3_eq(pattern.b, black, "pattern.b should equal black");
}

void test_stripe_pattern_constant_in_y(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- A stripe pattern is constant in y ---\n");

    // Given pattern ← stripe_pattern(white, black)
    pattern = pattern_stripe(white, black);
    
    // Then stripe_at(pattern, point(0, 0, 0)) = white
    result = stripe_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0, 0, 0)) should equal white");
    
    // And stripe_at(pattern, point(0, 1, 0)) = white
    result = stripe_at(pattern, point_constructor(0, 1, 0));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0, 1, 0)) should equal white");
    
    // And stripe_at(pattern, point(0, 2, 0)) = white
    result = stripe_at(pattern, point_constructor(0, 2, 0));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0, 2, 0)) should equal white");
}

void test_stripe_pattern_constant_in_z(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- A stripe pattern is constant in z ---\n");

    // Given pattern ← stripe_pattern(white, black)
    pattern = pattern_stripe(white, black);
    
    // Then stripe_at(pattern, point(0, 0, 0)) = white
    result = stripe_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0, 0, 0)) should equal white");
    
    // And stripe_at(pattern, point(0, 0, 1)) = white
    result = stripe_at(pattern, point_constructor(0, 0, 1));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0, 0, 1)) should equal white");
    
    // And stripe_at(pattern, point(0, 0, 2)) = white
    result = stripe_at(pattern, point_constructor(0, 0, 2));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0, 0, 2)) should equal white");
}

void test_stripe_pattern_alternates_in_x(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- A stripe pattern alternates in x ---\n");

    // Given pattern ← stripe_pattern(white, black)
    pattern = pattern_stripe(white, black);
    
    // Then stripe_at(pattern, point(0, 0, 0)) = white
    result = stripe_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0, 0, 0)) should equal white");
    
    // And stripe_at(pattern, point(0.9, 0, 0)) = white
    result = stripe_at(pattern, point_constructor(0.9, 0, 0));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(0.9, 0, 0)) should equal white");
    
    // And stripe_at(pattern, point(1, 0, 0)) = black
    result = stripe_at(pattern, point_constructor(1, 0, 0));
    assert_vec3_eq(result, black, "stripe_at(pattern, point(1, 0, 0)) should equal black");
    
    // And stripe_at(pattern, point(-0.1, 0, 0)) = black
    result = stripe_at(pattern, point_constructor(-0.1, 0, 0));
    assert_vec3_eq(result, black, "stripe_at(pattern, point(-0.1, 0, 0)) should equal black");
    
    // And stripe_at(pattern, point(-1, 0, 0)) = black
    result = stripe_at(pattern, point_constructor(-1, 0, 0));
    assert_vec3_eq(result, black, "stripe_at(pattern, point(-1, 0, 0)) should equal black");
    
    // And stripe_at(pattern, point(-1.1, 0, 0)) = white
    result = stripe_at(pattern, point_constructor(-1.1, 0, 0));
    assert_vec3_eq(result, white, "stripe_at(pattern, point(-1.1, 0, 0)) should equal white");
}

void test_lighting_with_pattern_applied(void)
{
    t_material m;
    t_vec3 eyev;
    t_vec3 normalv;
    t_point_light light;
    t_vec3 c1;
    t_vec3 c2;

    printf("\n--- Lighting with a pattern applied ---\n");

    // Given m.pattern ← stripe_pattern(color(1, 1, 1), color(0, 0, 0))
    m = material_default();
    m.pattern = pattern_stripe(color_constructor(1, 1, 1), color_constructor(0, 0, 0));
    
    // And m.ambient ← 1
    m.ambient = 1;
    
    // And m.diffuse ← 0
    m.diffuse = 0;
    
    // And m.specular ← 0
    m.specular = 0;
    
    // And eyev ← vector(0, 0, -1)
    eyev = vector_constructor(0, 0, -1);
    
    // And normalv ← vector(0, 0, -1)
    normalv = vector_constructor(0, 0, -1);
    
    // And light ← point_light(point(0, 0, -10), color(1, 1, 1))
    light = point_light(point_constructor(0, 0, -10), color_constructor(1, 1, 1));
    
    // When c1 ← lighting(m, light, point(0.9, 0, 0), eyev, normalv, false)
    c1 = lighting(m, light, point_constructor(0.9, 0, 0), eyev, normalv, false);
    
    // And c2 ← lighting(m, light, point(1.1, 0, 0), eyev, normalv, false)
    c2 = lighting(m, light, point_constructor(1.1, 0, 0), eyev, normalv, false);
    
    // Then c1 = color(1, 1, 1)
    assert_vec3_eq(c1, color_constructor(1, 1, 1), "c1 should equal white (1, 1, 1)");
    
    // And c2 = color(0, 0, 0)
    assert_vec3_eq(c2, color_constructor(0, 0, 0), "c2 should equal black (0, 0, 0)");
}

int main(void)
{
    printf("==========================================\n");
    printf("         PATTERNS UNIT TESTS\n");
    printf("==========================================\n");

    // Initialize color constants
    black = color_constructor(0, 0, 0);
    white = color_constructor(1, 1, 1);

    // Run tests
    test_creating_stripe_pattern();
    test_stripe_pattern_constant_in_y();
    test_stripe_pattern_constant_in_z();
    test_stripe_pattern_alternates_in_x();
    test_lighting_with_pattern_applied();

    printf("\n==========================================\n");
    if (g_tests_passed == g_tests_run)
        printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
    else
        printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
    printf("==========================================\n");
    
    return (g_tests_passed != g_tests_run);
}