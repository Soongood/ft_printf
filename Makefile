NAME = libftprintf.a
SRCS = $(addprefix ./srcs/, ft_printf base get_num handler is parsing type_f types others)
O_FILES = $(addsuffix .o, $(SRCS))
LIBFT = ./libft/libft.a
CFLAGS = -Wall -Wextra -Werror -I ./includes
TEST = tests

all: $(NAME)

$(NAME): $(O_FILES) $(LIBFT)
	ar rc $(NAME) $(O_FILES)
	ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

test: $(NAME) libft.a
	gcc -L. $(TEST)/main.c -lftprintf -lft -o test

libft.a: $(LIBFT)
	cp $(LIBFT) .

$(LIBFT)::
	make -C ./libft

clean:
	/bin/rm -f $(addsuffix .o,$(SRCS))
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME) ft_test libft.a
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re