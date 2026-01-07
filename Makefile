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

TESTERSRCS = $(TDIR)main_tester.c
TESTEROBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTERSRCS))

# ------------------------------ BUILD -------------------------------- #

OBJ = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(SRCFILES))
TESTOBJ = $(filter-out $(ODIR)main.o, $(OBJ))
DEP = $(IDIR)

# ------------------------------ SOURCES -------------------------------- #

SRCFILES = $(SDIR)main.c \
		   $(VEC_SRCS) \
		   $(COLOR_SRCS)

# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

test: $(TESTEROBJS) $(TESTOBJ) 
	$(CC) $(CFLAGS) -g $^ -o $(BDIR)tester -I$(IDIR) $(LMATH)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c
	mkdir -p $(BDIR)
	mkdir -p $(ODIR)$(VECDIR)
	mkdir -p $(ODIR)$(COLORDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

$(ODIR)$(TDIR)%.o: $(TDIR)%.c
	mkdir -p $(ODIR)$(TDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BDIR)

re: fclean all

.PHONY: all clean fclean re debug test
