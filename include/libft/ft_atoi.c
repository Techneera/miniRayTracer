/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:39:30 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/10 14:11:03 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	signal;

	result = 0;
	signal = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -1;
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		++nptr;
	}
	return (result * signal);
}

/*
#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	char	*strs[100] = {
		"julio",
	   	"123jil",
	   	"jul123",
	   	"     -1234",
	   	"---123",
	   	"-h-123",
	   	""
	};
	int		len = 7;

	for (int i = 0; i < len; i++)
	{
		int	expected = atoi(strs[i]);
		int	output = ft_atoi(strs[i]);
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
