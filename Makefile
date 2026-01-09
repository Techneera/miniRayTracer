NAME = $(BDIR)miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LMATH = -lm

# ------------------------------ DIRECTORIES -------------------------------- #

IDIR = include/
ODIR = obj/
SDIR = src/
TDIR = unit_test/
BDIR = build/

VECDIR = $(SDIR)vec_utils
MATDIR = $(SDIR)matrix_utils
COLORDIR = $(SDIR)color_utils

# ------------------------------ VECTORS -------------------------------- #

_VEC_SRCS = base.c
VEC_SRCS = $(patsubst %.c, $(VECDIR)/%.c, $(_VEC_SRCS))
VEC_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(VEC_SRCS))

# ------------------------------ MATRIX -------------------------------- #

_MATRIX_SRCS = matrix_ops.c
MATRIX_SRCS = $(patsubst %.c, $(MATDIR)/%.c, $(_MATRIX_SRCS))
MATRIX_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(MATRIX_SRCS))

# ------------------------------ COLORS -------------------------------- #

_COLOR_SRCS = color_operations.c \
			  color_conversion.c
COLOR_SRCS = $(patsubst %.c, $(COLORDIR)/%.c, $(_COLOR_SRCS))
COLOR_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(COLOR_SRCS))

# ------------------------------ UNIT TESTS-------------------------------- #

TESTERSRCS = $(TDIR)main_tester.c
TESTEROBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTERSRCS))

# ------------------------------ BUILD -------------------------------- #

OBJ = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(SRCFILES))
TESTOBJ = $(filter-out $(ODIR)$(SDIR)main.o, $(OBJ))
DEP = $(IDIR)

# ------------------------------ SOURCES -------------------------------- #

SRCFILES = $(SDIR)main.c \
		   $(VEC_SRCS) \
		   $(MATRIX_SRCS) \
		   $(COLOR_SRCS)

# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

test: $(TESTEROBJS) $(TESTOBJ) 
	$(CC) $(CFLAGS) $^ -o $(BDIR)tester -I$(IDIR) $(LMATH)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(ODIR)$(SDIR)%.o: $(SDIR)%.c
	@mkdir -p $(BDIR)
	@mkdir -p $(ODIR)$(VECDIR)
	@mkdir -p $(ODIR)$(MATDIR)
	@mkdir -p $(ODIR)$(COLORDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

$(ODIR)$(TDIR)%.o: $(TDIR)%.c
	@mkdir -p $(BDIR)
	@mkdir -p $(ODIR)$(TDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BDIR)

re: fclean all

.PHONY: all clean fclean re debug test
