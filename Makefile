NAME = libftprintf.a
SRCS = $(addprefix ./srcs/, ft_printf base get_num handler is parsing type_f types others)
O_FILES = $(addsuffix .o, $(SRCS))
LIBFT = ./libft/libft.a
CFLAGS = -Wall -Wextra -Werror -I ./includes

all: $(NAME)

$(NAME): $(O_FILES) $(LIBFT)
	ar rc $(NAME) $(O_FILES)
	ranlib $(NAME)

$(LIBFT)::
	make -C ./libft

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	/bin/rm -f $(addsuffix .o,$(SRCS))

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
