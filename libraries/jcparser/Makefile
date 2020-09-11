NAME = libjcparser.a

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

FLAGS = -Wall -Wextra -Werror
CC = gcc

LIBFT_INC = ../libft/inc
JCPARSER_INC = include/
INCLUDES = -I$(LIBFT_INC) -I$(JCPARSER_INC)

JCPARSER_HEADERS = include/jc_data.h \
		include/jc_parser.h \
		include/jcp_parser.h \

JCPARSER_MODULE = private/jcp_create_t_jcp_object.c \
        private/jcp_skip_whitespaces.c \
        private/jcp_free_tree.c \
        private/jcp_get_main_object.c \
        private/jcp_get_elem_by_idx.c \
        private/jcp_check_for_number.c \
        private/jcp_get_value_of_obj_or_arr.c \
        private/jcp_get_value_of_null.c \
        private/jcp_get_value_of_bool.c \
        private/jcp_get_value_of_str.c \
        private/jcp_get_value_of_num.c \
        private/jcp_get_value_by_type.c \
        private/jcp_get_object_name.c \
        private/jcp_get_element.c \
        private/jcp_get_object.c \
        private/jcp_parent_dot_child.c \
        private/jcp_get_obj_by_key.c \
        private/jcp_field_with_index.c \
        private/jcp_str_of_types.c \
        private/jcp_print_bad_type_error.c \
        api/jc_get_float.c \
        api/jc_get_field.c \
        api/jc_clear_all.c \
        api/jc_get_string.c \
        api/jc_additional_utils.c \
        api/jc_get_bool.c \

OBJ_DIR = ./obj/
OBJ_JCPARSER_MODULE = $(addprefix $(OBJ_DIR), $(JCPARSER_MODULE:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_JCPARSER_MODULE)
	@ar rc $(NAME) $(OBJ_JCPARSER_MODULE)
	@ranlib $(NAME)
	@printf "$(GREEN)RT:\t$(YELLOW)%-90s$(GREEN)[done]$(NONE)\n" $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c $(JCPARSER_HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

norm:
	@norminette $(JCPARSER_HEADERS) $(JCPARSER_MODULE)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean : clean
	@/bin/rm -f $(NAME)

re: fclean all