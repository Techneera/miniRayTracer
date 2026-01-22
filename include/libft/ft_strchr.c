/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:59:34 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 18:37:06 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		++i;
	}
	if ((char)c == 0)
		return (&str[i]);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*strs1[100] = {
		"bonjour",
		"",
		"julio",
	   	"123jil",
	   	"jul123",
	   	"     -1234",
	   	"",
	   	"-h-123",
	   	""
	};
	int		chars[] = {'b', '\0', -1, 'a', '3', '\0', '-', 'h', 129};
	int		len = 9;

	for (int i = 0; i < len; i++)
	{
		char	*expected = strchr(strs1[i], chars[i]);
		char	*output = ft_strchr(strs1[i], chars[i]);
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
