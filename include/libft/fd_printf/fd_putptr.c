/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:17:35 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 18:31:47 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	fd_putptr(int fd, unsigned long nb, int print_prefix)
{
	char	*hex_base;
	int		printed_chars;

	if (nb == 0)
		return (fd_putstr(fd, "(nil)"));
	hex_base = "0123456789abcdef";
	printed_chars = 0;
	if (print_prefix == 1)
		printed_chars += fd_putstr(fd, "0x");
	if (nb > 15)
	{
		printed_chars += fd_putptr(fd, nb / 16, 0);
		nb %= 16;
	}
	return (fd_putchar(fd, hex_base[nb]) + printed_chars);
}
