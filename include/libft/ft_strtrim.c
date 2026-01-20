/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:38:37 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/16 15:43:56 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int	found(char c, const char *set);
static char	*search(const char *s, const char *set);
static char	*rsearch(const char *s, const char *set, size_t len);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	char	*start;
	int		diff;
	int		i;

	start = search(s1, set);
	diff = rsearch(s1, set, ft_strlen(s1)) - start;
	if (diff <= 0)
		return (ft_strdup(""));
	arr = malloc(sizeof(char) * (diff + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < diff)
	{
		arr[i] = *start;
		++i;
		++start;
	}
	arr[i] = 0;
	return (arr);
}

static int	found(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*search(const char *s, const char *set)
{
	while (*s)
	{
		if (!found(*s, set))
			return ((char *)s);
		s++;
	}
	return ((char *)s);
}

static char	*rsearch(const char *s, const char *set, size_t len)
{
	char	*end;

	end = (char *)s + len - 1;
	while (len--)
	{
		if (!found(*end, set))
			return (end + 1);
		end--;
	}
	return (end);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strtrim(" \t \t \n  \n\n\n\t", " \n\t"));
	return (0);
}
*/
