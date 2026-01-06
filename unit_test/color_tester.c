#include "color.h"
#include <stdio.h>

void test_color_constructor(double r, double g, double b)
{
	t_vec3	color;
	color = color_constructor(r, g, b);
	printf("%f\n", color.x);
	printf("%f\n", color.y);
	printf("%f\n", color.z);
}

void test_color_add()
{
	t_vec3	color;
	t_vec3	u;
	t_vec3	v;

	u = color_constructor(0.9, 0.6, 0.75);
	v = color_constructor(0.7, 0.1, 0.25);
	color = vector_add(u, v);
	printf("%f\n", color.x);
	printf("%f\n", color.y);
	printf("%f\n", color.z);
}

int main(void)
{
	test_color_constructor(-0.5, 0.4, 1.7);
	test_color_add();
	return (1);
}
