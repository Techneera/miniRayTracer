/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:23:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/08 14:58:25 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
		int	expected = isdigit(chars[i]);
		int	output = ft_isdigit(chars[i]);
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
