NAME = libfts.a

ifeq ($(shell uname -s),Linux)
	CC := nasm
	FLAGS := -f elf64
else
	CC := /Users/ndudnicz/.brew/bin/nasm
	FLAGS := -f macho64
endif

CXX = gcc

NAME_TEST = run_tests

SRC_DIR = src

OBJ_DIR = obj

SRC =	ft_puts.s ft_strlen.s ft_bzero.s ft_isalpha.s ft_isdigit.s \
		ft_isalnum.s ft_isascii.s ft_isprint.s ft_isinrange.s \
		ft_tolower.s ft_toupper.s ft_strcat.s ft_memcpy.s ft_memset.s \
		ft_strdup.s ft_strchr.s ft_atoi.s ft_atol.s ft_putstr.s \
		ft_putstr_fd.s ft_putchar.s ft_putchar_fd.s ft_strcmp.s

OBJ = $(SRC:%.s=obj/%.o)

all: obj $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(CC) $(FLAGS) $< -o $@

obj:
	mkdir -p $(OBJ_DIR)

test:
	gcc -o $(NAME_TEST) tests/tests.c -I include $(NAME)
	./$(NAME_TEST)

clean:
		/bin/rm -f $(OBJ)

fclean: clean
		/bin/rm -f $(NAME) $(NAME_TEST) $(NAME_TEST_CAT)

re: clean fclean all
