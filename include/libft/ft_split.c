/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:42:47 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/05 18:34:59 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int		fill(char **vector, char const *str, char delimeter);
static int		free_all(char **vector, size_t position);

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	len;

	if (NULL == s)
		return (NULL);
	len = count_words(s, c);
	ptr = malloc(sizeof(char *) * (len + 1));
	if (!ptr)
		return (NULL);
	if (fill(ptr, s, c))
		return (NULL);
	ptr[len] = NULL;
	return (ptr);
}

static int	fill(char **vector, char const *str, char delimeter)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*str)
	{
		len = 0;
		while (*str == delimeter && *str)
			++str;
		while (*str != delimeter && *str)
		{
			++len;
			++str;
		}
		if (len)
		{
			vector[i] = ft_substr(str - len, 0, len);
			if (!vector[i])
				return (free_all(vector, i));
			++i;
		}
	}
	return (0);
}

static int	free_all(char **vector, size_t position)
{
	size_t	i;

	i = 0;
	while (i < position)
	{
		free(vector[i]);
		++i;
	}
	free(vector);
	return (1);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	**arr;
// 	arr = ft_split("hello!zzzzzzzz", 'z'); 
// 	for (int i = 0; arr[i]; i++)
// 		printf("%s\n", arr[i]);	
// 	return (0);
// }
