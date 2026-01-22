/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:38:47 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 19:21:58 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static int	ft_putconv(int fd, int stamp, va_list format)
{
	if (stamp == 'c')
		return (fd_putchar(fd, va_arg(format, int)));
	else if (stamp == 's')
		return (fd_putstr(fd, va_arg(format, char *)));
	else if (stamp == 'i' || stamp == 'd')
		return (fd_putnbr(fd, va_arg(format, int)));
	else if (stamp == '%')
		return (fd_putchar(fd, '%'));
	else if (stamp == 'u')
		return (fd_putnbr_u(fd, va_arg(format, unsigned int)));
	else if (stamp == 'p')
		return (fd_putptr(fd, (unsigned long)va_arg(format, void *), 1));
	else if (stamp == 'X')
		return (fd_putnbr_hex(fd, va_arg(format, unsigned int), 'u'));
	else if (stamp == 'x')
		return (fd_putnbr_hex(fd, va_arg(format, unsigned int), 'l'));
	else
		return (0);
}

int	fd_printf(int fd, const char *str, ...)
{
	va_list	value;
	int		count;

	va_start(value, str);
	count = 0;
	while (*str)
	{
		if (*str != '%')
		{
			count += fd_putchar(fd, *str++);
			continue ;
		}
		count += ft_putconv(fd, *++str, value);
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
