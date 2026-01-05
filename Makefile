NAME = $(BDIR)miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror
LMATH = -lm

# ------------------------------ DIRECTORIES -------------------------------- #

IDIR = include/
ODIR = obj/
SDIR = src/
TDIR = unit_test/
BDIR = build/

VECDIR = $(SDIR)vec_utils

# ------------------------------ VECTORS -------------------------------- #

_VEC_SRCS = base.c
VEC_SRCS = $(patsubst %.c, $(VECDIR)/%.c, $(_VEC_SCRS))


# ------------------------------ UNIT TESTS-------------------------------- #

_OPS_SRCS = vec_ops.c

# ------------------------------ BUILD -------------------------------- #

OBJ = $(patsubst %.c, %.o, $(SRCFILES))
DEP = $(IDIR)

# ------------------------------ SOURCES -------------------------------- #

SRCFILES = $(SDIR)main.c \
		   $(VECSRCS)

# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

vec_test:
	mkdir -p $(BDIR)
	$(CC) $(CFLAGS) $(TDIR)$(_OPS_SRCS) -o $(BDIR) -I $(IDIR) $(LMATH)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	mkdir -p $(BDIR)
	mkdir -p $(ODIR)vec_utils
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BDIR)

re: fclean all

.PHONY: all clean fclean re debug vec_test
