/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:17:39 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 18:32:03 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	fd_putstr(int fd, char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (fd_putstr(fd, "(null)"));
	while (*str)
		len += fd_putchar(fd, *str++);
	return (len);
}
