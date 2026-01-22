/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:38:47 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/06/13 11:22:29 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putconv(int stamp, va_list format)
{
	if (stamp == 'c')
		return (ft_putchar(va_arg(format, int)));
	else if (stamp == 's')
		return (ft_putstr(va_arg(format, char *)));
	else if (stamp == 'i' || stamp == 'd')
		return (ft_putnbr(va_arg(format, int)));
	else if (stamp == '%')
		return (ft_putchar('%'));
	else if (stamp == 'u')
		return (ft_putnbr_u(va_arg(format, unsigned int)));
	else if (stamp == 'p')
		return (ft_putptr((unsigned long)va_arg(format, void *), 1));
	else if (stamp == 'X')
		return (ft_putnbr_hex(va_arg(format, unsigned int), 'u'));
	else if (stamp == 'x')
		return (ft_putnbr_hex(va_arg(format, unsigned int), 'l'));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	value;
	int		count;

	va_start(value, str);
	count = 0;
	while (*str)
	{
		if (*str != '%')
		{
			count += ft_putchar(*str++);
			continue ;
		}
		count += ft_putconv(*++str, value);
		++str;
	}
	va_end(value);
	return (count);
}

/*
int	main(void)
{
	char	*ptr = NULL;

	ft_printf("I am %i years old\n", 10 + 12);
	ft_printf("Now I want to print a percent sign (%%)\n");
	ft_printf("%X\n", -1);
	printf("%X\n", -1);
	ft_printf("%x\n", -1);
	printf("%d\n", ft_printf("%p\n", ptr));
	printf("%d\n", printf("%p\n", ptr));
	ft_printf(" %p %p ", 0, 0);

	printf("\n\n", 2.3454);
	return 0;
}
*/
