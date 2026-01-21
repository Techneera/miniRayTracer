# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 15:40:37 by jcesar-s          #+#    #+#              #
#    Updated: 2025/06/13 11:24:08 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a
SRC=ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putnbr_hex.c ft_putnbr_u.c ft_putptr.c
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
