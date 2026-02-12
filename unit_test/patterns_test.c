#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "canvas.h"
#include "patterns.h"
#include "ray.h"
#include "vector.h"
#include "shades.h"
#include "matrix.h"

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

static bool assert_matrix_eq(t_mat4 actual, t_mat4 expected, const char *msg)
{
    int i;
    
    g_tests_run++;
    for (i = 0; i < 16; i++)
    {
        if (fabs(actual.m[i] - expected.m[i]) > EPSILON)
        {
            printf("%s[FAIL]%s %s\n", RED, RESET, msg);
            printf("\tMatrix mismatch at index %d: expected %.3f, got %.3f\n", i, expected.m[i], actual.m[i]);
            return (false);
        }
    }
    g_tests_passed++;
    printf("%s[PASS]%s %s\n", GREEN, RESET, msg);
    return (true);
}

// Test pattern that returns the coordinates as color for testing transformations
t_pattern test_pattern(void)
{
    return (pattern_constructor(PATTERN_SOLID, color_constructor(0, 0, 0), color_constructor(1, 1, 1)));
}

// Test pattern evaluation function that returns coordinates as color
t_vec3 test_pattern_at(t_pattern pattern, t_vec3 point)
{
    (void)pattern; // Suppress unused warning
    return (color_constructor(point.x, point.y, point.z));
}

// Pattern at shape function for test pattern
t_vec3 pattern_at_shape(t_pattern pattern, t_shape shape, t_vec3 world_point)
{
    t_vec3 object_point;
    t_vec3 pattern_point;
    
    // Transform world point to object space
    object_point = matrix_vector_multiply(matrix_inverse(shape.transform), world_point);
    
    // Transform object point to pattern space  
    pattern_point = matrix_vector_multiply(matrix_inverse(pattern.transform), object_point);
    
    // For test pattern, return the pattern point as color
    return (test_pattern_at(pattern, pattern_point));
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

    t_object object = {0};
    object.sp = sphere();

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
    c1 = lighting(m, light, point_constructor(0.9, 0, 0), eyev, normalv, false, object.sp.shape);
    
    // And c2 ← lighting(m, light, point(1.1, 0, 0), eyev, normalv, false)
    c2 = lighting(m, light, point_constructor(1.1, 0, 0), eyev, normalv, false, object.sp.shape);
    
    // Then c1 = color(1, 1, 1)
    assert_vec3_eq(c1, color_constructor(1, 1, 1), "c1 should equal white (1, 1, 1)");
    
    // And c2 = color(0, 0, 0)
    assert_vec3_eq(c2, color_constructor(0, 0, 0), "c2 should equal black (0, 0, 0)");
}

void test_stripes_with_object_transformation(void)
{
    t_object object;
    t_pattern pattern;
    t_vec3 c;

    printf("\n--- Stripes with an object transformation ---\n");

    // Given object ← sphere()
    object.sp = sphere();
    
    // And set_transform(object, scaling(2, 2, 2))
    set_transform(&object.sp.shape, matrix_scale(2, 2, 2));
    
    // And pattern ← stripe_pattern(white, black)
    pattern = pattern_stripe(white, black);
    
    // When c ← pattern_at_object(pattern, object, point(1.5, 0, 0))
    c = pattern_at_object(pattern, object.sp.shape, point_constructor(1.5, 0, 0));
    
    // Then c = white
    assert_vec3_eq(c, white, "pattern_at_object should return white with object scaling");
}

void test_stripes_with_pattern_transformation(void)
{
    t_object object;
    t_pattern pattern;
    t_vec3 c;

    printf("\n--- Stripes with a pattern transformation ---\n");

    // Given object ← sphere()
    object.sp = sphere();
    
    // And pattern ← stripe_pattern(white, black)
    pattern = pattern_stripe(white, black);
    
    // And set_pattern_transform(pattern, scaling(2, 2, 2))
    set_pattern_transform(&pattern, matrix_scale(2, 2, 2));
    
    // When c ← pattern_at_object(pattern, object, point(1.5, 0, 0))
    c = pattern_at_object(pattern, object.sp.shape, point_constructor(1.5, 0, 0));
    
    // Then c = white
    assert_vec3_eq(c, white, "pattern_at_object should return white with pattern scaling");
}

void test_stripes_with_both_transformations(void)
{
    t_object object;
    t_pattern pattern;
    t_vec3 c;

    printf("\n--- Stripes with both an object and a pattern transformation ---\n");

    // Given object ← sphere()
    object.sp = sphere();
    
    // And set_transform(object, scaling(2, 2, 2))
    set_transform(&object.sp.shape, matrix_scale(2, 2, 2));
    
    // And pattern ← stripe_pattern(white, black)
    pattern = pattern_stripe(white, black);
    
    // And set_pattern_transform(pattern, translation(0.5, 0, 0))
    set_pattern_transform(&pattern, matrix_translation(0.5, 0, 0));
    
    // When c ← pattern_at_object(pattern, object, point(1.5, 0, 0))
    c = pattern_at_object(pattern, object.sp.shape, point_constructor(1.5, 0, 0));
    
    // Then c = white
    assert_vec3_eq(c, white, "pattern_at_object should return white with both transformations");
}

void test_default_pattern_transformation(void)
{
    t_pattern pattern;
    t_mat4 identity;

    printf("\n--- The default pattern transformation ---\n");

    // Given pattern ← test_pattern()
    pattern = test_pattern();
    
    // Create identity matrix for comparison
    matrix_identity(&identity);
    
    // Then pattern.transform = identity_matrix
    assert_matrix_eq(pattern.transform, identity, "pattern transform should be identity matrix");
}

void test_assigning_transformation(void)
{
    t_pattern pattern;
    t_mat4 translation;

    printf("\n--- Assigning a transformation ---\n");

    // Given pattern ← test_pattern()
    pattern = test_pattern();
    
    // When set_pattern_transform(pattern, translation(1, 2, 3))
    translation = matrix_translation(1, 2, 3);
    set_pattern_transform(&pattern, translation);
    
    // Then pattern.transform = translation(1, 2, 3)
    assert_matrix_eq(pattern.transform, translation, "pattern transform should be translation(1, 2, 3)");
}

void test_pattern_with_object_transformation(void)
{
    t_shape shape;
    t_pattern pattern;
    t_vec3 c;

    printf("\n--- A pattern with an object transformation ---\n");

    // Given shape ← sphere()
    shape = sphere().shape;
    
    // And set_transform(shape, scaling(2, 2, 2))
    set_transform(&shape, matrix_scale(2, 2, 2));
    
    // And pattern ← test_pattern()
    pattern = test_pattern();
    
    // When c ← pattern_at_shape(pattern, shape, point(2, 3, 4))
    c = pattern_at_object(pattern, shape, point_constructor(2, 3, 4));
    
    // Then c = color(1, 1.5, 2)
    assert_vec3_eq(c, color_constructor(1, 1.5, 2), "pattern_at_shape should return color(1, 1.5, 2) with object transformation");
}

void test_pattern_with_pattern_transformation(void)
{
    t_shape shape;
    t_pattern pattern;
    t_vec3 c;

    printf("\n--- A pattern with a pattern transformation ---\n");

    // Given shape ← sphere()
    shape = sphere().shape;
    
    // And pattern ← test_pattern()
    pattern = test_pattern();
    
    // And set_pattern_transform(pattern, scaling(2, 2, 2))
    set_pattern_transform(&pattern, matrix_scale(2, 2, 2));
    
    // When c ← pattern_at_shape(pattern, shape, point(2, 3, 4))
    c = pattern_at_object(pattern, shape, point_constructor(2, 3, 4));
    
    // Then c = color(1, 1.5, 2)
    assert_vec3_eq(c, color_constructor(1, 1.5, 2), "pattern_at_shape should return color(1, 1.5, 2) with pattern transformation");
}

void test_pattern_with_both_transformations(void)
{
    t_shape shape;
    t_pattern pattern;
    t_vec3 c;

    printf("\n--- A pattern with both an object and a pattern transformation ---\n");

    // Given shape ← sphere()
    shape = sphere().shape;
    
    // And set_transform(shape, scaling(2, 2, 2))
    set_transform(&shape, matrix_scale(2, 2, 2));
    
    // And pattern ← test_pattern()
    pattern = test_pattern();
    
    // And set_pattern_transform(pattern, translation(0.5, 1, 1.5))
    set_pattern_transform(&pattern, matrix_translation(0.5, 1, 1.5));
    
    // When c ← pattern_at_shape(pattern, shape, point(2.5, 3, 3.5))
    c = pattern_at_object(pattern, shape, point_constructor(2.5, 3, 3.5));
    
    // Then c = color(0.75, 0.5, 0.25)
    assert_vec3_eq(c, color_constructor(0.75, 0.5, 0.25), "pattern_at_shape should return correct color with both transformations");
}

void test_gradient_linear_interpolation(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- A gradient linearly interpolates between colors ---\n");

    // Given pattern ← gradient_pattern(white, black)
    pattern = pattern_gradient(white, black);
    
    // Then pattern_at(pattern, point(0, 0, 0)) = white
    result = gradient_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "gradient_at(pattern, point(0, 0, 0)) should equal white");
    
    // And pattern_at(pattern, point(0.25, 0, 0)) = color(0.75, 0.75, 0.75)
    result = gradient_at(pattern, point_constructor(0.25, 0, 0));
    assert_vec3_eq(result, color_constructor(0.75, 0.75, 0.75), "gradient_at(pattern, point(0.25, 0, 0)) should equal color(0.75, 0.75, 0.75)");
    
    // And pattern_at(pattern, point(0.5, 0, 0)) = color(0.5, 0.5, 0.5)
    result = gradient_at(pattern, point_constructor(0.5, 0, 0));
    assert_vec3_eq(result, color_constructor(0.5, 0.5, 0.5), "gradient_at(pattern, point(0.5, 0, 0)) should equal color(0.5, 0.5, 0.5)");
    
    // And pattern_at(pattern, point(0.75, 0, 0)) = color(0.25, 0.25, 0.25)
    result = gradient_at(pattern, point_constructor(0.75, 0, 0));
    assert_vec3_eq(result, color_constructor(0.25, 0.25, 0.25), "gradient_at(pattern, point(0.75, 0, 0)) should equal color(0.25, 0.25, 0.25)");
}

void test_ring_extends_in_x_and_z(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- A ring should extend in both x and z ---\n");

    // Given pattern ← ring_pattern(white, black)
    pattern = pattern_ring(white, black);
    
    // Then pattern_at(pattern, point(0, 0, 0)) = white
    result = ring_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "ring_at(pattern, point(0, 0, 0)) should equal white");
    
    // And pattern_at(pattern, point(1, 0, 0)) = black
    result = ring_at(pattern, point_constructor(1, 0, 0));
    assert_vec3_eq(result, black, "ring_at(pattern, point(1, 0, 0)) should equal black");
    
    // And pattern_at(pattern, point(0, 0, 1)) = black
    result = ring_at(pattern, point_constructor(0, 0, 1));
    assert_vec3_eq(result, black, "ring_at(pattern, point(0, 0, 1)) should equal black");
    
    // And pattern_at(pattern, point(0.708, 0, 0.708)) = black (0.708 = just slightly more than √2/2)
    result = ring_at(pattern, point_constructor(0.708, 0, 0.708));
    assert_vec3_eq(result, black, "ring_at(pattern, point(0.708, 0, 0.708)) should equal black");
}

void test_checkers_repeat_in_x(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- Checkers should repeat in x ---\n");

    // Given pattern ← checkers_pattern(white, black)
    pattern = pattern_checker(white, black);
    
    // Then pattern_at(pattern, point(0, 0, 0)) = white
    result = checker_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "checker_at(pattern, point(0, 0, 0)) should equal white");
    
    // And pattern_at(pattern, point(0.99, 0, 0)) = white
    result = checker_at(pattern, point_constructor(0.99, 0, 0));
    assert_vec3_eq(result, white, "checker_at(pattern, point(0.99, 0, 0)) should equal white");
    
    // And pattern_at(pattern, point(1.01, 0, 0)) = black
    result = checker_at(pattern, point_constructor(1.01, 0, 0));
    assert_vec3_eq(result, black, "checker_at(pattern, point(1.01, 0, 0)) should equal black");
}

void test_checkers_repeat_in_y(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- Checkers should repeat in y ---\n");

    // Given pattern ← checkers_pattern(white, black)
    pattern = pattern_checker(white, black);
    
    // Then pattern_at(pattern, point(0, 0, 0)) = white
    result = checker_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "checker_at(pattern, point(0, 0, 0)) should equal white");
    
    // And pattern_at(pattern, point(0, 0.99, 0)) = white
    result = checker_at(pattern, point_constructor(0, 0.99, 0));
    assert_vec3_eq(result, white, "checker_at(pattern, point(0, 0.99, 0)) should equal white");
    
    // And pattern_at(pattern, point(0, 1.01, 0)) = black
    result = checker_at(pattern, point_constructor(0, 1.01, 0));
    assert_vec3_eq(result, black, "checker_at(pattern, point(0, 1.01, 0)) should equal black");
}

void test_checkers_repeat_in_z(void)
{
    t_pattern pattern;
    t_vec3 result;

    printf("\n--- Checkers should repeat in z ---\n");

    // Given pattern ← checkers_pattern(white, black)
    pattern = pattern_checker(white, black);
    
    // Then pattern_at(pattern, point(0, 0, 0)) = white
    result = checker_at(pattern, point_constructor(0, 0, 0));
    assert_vec3_eq(result, white, "checker_at(pattern, point(0, 0, 0)) should equal white");
    
    // And pattern_at(pattern, point(0, 0, 0.99)) = white
    result = checker_at(pattern, point_constructor(0, 0, 0.99));
    assert_vec3_eq(result, white, "checker_at(pattern, point(0, 0, 0.99)) should equal white");
    
    // And pattern_at(pattern, point(0, 0, 1.01)) = black
    result = checker_at(pattern, point_constructor(0, 0, 1.01));
    assert_vec3_eq(result, black, "checker_at(pattern, point(0, 0, 1.01)) should equal black");
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
    test_stripes_with_object_transformation();
    test_stripes_with_pattern_transformation();
    test_stripes_with_both_transformations();
    test_default_pattern_transformation();
    test_assigning_transformation();
    test_pattern_with_object_transformation();
    test_pattern_with_pattern_transformation();
    test_pattern_with_both_transformations();
    test_gradient_linear_interpolation();
    test_ring_extends_in_x_and_z();
    test_checkers_repeat_in_x();
    test_checkers_repeat_in_y();
    test_checkers_repeat_in_z();

    printf("\n==========================================\n");
    if (g_tests_passed == g_tests_run)
        printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
    else
        printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
    printf("==========================================\n");
    
    return (g_tests_passed != g_tests_run);
}