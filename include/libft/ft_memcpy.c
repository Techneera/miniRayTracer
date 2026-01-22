/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:34:44 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 17:12:51 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d_byte;
	unsigned char	*s_byte;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	d_byte = (unsigned char *)dest;
	s_byte = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d_byte[i] = s_byte[i];
		i++;
	}
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	char	*expected;
	char	*output;
	char	tab1[100];
	char	tab2[100];
	char	source[100];
	//char	*null_pointer = NULL;
	
	strcpy(source, "First test");
	expected = memcpy(tab1, source, sizeof(source));
	output = ft_memcpy(tab2, source, sizeof(source));
	if (strcmp(expected, output) == 0)
	{
		printf("Expected %s, got %s\n", expected, output);
		printf("Test 1 passed\n\n");
	}

	return (0);	
}
*/
