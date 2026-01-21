/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:25:24 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/12 10:36:23 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int		count_digits(int n);
static int		get_magnitude(int n);
static long		get_abs(int n);

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;
	int		i;
	int		mag;

	len = count_digits(n) + (n < 0);
	mag = get_magnitude(n);
	arr = malloc(sizeof(char) * (len + 1));
	if (arr == NULL)
		return (NULL);
	i = -1;
	if (n < 0)
	{
		arr[0] = '-';
		++i;
	}
	while (++i < len)
	{
		arr[i] = get_abs(n / mag) + '0';
		n %= mag;
		mag /= 10;
	}
	arr[i] = 0;
	return (arr);
}

static int	count_digits(int n)
{
	long	count;

	n = get_abs(n / 10);
	count = 1;
	while (n)
	{
		count++;
		n /= 10;
	}
	return ((int)count);
}

static int	get_magnitude(int n)
{
	int	result;

	n = get_abs(n / 10);
	result = 1;
	while (n)
	{
		result *= 10;
		n /= 10;
	}
	return (result);
}

static long	get_abs(int n)
{
	if (n < 0)
		return ((long)-n);
	return ((long)n);
}
