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

# ------------------------------ DIRECTORIES -------------------------------- #

IDIR = include/
ODIR = obj/
SDIR = src/

VECDIR = $(SDIR)vec_utils

# ------------------------------ VECTORS -------------------------------- #

VEC_SRCS = base.c
PATH_OBJS_VEC = $(patsubst %.c,$(ODIR)vec_utils/%.o,$(VEC_SRCS))

# ------------------------------ BUILD -------------------------------- #

OBJ = $(PATH_OBJS_VEC)
DEP = $(IDIR)

# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) main.c $(OBJ) -o $(NAME)

$(ODIR)vec_utils/%.o: $(VECDIR)%.c $(DEP)
	mkdir -p $(ODIR)vec_utils
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
