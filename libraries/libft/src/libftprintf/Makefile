NAME = libftprintf.a

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

FLAGS = -Wall -Wextra -Werror
CC = gcc

LIBFTPRINTF_HEADER = ../../inc/ftprintf.h
LIBFTPRINTF_INC = -I../../inc/

LIBFTPRINTF_MODULE = pft_validator.c \
        pft_parser.c \
        pft_parse_addition.c \
        pft_parse_flag.c \
        pft_parse_width.c \
        pft_parse_precision.c \
        pft_parse_length.c \
        pft_parse_type.c \
        pft_color.c \
        pft_choose_type.c \
        pft_print_wchar.c \
        pft_print_indent.c \
        pft_print_d.c \
        pft_print_u.c \
        pft_print_o.c \
        pft_print_x.c \
        pft_print_f.c \
        pft_print_c.c \
        pft_print_s.c \
        pft_print_p.c \
        pft_print_percent.c \
        pft_print_other.c \
        pft_calculator.c \
        pft_calculate_f.c \
        pft_cleaner.c \

OBJ_DIR = ./obj/
OBJ_LIBFTPRINTF_MODULE = $(addprefix $(OBJ_DIR), $(LIBFTPRINTF_MODULE:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_LIBFTPRINTF_MODULE)
	@ar rc $(NAME) $(OBJ_LIBFTPRINTF_MODULE)
	@ranlib $(NAME)
	@printf "$(GREEN)RT:\t$(YELLOW)%-90s$(GREEN)[done]$(NONE)\n" $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c $(LIBFTPRINTF_HEADER)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(LIBFTPRINTF_INC) $< -o $@

norm:
	@norminette $(LIBFTPRINTF_HEADER) $(LIBFTPRINTF_MODULE)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean : clean
	@/bin/rm -f $(NAME)

re: fclean all