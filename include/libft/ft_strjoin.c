/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:35:31 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 16:21:28 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long	lens;
	char			*arr;
	int				i;

	lens = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = malloc(sizeof(char) * lens);
	if (!arr)
		return (NULL);
	i = 0;
	while (s1 && *s1)
	{
		arr[i] = *s1;
		++i;
		++s1;
	}
	while (s2 && *s2)
	{
		arr[i] = *s2;
		++s2;
		++i;
	}
	arr[i] = '\0';
	return (arr);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strjoin("julio ", "souza."));
	return (0);
}
*/
