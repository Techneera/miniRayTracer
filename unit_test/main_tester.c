#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "vector.h"
#include "canvas.h"
#include "ray.h"

#define EPSILON 0.00001
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

static int g_tests_run = 0;
static int g_tests_passed = 0;

/* ************************************************************************** */
/* HELPER FUNCTIONS                                                          */
/* ************************************************************************** */

static bool	vectors_equal(t_vec3 a, t_vec3 b, double epsilon)
{
	return (fabs(a.x - b.x) < epsilon && 
			fabs(a.y - b.y) < epsilon && 
			fabs(a.z - b.z) < epsilon);
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
	printf("\tExpected: %.5f\n\tActual: %.5f\n", expected, actual);
	return (false);
}

static bool	assert_int_eq(int actual, int expected, const char *msg)
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
	printf("\tExpected: (%.3f, %.3f, %.3f)\n", expected.x, expected.y, expected.z);
	printf("\tActual:   (%.3f, %.3f, %.3f)\n", actual.x, actual.y, actual.z);
	return (false);
}

static t_uint	get_pixel(t_canvas *c, int x, int y)
{
	char	*dest;

	dest = c->img.addr + (y * c->img.line_len + x * (c->img.bpp / 8));
	return (*(t_uint *)dest);
}

/* ************************************************************************** */
/* COLOR TESTS                                                                */
/* ************************************************************************** */

void	test_color_constructor(void)
{
	t_vec3	color;

	printf("\n--- Color constructor ---\n");

	color = color_constructor(-0.5, 0.4, 1.7);
	assert_float_eq(color.x, -0.5, "Color red channel");
	assert_float_eq(color.y, 0.4, "Color green channel");
	assert_float_eq(color.z, 1.7, "Color blue channel");
}

void	test_color_add(void)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	color;

	printf("\n--- Adding colors ---\n");

	u = color_constructor(0.9, 0.6, 0.75);
	v = color_constructor(0.7, 0.1, 0.25);
	color = color_add(u, v);
	assert_float_eq(color.x, 1.6, "Color add red");
	assert_float_eq(color.y, 0.7, "Color add green");
	assert_float_eq(color.z, 1.0, "Color add blue");
}

void	test_color_subtract(void)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	color;

	printf("\n--- Subtracting colors ---\n");

	u = color_constructor(0.9, 0.6, 0.75);
	v = color_constructor(0.7, 0.1, 0.25);
	color = color_subtract(u, v);
	assert_float_eq(color.x, 0.2, "Color subtract red");
	assert_float_eq(color.y, 0.5, "Color subtract green");
	assert_float_eq(color.z, 0.5, "Color subtract blue");
}

void	test_color_scalar(void)
{
	t_vec3	u;
	t_vec3	color;

	printf("\n--- Multiplying color by scalar ---\n");

	u = color_constructor(0.2, 0.3, 0.4);
	color = color_scalar(u, 2.0);
	assert_float_eq(color.x, 0.4, "Color scalar red");
	assert_float_eq(color.y, 0.6, "Color scalar green");
	assert_float_eq(color.z, 0.8, "Color scalar blue");
}

void	test_color_multiply(void)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	color;

	printf("\n--- Multiplying colors (Hadamard product) ---\n");

	u = color_constructor(1.0, 0.2, 0.4);
	v = color_constructor(0.9, 1.0, 0.1);
	color = color_multiply(u, v);
	assert_float_eq(color.x, 0.9, "Color multiply red");
	assert_float_eq(color.y, 0.2, "Color multiply green");
	assert_float_eq(color.z, 0.04, "Color multiply blue");
}

void	test_color_to_int(void)
{
	int		expected;
	t_vec3	color;
	int		result;

	printf("\n--- Converting color to integer ---\n");

	expected = 0x9eeb34;
	color = color_constructor(0.61960784313, 0.92156862745, 0.20392156862);
	result = color_to_int(color);
	assert_int_eq(result, expected, "Color to int conversion");
}

/* ************************************************************************** */
/* CANVAS TESTS                                                               */
/* ************************************************************************** */

void	test_canvas_constructor(void)
{
	t_canvas	canvas;

	printf("\n--- Canvas constructor ---\n");

	if (canvas_constructor(10, 20, &canvas) == false)
	{
		printf("%s[FAIL]%s Canvas constructor failed\n", RED, RESET);
		return ;
	}
	assert_int_eq(canvas.width, 10, "Canvas width is 10");
	assert_int_eq(canvas.height, 20, "Canvas height is 20");
}

void	test_write_pixel(void)
{
	t_canvas	canvas;
	t_vec3		red;
	t_uint		expected;
	t_uint		pixel;

	printf("\n--- Writing pixels to canvas ---\n");

	red = color_constructor(1.0, 0, 0);
	expected = 0xff0000;

	if (canvas_constructor(10, 20, &canvas) == false)
	{
		printf("%s[FAIL]%s Canvas constructor failed\n", RED, RESET);
		return ;
	}
	write_pixel(&canvas, 2, 3, red);
	pixel = get_pixel(&canvas, 2, 3);
	assert_int_eq(pixel, expected, "Pixel color at (2,3) is red");
}

/* ************************************************************************** */
/* RAY TESTS                                                                  */
/* ************************************************************************** */

void	test_ray_constructor(void)
{
	t_vec3	origin;
	t_vec3	direction;
	t_ray	r;

	printf("\n--- Ray constructor ---\n");

	origin = point_constructor(1, 2, 3);
	direction = vector_constructor(4, 5, 6);
	r = ray_constructor(origin, direction);

	assert_vec3_eq(r.origin, origin, "Ray origin");
	assert_vec3_eq(r.direction, direction, "Ray direction");
}

void	test_ray_position(void)
{
	t_vec3	origin;
	t_vec3	direction;
	t_ray	r;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	t_vec3	p4;

	printf("\n--- Ray position ---\n");

	origin = point_constructor(2, 3, 4);
	direction = vector_constructor(1, 0, 0);
	r = ray_constructor(origin, direction);

	p1 = ray_position(r, 0);
	p2 = ray_position(r, 1);
	p3 = ray_position(r, -1);
	p4 = ray_position(r, 2.5);

	assert_vec3_eq(p1, point_constructor(2, 3, 4), "ray_position(t=0)");
	assert_vec3_eq(p2, point_constructor(3, 3, 4), "ray_position(t=1)");
	assert_vec3_eq(p3, point_constructor(1, 3, 4), "ray_position(t=-1)");
	assert_vec3_eq(p4, point_constructor(4.5, 3, 4), "ray_position(t=2.5)");
}

/* ************************************************************************** */
/* SPHERE TESTS                                                               */
/* ************************************************************************** */

int	test_sphere_intersect(t_ray r, int ex_count, double ex_t0, double ex_t1)
{
	t_sphere	s;
	t_intersect	xs;

	s = sphere();
	xs = sphere_intersect(r, s);

	if ((xs.count == ex_count && (ex_count == 0 || 
		(fabs(xs.i[0].t - ex_t0) < EPSILON && 
		 fabs(xs.i[1].t - ex_t1) < EPSILON))))
		return (0);
	else
		return (1);
}

void	test_sphere_intersections(void)
{
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;

	printf("\n--- Sphere intersections ---\n");

	t1 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 0, -5), 
			vector_constructor(0, 0, 1)), 2, 4.0, 6.0);
	t2 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 1, -5), 
			vector_constructor(0, 0, 1)), 2, 5.0, 5.0);
	t3 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 2, -5), 
			vector_constructor(0, 0, 1)), 0, 0.0, 0.0);
	t4 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 0, 0), 
			vector_constructor(0, 0, 1)), 2, -1.0, 1.0);
	t5 = test_sphere_intersect(
		ray_constructor(point_constructor(0, 0, 5), 
			vector_constructor(0, 0, 1)), 2, -6.0, -4.0);

	if (t1 == 0 && t2 == 0 && t3 == 0 && t4 == 0 && t5 == 0)
	{
		g_tests_run++;
		g_tests_passed++;
		printf("%s[PASS]%s All sphere intersection tests\n", GREEN, RESET);
	}
	else
	{
		g_tests_run++;
		printf("%s[FAIL]%s Some sphere intersection tests\n", RED, RESET);
	}
}

void	test_intersection(void)
{
	t_object		o;
	t_intersection	i;

	printf("\n--- Intersection ---\n");

	o.sp = sphere();
	i = intersection(3.5, o);

	assert_float_eq(i.t, 3.5, "Intersection t value");
	assert_int_eq(i.object.sp.id, o.sp.id, "Intersection object ID");
}

bool	helper_test_hit(t_intersection *items, int items_size, t_intersection *expected)
{
	t_intersect		xs;
	t_intersection	result;
	t_intersection	*ret_val;

	intersections(items, &xs, items_size);
	ret_val = hit(&xs, &result, items_size);
	if (ret_val == NULL && expected == NULL)
		return (true);
	else if (ret_val == NULL && expected != NULL)
		return (false);
	if (result.t != expected->t || result.object.sp.id != expected->object.sp.id)
		return (false);
	return (true);
}

void	test_hit(void)
{
	t_object		object;
	t_intersection	items1[MAX_INTERSECTION];
	t_intersection	items2[MAX_INTERSECTION];
	t_intersection	items3[MAX_INTERSECTION];
	t_intersection	items4[MAX_INTERSECTION];

	printf("\n--- Hit detection ---\n");

	object.sp = sphere();
	items1[0] = intersection(1, object);
	items1[1] = intersection(2, object);
	items2[0] = intersection(-1, object);
	items2[1] = intersection(1, object);
	items3[0] = intersection(-2, object);
	items3[1] = intersection(-1, object);
	items4[0] = intersection(5, object);

	if (helper_test_hit(items1, 2, &items1[0]) == true
		&& helper_test_hit(items2, 2, &items2[1]) == true
		&& helper_test_hit(items3, 2, NULL) == true
		&& helper_test_hit(items4, 1, &items4[0]) == true)
	{
		g_tests_run++;
		g_tests_passed++;
		printf("%s[PASS]%s All hit detection tests\n", GREEN, RESET);
	}
	else
	{
		g_tests_run++;
		printf("%s[FAIL]%s Some hit detection tests\n", RED, RESET);
	}
}

/* ************************************************************************** */
/* MAIN                                                                       */
/* ************************************************************************** */

int	main(void)
{
	printf("===============================================================\n");
	printf("                MINIRT MAIN TESTER                            \n");
	printf("===============================================================\n");

	/* Color Tests */
	test_color_constructor();
	test_color_add();
	test_color_subtract();
	test_color_scalar();
	test_color_multiply();
	test_color_to_int();

	/* Canvas Tests */
	test_canvas_constructor();
	test_write_pixel();

	/* Ray Tests */
	test_ray_constructor();
	test_ray_position();

	/* Sphere Tests */
	test_sphere_intersections();
	test_intersection();
	test_hit();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");

	return (g_tests_passed != g_tests_run);
}
