/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:31:28 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/11 10:04:56 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_b;
	unsigned char	*s2_b;

	if (n == 0)
		return (0);
	i = -1;
	s1_b = (unsigned char *)s1;
	s2_b = (unsigned char *)s2;
	while (++i < n)
	{
		if (s1_b[i] != s2_b[i])
			return (s1_b[i] - s2_b[i]);
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*strs1[100] = {
		"julio",
	   	"123jil",
	   	"jul123",
	   	"     -1234",
	   	"",
	   	"-h-123",
	   	""
	};
	char	*strs2[100] = {
		"jio",
	   	"",
	   	"banana",
	   	" a    -1234",
	   	"---123",
	   	"-h-123",
	   	""
	};
	int		len = 7;

	for (int i = 0; i < len; i++)
	{
		int	expected = memcmp(strs1[i], strs2[i], i);
		int	output = ft_memcmp(strs1[i], strs2[i], i);
		if (expected == output)
		{
			printf("Test %d passed!", i + 1);
			printf("Expected %d, got %d\n\n", expected, output);
		}
		else
		{
			printf("Test %d failed!", i + 1);
			printf("Expected %d, got %d\n\n", expected, output);
		}
	}
	return (0);
}
*/
