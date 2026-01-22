/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:39:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 18:31:32 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		++i;
	}
	return (NULL);
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
	int		chars[] = {-1, 'a', '3', '\0', '-', 'h', 129};
	int		len = 7;

	for (int i = 0; i < len; i++)
	{
		char	*expected = memchr(strs1[i], chars[i]);
		char	*output = ft_memchr(strs1[i], chars[i]);
		if (expected == output)
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
	return (0);
}
*/
