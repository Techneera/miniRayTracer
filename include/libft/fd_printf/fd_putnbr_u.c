/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:17:27 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 18:31:06 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	fd_putnbr_u(int fd, unsigned int nb)
{
	int	printed_chars;

	printed_chars = 0;
	if (nb > 9)
	{
		printed_chars += fd_putnbr(fd, nb / 10);
		nb %= 10;
	}
	return (printed_chars + fd_putchar(fd, nb + '0'));
}

// int	main(void)
// {
// 	int	count = fd_putnbr(-2147483647);
// 
// 	printf("\n%d\n", count);
// 	return (0);
// }
