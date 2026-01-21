/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:13:00 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 14:24:08 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (2048);
	return (0);
}

/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	char	chars[] = "abc1 5460\n\tl";
	int		len = sizeof(chars);
	
	for (int i = 0; i < len; i++)
	{
		int	expected = isprint(chars[i]);
		int	output = ft_isprint(chars[i]);
		if (expected == output)
		{
			printf("Test %d passed! ", i + 1);
			printf("Expected %d, got %d\n\n", expected, output);
		}
		else
		{
			printf("Test %d Failed! ", i + 1);
			printf("Expected %d, got %d\n\n", expected, output);
		}
	}
	return (0);
}
*/
