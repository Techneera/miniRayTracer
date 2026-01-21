/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:42:48 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 16:32:29 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] != 0 && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == 0)
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	size_t	sizes[] = {2, 3, 1, 0, 15};
	char	src_strs[5][100] = {
		"abcdefgh",
		"aaxx",
		"juli",
		"    julio    ",
		"ara ma ra mare amar"
	};
	char	dst_strs[5][100] = {
		"abc",
		"xx",
		"",
		"julio",
		"mar"
	};
	int		len = 5;

	for (int i = 0; i < len; i++)
	{
		char	*expected;
		char	*output;

		expected = strnstr(src_strs[i], dst_strs[i], sizes[i]);
		output = ft_strnstr(src_strs[i], dst_strs[i], sizes[i]);
		if (expected && strncmp(expected, output, strlen(expected) + 1) == 0)
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
