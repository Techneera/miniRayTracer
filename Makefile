NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror

# ------------------------------ DIRECTORIES -------------------------------- #

IDIR = include/
ODIR = obj/
SDIR = src/

VECDIR = $(SDIR)vec_utils

# ------------------------------ VECTORS -------------------------------- #

_VEC_SRCS = base.c
VEC_SRCS = $(patsubst %.c, $(VECDIR)/%.c, $(_VECSCRS))

SRCFILES = $(SDIR)main.c \
		   $(VECSRCS)

# ------------------------------ BUILD -------------------------------- #

OBJ = $(patsubst %.c, %.o, $(SRCFILES))
DEP = $(IDIR)

# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	mkdir -p $(ODIR)vec_utils
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
