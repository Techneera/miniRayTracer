/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:34:21 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/16 15:38:45 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
#include "strings.h"
#include <ctype.h>
int	main(void)
{
	int	chars[] = {-1, 'a', 'z', '4', '\0', 'A', '>', 'Z'};
	int		len = 8;

	for (int i = 0; i < len; i++)
	{
		int	expected = tolower(chars[i]);
		int	output = ft_tolower(chars[i]);
		if (expected == output)
		{
			printf("Test %d passed!", i + 1);
			printf("Expected %d, got %d\n\n", expected, output);
		}
		else
		{
			printf("Test %d failed!", i + 1);
			printf("Expected %d, got %d\n\n", expected, output);
		}
	}
	return (0);

}
*/
