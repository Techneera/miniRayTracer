/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:43:14 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 14:20:15 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_b;
	unsigned char	*src_b;
	size_t			i;

	dest_b = (unsigned char *)dest;
	src_b = (unsigned char *)src;
	if (n == 0)
		return (dest);
	if (dest > src)
	{
		i = n;
		while (i-- > 0)
			dest_b[i] = src_b[i];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	size_t	sizes[] = {4, 5, 1, 0, 6};
	char	src_strs[4][100] = {
		"ana",
		"this is a test",
		"",
		"    julio    "
	};
	char	dst_strs[4][100] = {
		"julio",
		"Another test",
		"juli",
		"julio"
	};
	int		len = 4;

	for (int i = 0; i < len + 1; i++)
	{
		char	*expected;
		char	*output;

		if (i < len)
		{
			expected = memmove(dst_strs[i], src_strs[i], sizes[i]);
			output = ft_memmove(dst_strs[i], src_strs[i], sizes[i]);
		}
		if (i == len)
		{
			expected = memmove(&dst_strs[1][5], &dst_strs[1][1], sizes[i]);
			output = ft_memmove(&dst_strs[1][5], &dst_strs[1][1], sizes[i]);
		}
		if (strncmp(expected, output, strlen(dst_strs[i]) + 1) == 0)
		{
			printf("Test %d passed!", i + 1);
			printf("Expected %s, got %s\n\n", expected, output);
		}
		else
		{
			printf("Test %d failed!", i + 1);
			printf("Expected %s, got %s\n\n", expected, output);
		}
	}
}
*/
