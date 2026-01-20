/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:15:26 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/08 13:40:50 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}

/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	char	chars[] = "abc1 \n\tl";
	int		len = sizeof(chars);
	
	for (int i = 0; i < len; i++)
	{
		int	expected = isalpha(chars[i]);
		int	output = ft_isalpha(chars[i]);
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
