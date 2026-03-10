NAME = $(BDIR)miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-psabi -O3 -ffast-math
#-O3 -ffast-math
#-Wno-incompatible-pointer-types
LMATH = -lm
LMLX = -lmlx_Linux -lXext -lX11
LLFT = -lft

# ------------------------------ DIRECTORIES -------------------------------- #

IDIR = include/
ODIR = obj/
SDIR = src/
TDIR = unit_test/
BDIR = build/

MLXDIR = $(IDIR)minilibx-linux/
LFTDIR = $(IDIR)libft/
VECDIR = $(SDIR)vec_utils
CANVASDIR = $(SDIR)canvas_utils
RAYDIR = $(SDIR)ray_utils
MATDIR = $(SDIR)matrix_utils
PARSEDIR = $(SDIR)parsing
SHADESDIR = $(SDIR)shades_utils
SCENEDIR = $(SDIR)scene_utils
SHADOWSDIR = $(SDIR)shadows_utils
PATTERNSDIR = $(SDIR)patterns_utils
REFLECTIONDIR = $(SDIR)reflection_utils
REFRACTIONDIR = $(SDIR)refraction_utils
APIDIR = $(SDIR)scene_api

# ------------------------------ VECTORS -------------------------------- #

_VEC_SRCS = base.c operations.c multiply.c
VEC_SRCS = $(patsubst %.c, $(VECDIR)/%.c, $(_VEC_SRCS))
VEC_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(VEC_SRCS))

# ------------------------------ CANVAS -------------------------------- #

_CANVAS_SRCS = color_operations.c \
			  color_conversion.c \
			  canvas_constructor.c \
			  canvas_utils.c
CANVAS_SRCS = $(patsubst %.c, $(CANVASDIR)/%.c, $(_CANVAS_SRCS))
CANVAS_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(CANVAS_SRCS))

# ------------------------------ MATRIX -------------------------------- #

_MATRIX_SRCS = matrix_ops.c matrix_transforms.c matrix_rotations.c \
			 matrix_determinant_utils.c matrix_inverse_utils.c \
			 object_transform_utils.c
MATRIX_SRCS = $(patsubst %.c, $(MATDIR)/%.c, $(_MATRIX_SRCS))
MATRIX_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(MATRIX_SRCS))

# ------------------------------ RAYS -------------------------------- #

_RAY_SRCS = ray_constructor.c \
			sphere.c \
			plane.c \
			shape.c \
			shape_utils.c \
			intersection.c \
			ray_transform.c \
			cube.c \
			cylinder.c \
			cylinder_utils.c \
			cone_utils.c \
			cone.c
RAY_SRCS = $(patsubst %.c, $(RAYDIR)/%.c, $(_RAY_SRCS))
RAY_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(RAY_SRCS))

# ------------------------------ PARSING -------------------------------- #

_PARSE_SRCS = parser.c \
			  parser_utils.c \
			  parser_string_utils.c \
			  parse_setup.c \
			  parse_objects.c \
			  get_line_buf.c \
			  load_scene.c

PARSE_SRCS = $(patsubst %.c, $(PARSEDIR)/%.c, $(_PARSE_SRCS))
PARSE_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(PARSE_SRCS))

# ------------------------------ SHADES -------------------------------- #

_SHADES_SRCS = shades_utils.c lighting.c

SHADES_SRCS = $(patsubst %.c, $(SHADESDIR)/%.c, $(_SHADES_SRCS))
SHADES_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(SHADES_SRCS))

# ------------------------------ SCENE -------------------------------- #

_SCENE_SRCS = world.c world_camera.c world_refraction.c

SCENE_SRCS = $(patsubst %.c, $(SCENEDIR)/%.c, $(_SCENE_SRCS))
SCENE_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(SCENE_SRCS))

# ------------------------------ SCENE API -------------------------------- #

_SCENE_API_SRCS = material_setters.c \
				  object_spawn.c \
				  rotations.c \
				  transformations.c

SCENE_API_SRCS = $(patsubst %.c, $(APIDIR)/%.c, $(_SCENE_API_SRCS))
SCENE_API_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(SCENE_API_SRCS))

# ------------------------------ SHADOWS -------------------------------- #

_SHADOWS_SRCS = shadows.c

SHADOWS_SRCS = $(patsubst %.c, $(SHADOWSDIR)/%.c, $(_SHADOWS_SRCS))
SHADOWS_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(SHADOWS_SRCS))


# ------------------------------ REFLECTION -------------------------------- #

_REFLECTION_SRCS = reflected_color.c

REFLECTION_SRCS = $(patsubst %.c, $(REFLECTIONDIR)/%.c, $(_REFLECTION_SRCS))
REFLECTION_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(REFLECTION_SRCS))

# ------------------------------ REFRACTION -------------------------------- #

_REFRACTION_SRCS = manage_containers.c refracted_colors.c

REFRACTION_SRCS = $(patsubst %.c, $(REFRACTIONDIR)/%.c, $(_REFRACTION_SRCS))
REFRACTION_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(REFRACTION_SRCS))

# ------------------------------ PATTERNS -------------------------------- #

_PATTERNS_SRCS = patterns_utils.c \
				 stripe_pattern.c \
				 checker_pattern.c \
				 gradient_pattern.c \
				 ring_pattern.c

PATTERNS_SRCS = $(patsubst %.c, $(PATTERNSDIR)/%.c, $(_PATTERNS_SRCS))
PATTERNS_OBJS = $(patsubst $(SDIR)%.c, $(ODIR)$(SDIR)%.o, $(PATTERNS_SRCS))


# ------------------------------ UNIT TESTS-------------------------------- #

TESTER4SRCS = $(TDIR)parsing_test.c
TESTER4OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER4SRCS))

TESTER11SRCS = $(TDIR)test_reflection.c
TESTER11OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER11SRCS))

TESTER12SRCS = $(TDIR)standard_forms.c
TESTER12OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER12SRCS))

TESTER12SRCS = $(TDIR)standard_forms.c
TESTER12OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER12SRCS))

TESTER13SRCS = $(TDIR)transparency_test.c
TESTER13OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER13SRCS))

TESTER14SRCS = $(TDIR)glass_box.c
TESTER14OBJS = $(patsubst $(TDIR)%.c, $(ODIR)$(TDIR)%.o, $(TESTER14SRCS))
# ------------------------------ LIBRARIES -------------------------------- #

MLX = $(MLXDIR)libmlx_Linux.a
LFT = $(LFTDIR)libft.a

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
		   $(SHADES_SRCS) \
		   $(SCENE_SRCS) \
		   $(SHADOWS_SRCS) \
		   $(PARSE_SRCS) \
		   $(PATTERNS_SRCS) \
		   $(REFLECTION_SRCS) \
		   $(SCENE_API_SRCS) \
		   $(REFRACTION_SRCS)


# ------------------------------ RULES -------------------------------- #

all: $(NAME)

debug: CFLAGS += -g
debug: re

test_parsing: $(MLX) $(LFT) $(TESTER4OBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTER4OBJS) $(TESTOBJ) -o $(BDIR)tester_parsing -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX) -L$(LFTDIR) $(LLFT)

test_reflection: $(MLX) $(LFT) $(TESTER11OBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTER11OBJS) $(TESTOBJ) -o $(BDIR)tester_reflection -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX) -L$(LFTDIR) $(LLFT)

std_forms: $(MLX) $(LFT) $(TESTER12OBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTER12OBJS) $(TESTOBJ) -o $(BDIR)$@ -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX) -L$(LFTDIR) $(LLFT)
	./build/std_forms

std_trans: $(MLX) $(LFT) $(TESTER13OBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTER13OBJS) $(TESTOBJ) -o $(BDIR)$@ -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX) -L$(LFTDIR) $(LLFT)
	./build/std_trans

glassbox: $(MLX) $(LFT) $(TESTER14OBJS) $(TESTOBJ)
	$(CC) $(CFLAGS) -g $(TESTER14OBJS) $(TESTOBJ) -o $(BDIR)$@ -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX) -L$(LFTDIR) $(LLFT)
	./build/glassbox

$(NAME): $(MLX) $(LFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I$(IDIR) -I$(MLXDIR) $(LMATH) -L$(MLXDIR) $(LMLX) -L$(LFTDIR) $(LLFT)

$(ODIR)$(SDIR)%.o: $(SDIR)%.c
	@mkdir -p $(BDIR)
	@mkdir -p $(ODIR)$(VECDIR)
	@mkdir -p $(ODIR)$(CANVASDIR)
	@mkdir -p $(ODIR)$(RAYDIR)
	@mkdir -p $(ODIR)$(MATDIR)
	@mkdir -p $(ODIR)$(PARSEDIR)
	@mkdir -p $(ODIR)$(SHADESDIR)
	@mkdir -p $(ODIR)$(SHADOWSDIR)
	@mkdir -p $(ODIR)$(SCENEDIR)
	@mkdir -p $(ODIR)$(PATTERNSDIR)
	@mkdir -p $(ODIR)$(REFLECTIONDIR)
	@mkdir -p $(ODIR)$(REFRACTIONDIR)
	@mkdir -p $(ODIR)$(APIDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR) -I$(MLXDIR) -I$(LFTDIR)

$(ODIR)$(TDIR)%.o: $(TDIR)%.c
	@mkdir -p $(BDIR)
	@mkdir -p $(ODIR)$(TDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(IDIR) -I$(MLXDIR) -I$(LFTDIR)

$(MLX):
	make -C $(MLXDIR)

$(LFT):
	make -C $(LFTDIR)

clean:
	make clean -C $(MLXDIR)
	make clean -C $(LFTDIR)
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BDIR)

re: fclean all

.PHONY: all clean fclean re debug test_parsing test_reflection std_forms std_trans glassbox
