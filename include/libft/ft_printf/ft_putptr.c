/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:17:35 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/06/12 13:18:51 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long nb, int print_prefix)
{
	char	*hex_base;
	int		printed_chars;

	if (nb == 0)
		return (ft_putstr("(nil)"));
	hex_base = "0123456789abcdef";
	printed_chars = 0;
	if (print_prefix == 1)
		printed_chars += ft_putstr("0x");
	if (nb > 15)
	{
		printed_chars += ft_putptr(nb / 16, 0);
		nb %= 16;
	}
	return (ft_putchar(hex_base[nb]) + printed_chars);
}
