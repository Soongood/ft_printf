NAME = libftprintf.a
OBJ_DIR = obj/
SRCS_DIR = srcs/
FUN = ft_printf base get_num handler is parsing type_f types others
SRCS = $(addsuffix .c, $(FUN))
O_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FUN)))
LIBFT = ./libft/libft.a
CFLAGS = -Wall -Wextra -Werror -I ./includes
PRINT = @echo "\e[0;34mBuilding... \t$(NAME)\t$@\e[0m"

.DEFAULT_GOAL := default
.PHONY: all clean fclean re default test

default:
	@$(MAKE) --no-print-directory all

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	$(PRINT)
	@mkdir $(OBJ_DIR)
	@echo "\e[0;32mObject directory is created\e[0m"

$(NAME): $(O_FILES) $(LIBFT)
	@echo "\e[0;34mCopying... \t$(LIBFT) to $(NAME)\e[0m"
	@cp $(LIBFT) $(NAME)
	@echo "\e[0;34mArchiving... \t$@\e[0m"
	@ar rc $(NAME) $(O_FILES)
	@ranlib $(NAME)
	@echo "\e[0;32m$@ is archived\e[0m"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	$(PRINT)
	@gcc $(CFLAGS) -o $@ -c $<

test: all
	$(PRINT)
	@gcc -w tests/main.c -L. -lftprintf -o test
	@echo "\e[0;32mTest file is created\e[0m"

$(LIBFT)::
	@make --no-print-directory -C ./libft

clean:
	@make --no-print-directory -C ./libft clean
	@echo "\e[0;34mCleaning...\e[0m"
	@/bin/rm -fr $(OBJ_DIR)
	@echo "\e[0;32m$(NAME): Object files are removed\e[0m"

fclean: clean
	@make --no-print-directory -C ./libft fclean
	@echo "\e[0;34mCleaning...\e[0m"
	@/bin/rm -f $(NAME) test
	@echo "\e[0;32m$(NAME): Lib, obj and test files are removed\e[0m"

re: fclean all
