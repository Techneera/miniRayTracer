/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:41:51 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 15:16:56 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	unsigned long	len;

	str = (char *)s;
	len = ft_strlen(str) + 1;
	while (len > 0)
	{
		if (str[len - 1] == (char)c)
			return (&str[len - 1]);
		len--;
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
		char	*expected = strrchr(strs1[i], chars[i]);
		char	*output = ft_strrchr(strs1[i], chars[i]);
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
