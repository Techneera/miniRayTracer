/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:02:56 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/16 15:51:26 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*arr;

	if (!len || !*s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		arr[i] = s[start + i];
		++i;
	}
	arr[i] = 0;
	return (arr);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_substr("", 0, 1));	
	return (0);
}
*/
