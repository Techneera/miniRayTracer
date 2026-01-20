/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:33:27 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/05 18:33:46 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(char const *str, char delimeter)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		while (*str == delimeter && *str)
			++str;
		if (*str)
			++len;
		while (*str != delimeter && *str)
			++str;
	}
	return (len);
}
