NAME = liboclmath.a

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

FLAGS = -Wall -Wextra -Werror
CC = gcc

OCLMATH_HEADER = include/ocl_math.h
OCLMATH_INC = -Iinclude/

OCLMATH_MODULE = source/rad_to_deg.c \
        source/deg_to_rad.c \
        source/v3_length.c \
        source/v3_add.c \
        source/v3_sub.c \
        source/v3_cross.c \
        source/v3_scale.c \
        source/v3_norm.c \
        source/v3_length_sq.c \
        source/v3_dot.c \
        source/v3_rotate.c \
        source/v2_dot.c \
        source/v2_det.c \
        source/v2_angle.c \
        source/v2_length.c \
        source/v2_scale.c \
        source/v2_norm.c \
        source/v3_angle_to_xz.c \
        source/i2_sub.c \

OBJ_DIR = ./obj/
OBJ_OCLMATH_MODULE = $(addprefix $(OBJ_DIR), $(OCLMATH_MODULE:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_OCLMATH_MODULE)
	@ar rc $(NAME) $(OBJ_OCLMATH_MODULE)
	@ranlib $(NAME)
	@printf "$(GREEN)RT:\t$(YELLOW)%-90s$(GREEN)[done]$(NONE)\n" $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c $(OCLMATH_HEADER)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(OCLMATH_INC) $< -o $@

norm:
	@norminette $(OCLMATH_HEADER) $(OCLMATH_MODULE)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean : clean
	@/bin/rm -f $(NAME)

re: fclean all