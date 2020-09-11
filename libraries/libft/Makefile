NAME = libft.a

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

FLAGS = -Wall -Wextra -Werror
CC = gcc

LIBFT_HEADERS = inc/libft.h
LIBFT_INC = -Iinc/

LIBFT_MODULE = src/ft_strlen.c \
        src/ft_strlcat.c \
        src/ft_memcmp.c \
        src/ft_atoi.c \
        src/ft_isascii.c \
        src/ft_isprint.c \
        src/ft_tolower.c \
        src/ft_toupper.c \
        src/ft_isalnum.c \
        src/ft_isalpha.c \
        src/ft_isdigit.c \
        src/ft_strcmp.c \
        src/ft_strncmp.c \
        src/ft_strdup.c \
        src/ft_strchr.c \
        src/ft_strrchr.c \
        src/ft_strstr.c \
        src/ft_strnstr.c \
        src/ft_strcat.c \
        src/ft_strncat.c \
        src/ft_strcpy.c \
        src/ft_strncpy.c \
        src/ft_bzero.c \
        src/ft_memset.c \
        src/ft_memchr.c \
        src/ft_memcpy.c \
        src/ft_memccpy.c \
        src/ft_memmove.c \
        src/ft_memalloc.c \
        src/ft_memdel.c \
        src/ft_strnew.c \
        src/ft_strdel.c \
        src/ft_strclr.c \
        src/ft_striter.c \
        src/ft_striteri.c \
        src/ft_strmap.c \
        src/ft_strmapi.c \
        src/ft_strequ.c \
        src/ft_strnequ.c \
        src/ft_strsub.c \
        src/ft_strjoin.c \
        src/ft_strtrim.c \
        src/ft_strsplit.c \
        src/ft_itoa.c \
        src/ft_putchar.c \
        src/ft_putstr.c \
        src/ft_putendl.c \
        src/ft_putnbr.c \
        src/ft_putchar_fd.c \
        src/ft_putstr_fd.c \
        src/ft_putendl_fd.c \
        src/ft_putnbr_fd.c \
        src/ft_lstnew.c \
        src/ft_lstdelone.c \
        src/ft_lstdel.c \
        src/ft_lstadd.c \
        src/ft_lstiter.c \
        src/ft_lstmap.c \
        src/ft_abs.c \
        src/ft_dabs.c \
        src/ft_strrev.c \
        src/ft_lstlen.c \
        src/ft_lstsplit.c \
        src/ft_lstabi.c \
        src/ft_wordcnt.c \
        src/ft_strstrsplit.c \
        src/get_next_line.c \
        src/ft_itoa_base.c \
        src/ft_printf.c \
        src/ft_del.c \
        src/ft_dlstnew.c \
        src/ft_dlstdel.c \
        src/ft_dlstdelone.c \
        src/ft_dlstsplit.c \
        src/ft_dlstargv.c \
        src/ft_dlstlen.c \
        src/ft_strlen.c \
        src/ft_strlcat.c \
        src/ft_error.c \
        src/ft_strsplit_del.c \
        src/ft_get_text_file.c \
        src/ft_str_to_upper.c \
        src/ft_strlen_rus.c \

OBJ_DIR = ./obj/
OBJ_LIBFT_MODULE = $(addprefix $(OBJ_DIR), $(LIBFT_MODULE:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_LIBFT_MODULE)
	@ar rc $(NAME) $(OBJ_LIBFT_MODULE)
	@ranlib $(NAME)
	@printf "$(GREEN)RT:\t$(YELLOW)%-90s$(GREEN)[done]$(NONE)\n" $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c $(LIBFT_HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(LIBFT_INC) $< -o $@

norm:
	@norminette $(LIBFT_HEADERS) $(LIBFT_MODULE)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean : clean
	@/bin/rm -f $(NAME)

re: fclean all