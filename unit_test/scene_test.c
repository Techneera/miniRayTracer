#include <stdio.h>
#include <math.h>
#include "canvas.h"
#include "mlx.h"
#include "shades.h"
#include "vector.h"
#include "matrix.h"
#include "scene.h"
#include "ray.h"
#include "librt.h"

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

static t_uint	pixel_at(t_canvas *c, int x, int y)
{
	char	*dest;

	dest = c->img.addr + (y * c->img.line_len + x * (c->img.bpp / 8));
	return (*(t_uint *)dest);
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

void test_shade_hit(void)
{
    t_world         w;
    t_ray           r;
    t_object        shape;
    t_intersection  i;
    t_computation   comps;
    t_vec3          c;
    t_vec3          expected;

    printf("\n--- Shading an intersection ---\n");

    w = default_world();
    r = ray_constructor(point_constructor(0, 0, -5),
                        vector_constructor(0, 0, 1));
    shape = w.objects[0].object;
    i = intersection(4.0f, shape);
    comps = prepare_computations(i, r);
    c = shade_hit(w, comps);
    expected = color_constructor(0.38066, 0.47583, 0.2855);

    assert_vec3_eq(c, expected, "Shaded color is correct");
}

void test_shade_hit_inside(void)
{
    t_world         w;
    t_ray           r;
    t_object        shape;
    t_intersection  i;
    t_computation   comps;
    t_vec3          c;
    t_vec3          expected;

    printf("\n--- Shading an intersection from the inside ---\n");

    w = default_world();
    w.light = point_light(point_constructor(0, 0.25, 0),
                          color_constructor(1, 1, 1));
    r = ray_constructor(point_constructor(0, 0, 0),
                        vector_constructor(0, 0, 1));
    shape = w.objects[1].object;
    i = intersection(0.5f, shape);
    comps = prepare_computations(i, r);
    c = shade_hit(w, comps);
    expected = color_constructor(0.90498, 0.90498, 0.90498);

    assert_vec3_eq(c, expected, "Shaded color from inside is correct");
}

void test_color_when_ray_misses(void)
{
    t_world         w;
    t_ray           r;
    t_vec3          c;
    t_vec3          expected;

    printf("\n--- The color when a ray misses ---\n");

    w = default_world();
    r = ray_constructor(point_constructor(0, 0, -5),
                        vector_constructor(0, 1, 0));
    c = color_at(w, r);
    expected = color_constructor(0, 0, 0);

    assert_vec3_eq(c, expected, "Color when ray misses is black");
}

void test_color_when_ray_hits(void)
{
    t_world         w;
    t_ray           r;
    t_vec3          c;
    t_vec3          expected;

    printf("\n--- The color when a ray hits ---\n");

    w = default_world();
    r = ray_constructor(point_constructor(0, 0, -5),
                        vector_constructor(0, 0, 1));
    c = color_at(w, r);
    expected = color_constructor(0.38066, 0.47583, 0.2855);

    assert_vec3_eq(c, expected, "Color when ray hits is correct");
}

void test_color_with_intersection_behind_ray(void)
{
    t_world         w;
    t_ray           r;
    t_vec3          c;

    printf("\n--- The color with an intersection behind the ray ---\n");

    w = default_world();
    w.objects[0].object.sp.material.ambient = 1.0f;
    w.objects[1].object.sp.material.ambient = 1.0f;
    r = ray_constructor(point_constructor(0, 0, 0.75),
                        vector_constructor(0, 0, -1));
    c = color_at(w, r);

    assert_vec3_eq(c, w.objects[1].object.sp.material.color,
                   "Color matches inner object material color");
}

void test_view_transform_default_orientation(void)
{
    t_vec3      from;
    t_vec3      to;
    t_vec3      up;
    t_mat4    t;
    t_mat4    identity;
    int         i;

    printf("\n--- The transformation matrix for the default orientation ---\n");

    from = point_constructor(0, 0, 0);
    to = point_constructor(0, 0, -1);
    up = vector_constructor(0, 1, 0);
    t = view_transform(from, to, up);
    matrix_identity(&identity);

    i = 0;
    while (i < 16)
    {
        assert_float_eq(t.m[i], identity.m[i],
                        "View transform matches identity matrix");
        i++;
    }
}

void test_view_transform_positive_z(void)
{
    t_vec3      from;
    t_vec3      to;
    t_vec3      up;
    t_mat4      t;
    t_mat4      expected;
    int         i;

    printf("\n--- A view transformation matrix looking in positive z direction ---\n");

    from = point_constructor(0, 0, 0);
    to = point_constructor(0, 0, 1);
    up = vector_constructor(0, 1, 0);
    t = view_transform(from, to, up);
    expected = matrix_scale(-1, 1, -1);

    i = 0;
    while (i < 16)
    {
        assert_float_eq(t.m[i], expected.m[i],
                        "View transform looking in +Z equals scaling(-1, 1, -1)");
        i++;
    }
}

void test_view_transform_moves_world(void)
{
    t_vec3      from;
    t_vec3      to;
    t_vec3      up;
    t_mat4      t;
    t_mat4      expected;
    int         i;

    printf("\n--- The view transformation moves the world ---\n");

    from = point_constructor(0, 0, 8);
    to = point_constructor(0, 0, 0);
    up = vector_constructor(0, 1, 0);
    t = view_transform(from, to, up);
    expected = matrix_translation(0, 0, -8);

    i = 0;
    while (i < 16)
    {
        assert_float_eq(t.m[i], expected.m[i],
                        "View transform equals translation(0, 0, -8)");
        i++;
    }
}

void test_view_transform_arbitrary(void)
{
    t_vec3      from;
    t_vec3      to;
    t_vec3      up;
    t_mat4      t;
    t_mat4      expected;

    printf("\n--- An arbitrary view transformation ---\n");

    from = point_constructor(1, 3, 2);
    to = point_constructor(4, -2, 8);
    up = vector_constructor(1, 1, 0);
    t = view_transform(from, to, up);
    
    expected = (t_mat4){
        .m = {
            -0.50709f, 0.50709f,  0.67612f, -2.36643f,
             0.76772f, 0.60609f,  0.12122f, -2.82843f,
            -0.35857f, 0.59761f, -0.71714f,  0.00000f,
             0.00000f, 0.00000f,  0.00000f,  1.00000f
        }
    };

    assert_float_eq(t.m[0], expected.m[0], "Matrix[0,0] matches");
    assert_float_eq(t.m[1], expected.m[1], "Matrix[0,1] matches");
    assert_float_eq(t.m[2], expected.m[2], "Matrix[0,2] matches");
    assert_float_eq(t.m[3], expected.m[3], "Matrix[0,3] matches");
    assert_float_eq(t.m[4], expected.m[4], "Matrix[1,0] matches");
    assert_float_eq(t.m[5], expected.m[5], "Matrix[1,1] matches");
    assert_float_eq(t.m[6], expected.m[6], "Matrix[1,2] matches");
    assert_float_eq(t.m[7], expected.m[7], "Matrix[1,3] matches");
    assert_float_eq(t.m[8], expected.m[8], "Matrix[2,0] matches");
    assert_float_eq(t.m[9], expected.m[9], "Matrix[2,1] matches");
    assert_float_eq(t.m[10], expected.m[10], "Matrix[2,2] matches");
    assert_float_eq(t.m[11], expected.m[11], "Matrix[2,3] matches");
    assert_float_eq(t.m[12], expected.m[12], "Matrix[3,0] matches");
    assert_float_eq(t.m[13], expected.m[13], "Matrix[3,1] matches");
    assert_float_eq(t.m[14], expected.m[14], "Matrix[3,2] matches");
    assert_float_eq(t.m[15], expected.m[15], "Matrix[3,3] matches");
}

void test_camera_constructor(void)
{
    t_camera    c;
    t_mat4      identity;
    int         i;

    printf("\n--- Constructing a camera ---\n");

    c = camera_constructor(160, 120, M_PI / 2);
    matrix_identity(&identity);

    assert_int_eq(c.hsize, 160, "Camera hsize equals 160");
    assert_int_eq(c.vsize, 120, "Camera vsize equals 120");
    assert_float_eq(c.field_of_view, M_PI / 2, "Camera field_of_view equals π/2");
    
    i = 0;
    while (i < 16)
    {
        assert_float_eq(c.transform.m[i], identity.m[i],
                        "Camera transform is identity matrix");
        i++;
    }
}

void test_pixel_size_horizontal_canvas(void)
{
    t_camera    c;

    printf("\n--- The pixel size for a horizontal canvas ---\n");

    c = camera_constructor(200, 125, M_PI / 2);
    assert_float_eq(c.pixel_size, 0.01f, "Pixel size equals 0.01");
}

void test_pixel_size_vertical_canvas(void)
{
    t_camera    c;

    printf("\n--- The pixel size for a vertical canvas ---\n");

    c = camera_constructor(125, 200, M_PI / 2);
    assert_float_eq(c.pixel_size, 0.01f, "Pixel size equals 0.01");
}

void test_ray_through_canvas_center(void)
{
    t_camera    c;
    t_ray       r;

    printf("\n--- Constructing a ray through the center of the canvas ---\n");

    c = camera_constructor(201, 101, M_PI / 2);
    r = ray_for_pixel(c, 100, 50);

    assert_vec3_eq(r.origin, point_constructor(0, 0, 0),
                   "Ray origin is point(0, 0, 0)");
    assert_vec3_eq(r.direction, vector_constructor(0, 0, -1),
                   "Ray direction is vector(0, 0, -1)");
}

void test_ray_through_canvas_corner(void)
{
    t_camera    c;
    t_ray       r;

    printf("\n--- Constructing a ray through a corner of the canvas ---\n");

    c = camera_constructor(201, 101, M_PI / 2);
    r = ray_for_pixel(c, 0, 0);

    assert_vec3_eq(r.origin, point_constructor(0, 0, 0),
                   "Ray origin is point(0, 0, 0)");
    assert_vec3_eq(r.direction, vector_constructor(0.66519, 0.33259, -0.66851),
                   "Ray direction is vector(0.66519, 0.33259, -0.66851)");
}

void test_ray_with_transformed_camera(void)
{
    t_camera    c;
    t_ray       r;
    t_mat4      rotation;
    t_mat4      translation;

    printf("\n--- Constructing a ray when the camera is transformed ---\n");

    c = camera_constructor(201, 101, M_PI / 2);
    rotation = matrix_rot_y(M_PI / 4);
    translation = matrix_translation(0, -2, 5);
    c.transform = matrix_multiply(rotation, translation);
    r = ray_for_pixel(c, 100, 50);

    assert_vec3_eq(r.origin, point_constructor(0, 2, -5),
                   "Ray origin is point(0, 2, -5)");
    assert_vec3_eq(r.direction, vector_constructor(sqrtf(2) / 2, 0, -sqrtf(2) / 2),
                   "Ray direction is vector(√2/2, 0, -√2/2)");
}

void test_render_world_with_camera(void)
{
    t_world     w;
    t_camera    c;
    t_canvas    image;
    t_vec3      from;
    t_vec3      to;
    t_vec3      up;
    t_uint      color;
    t_uint      expected;

    printf("\n--- Rendering a world with a camera ---\n");

    w = default_world();
    c = camera_constructor(11, 11, M_PI / 2);
    from = point_constructor(0, 0, -5);
    to = point_constructor(0, 0, 0);
    up = vector_constructor(0, 1, 0);
    c.transform = view_transform(from, to, up);
    image = render(c, w);
    color = pixel_at(&image, 5, 5);
    expected = color_to_int(color_constructor(0.38066, 0.47583, 0.2855));

    assert_int_eq(color, expected, "Pixel at (5, 5) is color(0.38066, 0.47583, 0.2855)");
}
void    test_example_scene(void) {
    t_world     world;
    t_camera    camera;
    t_canvas    canvas;
    void        *win;
    t_object    floor, left_wall, right_wall, middle, right, left;
    t_mat4      transform;

    // Initialize world
    world.object_count = 0;
    world.light = point_light(
        point_constructor(-10, 10, -10),
        color_constructor(1, 1, 1)
    );

    // Floor - flattened sphere
    floor.sp = sphere();
    sphere_set_transform(&floor.sp, matrix_scale(10, 0.01, 10));
    floor.sp.material.color = color_constructor(1, 0.9, 0.9);
    floor.sp.material.specular = 0;
    world.objects[world.object_count].object = floor;
    world.objects[world.object_count++].type = SPHERE;

    // Left wall - sphere scaled, rotated, and translated
    left_wall.sp = sphere();
    transform = matrix_multiply(
        matrix_translation(0, 0, 5),
        matrix_multiply(
            matrix_rot_y(-M_PI / 4),
            matrix_multiply(
                matrix_rot_x(M_PI / 2),
                matrix_scale(10, 0.01, 10)
            )
        )
    );
    sphere_set_transform(&left_wall.sp, transform);
    left_wall.sp.material = floor.sp.material;
    world.objects[world.object_count].object = left_wall;
    world.objects[world.object_count++].type = SPHERE;

    // Right wall - sphere scaled, rotated opposite direction, and translated
    right_wall.sp = sphere();
    transform = matrix_multiply(
        matrix_translation(0, 0, 5),
        matrix_multiply(
            matrix_rot_y(M_PI / 4),
            matrix_multiply(
                matrix_rot_x(M_PI / 2),
                matrix_scale(10, 0.01, 10)
            )
        )
    );
    sphere_set_transform(&right_wall.sp, transform);
    right_wall.sp.material = floor.sp.material;
    world.objects[world.object_count].object = right_wall;
    world.objects[world.object_count++].type = SPHERE;

    // Middle sphere - large green sphere
    middle.sp = sphere();
    sphere_set_transform(&middle.sp, matrix_translation(-0.5, 1, 0.5));
    middle.sp.material.color = color_constructor(0.1, 1, 0.5);
    middle.sp.material.diffuse = 0.7;
    middle.sp.material.specular = 0.3;
    world.objects[world.object_count].object = middle;
    world.objects[world.object_count++].type = SPHERE;

    // Right sphere - smaller green sphere
    right.sp = sphere();
    transform = matrix_multiply(
        matrix_translation(1.5, 0.5, -0.5),
        matrix_scale(0.5, 0.5, 0.5)
    );
    sphere_set_transform(&right.sp, transform);
    right.sp.material.color = color_constructor(0.5, 1, 0.1);
    right.sp.material.diffuse = 0.7;
    right.sp.material.specular = 0.3;
    world.objects[world.object_count].object = right;
    world.objects[world.object_count++].type = SPHERE;

    // Left sphere - smallest sphere (yellow)
    left.sp = sphere();
    transform = matrix_multiply(
        matrix_translation(-1.5, 0.33, -0.75),
        matrix_scale(0.33, 0.33, 0.33)
    );
    sphere_set_transform(&left.sp, transform);
    left.sp.material.color = color_constructor(1, 0.8, 0.1);
    left.sp.material.diffuse = 0.7;
    left.sp.material.specular = 0.3;
    world.objects[world.object_count].object = left;
    world.objects[world.object_count++].type = SPHERE;

    // Camera setup
    camera = camera_constructor(800, 800, M_PI / 3);
    camera.transform = view_transform(
        point_constructor(0, 1.5, -5),
        point_constructor(0, 1, 0),
        vector_constructor(0, 1, 0)
    );

    // Render and display
    printf("\n--- Rendering 800x800 scene (this will take a moment) ---\n");
    canvas = render(camera, world);
    win = mlx_new_window(canvas.mlx, canvas.width, canvas.height, "miniRT - Example Scene");
    mlx_put_image_to_window(canvas.mlx, win, canvas.img.img, 0, 0);
    mlx_key_hook(win, key_hook, &canvas);
    mlx_loop(canvas.mlx);
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
    test_shade_hit();
    test_shade_hit_inside();
    test_color_when_ray_misses();
    test_color_when_ray_hits();
    test_color_with_intersection_behind_ray();
    test_view_transform_default_orientation();
    test_view_transform_positive_z();
    test_view_transform_moves_world();
    test_view_transform_arbitrary();
    test_camera_constructor();
    test_pixel_size_horizontal_canvas();
    test_pixel_size_vertical_canvas();
    test_ray_through_canvas_center();
    test_ray_through_canvas_corner();
    test_ray_with_transformed_camera();
    test_render_world_with_camera();
    //addtest_example_scene();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");
	
	return (g_tests_passed != g_tests_run);
}
