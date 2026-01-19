NAME = $(BDIR)miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LMATH = -lm
LMLX = -lmlx_Linux -lXext -lX11

# ------------------------------ DIRECTORIES -------------------------------- #

IDIR = include/
ODIR = obj/
SDIR = src/
TDIR = unit_test/
BDIR = build/

MLXDIR = $(IDIR)minilibx-linux/

VECDIR = $(SDIR)vec_utils
CANVASDIR = $(SDIR)canvas_utils
RAYDIR = $(SDIR)ray_utils
MATDIR = $(SDIR)matrix_utils

# ------------------------------ VECTORS -------------------------------- #

_VEC_SRCS = base.c
VEC_SRCS = $(patsubst %.c, $(VECDIR)/%.c, $(_VEC_SRCS))
VEC_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(VEC_SRCS))

# ------------------------------ CANVAS -------------------------------- #

_CANVAS_SRCS = color_operations.c \
			  color_conversion.c \
			  canvas_constructor.c
CANVAS_SRCS = $(patsubst %.c, $(CANVASDIR)/%.c, $(_CANVAS_SRCS))
CANVAS_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(CANVAS_SRCS))

# ------------------------------ MATRIX -------------------------------- #

_MATRIX_SRCS = matrix_ops.c matrix_transforms.c
MATRIX_SRCS = $(patsubst %.c, $(MATDIR)/%.c, $(_MATRIX_SRCS))
MATRIX_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(MATRIX_SRCS))

# ------------------------------ RAYS -------------------------------- #

_RAY_SRCS = ray_constructor.c \
			sphere.c \
			intersection.c \
			ray_transform.c
RAY_SRCS = $(patsubst %.c, $(RAYDIR)/%.c, $(_RAY_SRCS))
RAY_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(RAY_SRCS))

# ------------------------------ UNIT TESTS-------------------------------- #

TESTERSRCS = $(TDIR)main_tester.c
TESTEROBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTERSRCS))

TESTER2SRCS = $(TDIR)tester_v2.c
TESTER2OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER2SRCS))

TESTER3SRCS = $(TDIR)draw_test.c
TESTER3OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER3SRCS))

# ------------------------------ LIBRARIES -------------------------------- #

MLX = $(MLXDIR)libmlx_Linux.a

# ------------------------------ BUILD -------------------------------- #

OBJ = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(SRCFILES))
TESTOBJ = $(filter-out $(ODIR)$(SDIR)main.o, $(OBJ))
DEP = $(IDIR)

# ------------------------------ SOURCES -------------------------------- #

SRCFILES = $(SDIR)main.c \
		   $(VEC_SRCS) \
		   $(CANVAS_SRCS) \
		   $(RAY_SRCS) \
		   $(MATRIX_SRCS) \

# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

test: $(MLX) $(TESTEROBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTEROBJS) $(TESTOBJ) -o $(BDIR)tester -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX)

test_v2: $(MLX) $(TESTER2OBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTER2OBJS) $(TESTOBJ) -o $(BDIR)tester_v2 -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX)

test_draw: $(MLX) $(TESTER3OBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTER3OBJS) $(TESTOBJ) -o $(BDIR)tester_draw -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX)

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(ODIR)$(SDIR)%.o: $(SDIR)%.c
	@mkdir -p $(BDIR)
	@mkdir -p $(ODIR)$(VECDIR)
	@mkdir -p $(ODIR)$(CANVASDIR)
	@mkdir -p $(ODIR)$(RAYDIR)
	@mkdir -p $(ODIR)$(MATDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR) -I$(MLXDIR)

$(ODIR)$(TDIR)%.o: $(TDIR)%.c
	@mkdir -p $(BDIR)
	@mkdir -p $(ODIR)$(TDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(IDIR) -I$(MLXDIR)

$(MLX):
	make -C $(MLXDIR)

clean:
	make clean -C $(MLXDIR)
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BDIR)

re: fclean all

.PHONY: all clean fclean re debug test test_v2 test_draw
