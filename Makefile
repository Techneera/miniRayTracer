# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 13:42:18 by jcesar-s          #+#    #+#              #
#    Updated: 2026/01/05 13:46:43 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -lm
IDIR = include/
ODIR = obj/
SDIR = src/
SRCFILES = main.c
SRC = $(patsubst %, $(SDIR)%, $(SRCFILES))
OBJ = $(patsubst %.c, $(ODIR)%.o, $(SRCFILES))
DEP = $(IDIR)

all: $(NAME)

debug: CFLAGS += -g
debug: re

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c $(DEP)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
