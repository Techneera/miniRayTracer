/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:35:33 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 18:58:24 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_PRINTF_H
# define FD_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	fd_printf(int fd, const char *str, ...);

// utils
int	fd_putchar(int fd, char c);
int	fd_putstr(int fd, char *str);
int	fd_putnbr(int fd, int nb);
int	fd_putnbr_u(int fd, unsigned int nb);
int	fd_putnbr_hex(int fd, unsigned long nb, int letter_case);
int	fd_putptr(int fd, unsigned long nb, int print_prefix);

#endif
