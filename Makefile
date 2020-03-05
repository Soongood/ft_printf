# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/23 15:24:33 by trobbin           #+#    #+#              #
#    Updated: 2020/03/05 01:09:46 by trobbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
OBJ_DIR = obj/
SRCS_DIR = srcs/
FUN = ft_printf base get_num handler is parsing type_f types others buf binary minus
SRCS = $(addsuffix .c, $(FUN))
O_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FUN)))
LIBFT = ./libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g -I ./includes
BLUE = \x1B[34m
GREEN = \x1B[32m
PRINT = echo "$(BLUE)Building... \t$(NAME)\t$@\x1B[0m"

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ_DIR) $(O_FILES) $(LIBFT)
	@echo "$(BLUE)Copying... \t$(LIBFT) to $(NAME)\x1B[0m"
	@cp $(LIBFT) $(NAME)
	@echo "$(BLUE)Archiving... \t$@\x1B[0m"
	@ar rc $(NAME) $(O_FILES)
	@ranlib $(NAME)
	@echo "$(GREEN)$@ is archived\x1B[0m"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJ_DIR)
	@$(PRINT)
	@gcc $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@$(PRINT)
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)Object directory is created\e[0m"

test: all
	@$(PRINT)
	@gcc -w -g tests/main.c -L. -lftprintf -o test
	@echo "$(GREEN)Test file is created\x1B[0m"

$(LIBFT)::
	@make --no-print-directory -C ./libft

clean:
	@make --no-print-directory -C ./libft clean
	@echo "$(BLUE)Cleaning...\x1B[0m"
	@/bin/rm -fr $(OBJ_DIR)
	@echo "$(GREEN)$(NAME): Object files are removed\x1B[0m"

fclean: clean
	@make --no-print-directory -C ./libft fclean
	@echo "$(BLUE)Cleaning...\x1B[0m"
	@/bin/rm -f $(NAME) test
	@echo "$(GREEN)$(NAME): Lib, obj and test files are removed\x1B[0m"

re: fclean all
