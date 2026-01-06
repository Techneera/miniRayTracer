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
COLORDIR = $(SDIR)color_utils

# ------------------------------ VECTORS -------------------------------- #

_VEC_SRCS = base.c
VEC_SRCS = $(patsubst %.c, $(VECDIR)/%.c, $(_VEC_SRCS))
VEC_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(VEC_SRCS))

# ------------------------------ COLORS -------------------------------- #

_COLOR_SRCS = colors.c
COLOR_SRCS = $(patsubst %.c, $(COLORDIR)/%.c, $(_COLOR_SRCS))
COLOR_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(COLOR_SRCS))

# ------------------------------ UNIT TESTS-------------------------------- #

_OPS_SRCS = vec_ops.c
COLOR_TEST_SRCS = $(TDIR)color_tester.c

# ------------------------------ BUILD -------------------------------- #

OBJ = $(patsubst %.c, %.o, $(SRCFILES))
DEP = $(IDIR)

# ------------------------------ SOURCES -------------------------------- #

SRCFILES = $(SDIR)main.c \
		   $(VEC_SRCS) \
		   $(COLOR_SRCS)

TESTFILES = $(filter-out $(SDIR)main.c, $(SRCFILES))

# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

vec_test: $(VEC_OBJS)
	$(CC) $(CFLAGS) -g $(TDIR)$(_OPS_SRCS) $^ -o $(BDIR)vec_tester -I$(IDIR) $(LMATH)

color_test: TESTFILES += $(COLOR_TEST_SRCS)
color_test:
	$(CC) $(CFLAGS) -g $(TESTFILES) $^ -o $(BDIR)color_tester -I$(IDIR) $(LMATH)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c
	mkdir -p $(BDIR)
	mkdir -p $(ODIR)vec_utils
	mkdir -p $(ODIR)color_utils
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BDIR)

re: fclean all

.PHONY: all clean fclean re debug vec_test
