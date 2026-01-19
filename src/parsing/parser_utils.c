#include "parser.h"

char	*skip_to_next(char *ptr)
{
	if (ptr == NULL)
		return (NULL);
	while (*ptr && (*ptr != ' ' && *ptr != '\t'))
		++ptr;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		++ptr;
	return (ptr);
}

static
float	ft_atof_error(int *error)
{
	*error = 1;
	return (0.0);
}

static
void	init_vars(float *result, float *div, int *sign)
{
	*result = 0.0;
	*div = 10.0;
	*sign = 1;
}

static
bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static
char	**handle_signal(char **ptr, int *sign)
{
	if (**ptr == '-' || **ptr == '+')
	{
		if (**ptr == '-')
			*sign *= -1;
		++(*ptr);
	}
	return (ptr);
}

float	ft_atof(char **ptr, int *error)
{
	float	result;
	float	div;
	int		sign;

	init_vars(&result, &div, &sign);
	ptr = handle_signal(ptr, &sign);
	if (ft_isdigit(**ptr) != true && **ptr != '.')
		return (ft_atof_error(error));
	while (ft_isdigit(**ptr) == true)
		result = result * 10.0 + ((*(*ptr)++) - '0');
	if (**ptr == '.')
	{
		++(*ptr);
		if (ft_isdigit(**ptr) != true)
			return (ft_atof_error(error));
		while (ft_isdigit(**ptr) == true)
		{
			result = result + ((*(*ptr)++) - '0') / div;
			div *= 10;
		}
	}
	if (**ptr != '\0' && **ptr != ' ' && **ptr != '\t'
		&& **ptr != ',' && **ptr != '\n')
		return (ft_atof_error(error));
	return (result * sign);
}

/*
#include <stdio.h>
#include <string.h>

void test_skip_to_next(void)
{
    printf("Starting skip_to_next tests...\n");

    // Test Case 1: Simple space separation
    char *s1 = "A 0.2 255";
    char *res1 = skip_to_next(s1);
    if (res1 && strcmp(res1, "0.2 255") == 0)
        printf("[OK] Case 1: Standard space\n");
    else
        printf("[FAIL] Case 1: Expected '0.2 255', got '%s'\n", res1);

    // Test Case 2: Tab separation
    char *s2 = "C\t-50,0,20";
    char *res2 = skip_to_next(s2);
    if (res2 && strcmp(res2, "-50,0,20") == 0)
        printf("[OK] Case 2: Tabulator\n");
    else
        printf("[FAIL] Case 2: Expected '-50,0,20', got '%s'\n", res2);

    // Test Case 3: Multiple spaces
    char *s3 = "L      0.6";
    char *res3 = skip_to_next(s3);
    if (res3 && strcmp(res3, "0.6") == 0)
        printf("[OK] Case 3: Multiple spaces\n");
    else
        printf("[FAIL] Case 3: Expected '0.6', got '%s'\n", res3);

    // Test Case 4: No next word (end of string)
    char *s4 = "sp";
    char *res4 = skip_to_next(s4);
    if (res4 && *res4 == '\0')
        printf("[OK] Case 4: End of string\n");
    else
        printf("[FAIL] Case 4: Expected empty string, got '%s'\n", res4);

    // Test Case 5: NULL pointer
    if (skip_to_next(NULL) == NULL)
        printf("[OK] Case 5: NULL protection\n");
    else
        printf("[FAIL] Case 5: NULL not handled\n");

    printf("Tests completed.\n");
}

 bool float_approx(float a, float b) {
    float diff = a - b;
    return (diff < 0.0001 && diff > -0.0001);
}

void test_ft_atof(void)
{
    int   error;
    float res;
    char  *ptr;

    printf("--- Testing ft_atof ---\n");

    // Case 1: Standard Positive
    ptr = "12.34 ";
    error = 0;
    res = ft_atof(&ptr, &error);
    if (!error && float_approx(res, 12.34f) && *ptr == ' ')
        printf("[OK] Standard positive: 12.34\n");
    else
        printf("[FAIL] Standard positive: got %f, error: %d\n", res, error);

    // Case 2: Negative with Sign
    ptr = "-0.5";
    error = 0;
    res = ft_atof(&ptr, &error);
    if (!error && float_approx(res, -0.5f))
        printf("[OK] Standard negative: -0.5\n");
    else
        printf("[FAIL] Standard negative: got %f\n", res);

    // Case 3: Error - Garbage character after number
    ptr = "42.2abc";
    error = 0;
    res = ft_atof(&ptr, &error);
    if (error == 1)
        printf("[OK] Error catch: '42.2abc' triggered error\n");
    else
        printf("[FAIL] Error catch: '42.2abc' passed unexpectedly\n");

    // Case 4: Error - Multiple dots (2.5.5)
    ptr = "2.5.5";
    error = 0;
    res = ft_atof(&ptr, &error);
    // After first 2.5, it should see '.' and trigger termination error
    if (error == 1)
        printf("[OK] Error catch: '2.5.5' triggered error\n");
    else
        printf("[FAIL] Error catch: '2.5.5' passed\n");

    // Case 5: Error - Only a dot
    ptr = ".";
    error = 0;
    res = ft_atof(&ptr, &error);
    if (error == 1)
        printf("[OK] Error catch: '.' triggered error\n");
    else
        printf("[FAIL] Error catch: '.' passed\n");

    // Case 6: Pointer Advancement
    char *data = "10.5,20.5";
    ptr = data;
    error = 0;
    res = ft_atof(&ptr, &error); // Should parse 10.5 and stop at ','
    // Note: your current function triggers error if it stops at ','
    // You might need to add ',' to your termination check for miniRT.
    if (error == 1) 
        printf("[INFO] Note: your function currently rejects ',' as a separator.\n");
}

int main(void)
{
	test_skip_to_next();
	test_ft_atof();
}
*/
