# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 15:40:37 by jcesar-s          #+#    #+#              #
#    Updated: 2025/09/08 18:59:41 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libfdprintf.a
SRC=fd_printf.c fd_putchar.c fd_putstr.c fd_putnbr.c fd_putnbr_hex.c fd_putnbr_u.c fd_putptr.c
OBJS=$(SRC:.c=.o)
CC=cc
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
