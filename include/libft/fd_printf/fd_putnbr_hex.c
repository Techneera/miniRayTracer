/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:53:36 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 18:47:09 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	fd_putnbr_hex(int fd, unsigned long nb, int letter_case)
{
	int			printed_chars;
	const char	*u_base = "0123456789ABCDEF";
	const char	*l_base = "0123456789abcdef";

	printed_chars = 0;
	if (nb > 15)
	{
		printed_chars += fd_putnbr_hex(fd, nb / 16, letter_case);
		nb %= 16;
	}
	if (letter_case == 'u')
		return (fd_putchar(fd, u_base[nb]) + printed_chars);
	else if (letter_case == 'l')
		return (fd_putchar(fd, l_base[nb]) + printed_chars);
	else
		return (-1);
}
