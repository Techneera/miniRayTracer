#include "parser.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

#define EPSILON 0.00001
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

static int g_tests_run = 0;
static int g_tests_passed = 0;

/* ************************************************************************** */
/* HELPER FOR TESTS                              */
/* ************************************************************************** */

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

static bool assert_int_eq(int actual, int expected, const char *msg)
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

static bool assert_ptr_eq(void *actual, void *expected, const char *msg)
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

/* ************************************************************************** */
/* UTILITY TESTS                                 */
/* ************************************************************************** */

void test_skip_to_next(void)
{
	printf("\n--- 1. skip_to_next ---\n");

	char *s1 = "A 0.2 255";
	assert_ptr_eq(skip_to_next(s1), s1 + 2, "Skip 'A ' to '0.2'");

	char *s2 = "C\t-50,0,20";
	assert_ptr_eq(skip_to_next(s2), s2 + 2, "Skip 'C\\t' to '-50'");

	char *s3 = "sp      10.5";
	assert_ptr_eq(skip_to_next(s3), s3 + 8, "Skip 'sp' and multiple spaces");

	char *s4 = "L";
	assert_ptr_eq(skip_to_next(s4), s4 + 1, "Skip to end of string if no next word");
}

void test_ft_atof(void)
{
	printf("\n--- 2. ft_atof (Float Parsing) ---\n");
	
	int   error;
	char  *ptr;
	float res;

	// Valid Positive
	ptr = "12.34 ";
	error = 0;
	res = ft_atof(&ptr, &error);
	assert_float_eq(res, 12.34f, "Parse '12.34'");
	assert_int_eq(error, 0, "No error on '12.34'");
	assert_int_eq(*ptr, ' ', "Pointer advanced to space after '12.34'");

	// Valid Negative
	ptr = "-0.5";
	error = 0;
	res = ft_atof(&ptr, &error);
	assert_float_eq(res, -0.5f, "Parse '-0.5'");
	assert_int_eq(error, 0, "No error on '-0.5'");

	// Integer
	ptr = "5";
	error = 0;
	res = ft_atof(&ptr, &error);
	assert_float_eq(res, 5.0, "Parse '5'");
	assert_int_eq(error, 0, "No error on '5'");

	// Edge Case: Leading dot
	ptr = ".5 ";
	error = 0;
	res = ft_atof(&ptr, &error);
	assert_float_eq(res, 0.5f, "Parse '.5' as 0.5");

	// Error Case: Garbage
	ptr = "42.2abc";
	error = 0;
	ft_atof(&ptr, &error);
	assert_int_eq(error, 1, "Error triggered by '42.2abc'");

	// Error Case: Double dot
	ptr = "1.2.3";
	error = 0;
	ft_atof(&ptr, &error);
	assert_int_eq(error, 1, "Error triggered by '1.2.3'");

	// Error Case: Trailing dot
	ptr = "2. ";
	error = 0;
	ft_atof(&ptr, &error);
	assert_int_eq(error, 1, "Error triggered by '2.' (no digits after dot)");
}

void test_load_scene(void)
{
	t_scene scene;
	printf("\n--- 3. load_scene (File & Scene Validation) ---\n");

	// Test Case 1: Wrong Extension
	ft_memset(&scene, 0, sizeof(t_scene));
	assert_int_eq(load_scene("unit_test/test_files/test.txt", &scene), 1, "Reject file with .txt extension");

	// Test Case 2: Non-existent file
	ft_memset(&scene, 0, sizeof(t_scene));
	assert_int_eq(load_scene("unit_test/test_files/non_existent.rt", &scene), 1, "Handle non-existent .rt file");

	// Test Case 3: Missing Mandatory Elements (Assuming empty_but_valid_ext.rt exists)
	// Create a dummy file if needed: touch empty.rt
	ft_memset(&scene, 0, sizeof(t_scene));
	assert_int_eq(load_scene("unit_test/test_files/empty.rt", &scene), 1, "Fail if A or C are missing");

	/* Note: For the following tests, ensure these files exist with content:
	   valid_minimal.rt:
	   A 0.2 255,255,255
	   C 0,0,0 0,0,1 70
	*/
	
	// Test Case 4: Valid Minimal Scene
	ft_memset(&scene, 0, sizeof(t_scene));
	int res = load_scene("unit_test/test_files/valid_minimal.rt", &scene);
	if (assert_int_eq(res, 0, "Load valid minimal scene (A and C)"))
	{
		assert_float_eq(scene.a_light.ratio, 0.2f, "Verify Ambient Ratio");
	}

	// Test Case 5: Object Count Verification
	/*
	   valid_objects.rt:
	   A 0.1 255,255,255
	   C 0,0,0 0,0,1 70
	   sp 0,0,20 10 255,0,0
	   pl 0,-1,0 0,1,0 255,255,255
	*/
	ft_memset(&scene, 0, sizeof(t_scene));
	if (load_scene("unit_test/test_files/valid_objects.rt", &scene) == 0)
	{
		assert_int_eq(scene.object_count, 2, "Correctly count 2 objects (sp and pl)");
	}
}

/* ************************************************************************** */
/* MAIN                                     */
/* ************************************************************************** */

int main(void)
{
	printf("===============================================================\n");
	printf("                MINIRT PARSING UTILS TESTER                    \n");
	printf("===============================================================\n");

	test_skip_to_next();
	test_ft_atof();
	test_load_scene();

	printf("\n==========================================\n");
	if (g_tests_passed == g_tests_run)
		printf("%sALL TESTS PASSED (%d/%d)%s\n", GREEN, g_tests_passed, g_tests_run, RESET);
	else
		printf("%sSOME TESTS FAILED (%d/%d)%s\n", RED, g_tests_passed, g_tests_run, RESET);
	printf("==========================================\n");
	
	return (g_tests_passed != g_tests_run);
}
