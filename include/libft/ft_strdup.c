/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:22:08 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/11 14:29:31 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strdup(const char *s)
{
	long	len;
	char	*arr;

	len = ft_strlen(s) + 1;
	arr = malloc(sizeof(char) * len);
	if (!arr)
		return (NULL);
	while (len--)
		arr[len] = s[len];
	return (arr);
}
