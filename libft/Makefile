# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobbin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/17 15:48:48 by trobbin           #+#    #+#              #
#    Updated: 2019/09/24 21:54:05 by trobbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJ_DIR = obj/
SRCS_DIR = srcs/
FLAGS = -Wall -Wextra -Werror
FUNCTIONS = ft_atoi ft_bzero ft_isascii ft_isdigit ft_isalpha ft_isalnum ft_isblank ft_islower ft_isupper ft_isprint ft_itoa ft_lstadd ft_lstaddback ft_lstdel ft_lstdelone ft_lstiter ft_lstnew ft_lstmap ft_memalloc ft_memdel ft_memdelarr ft_memchr ft_memcmp ft_memcpy ft_memccpy ft_memset ft_memmove ft_putchar ft_putchar_fd ft_putnbr ft_putnbr_fd ft_putendl ft_putendl_fd ft_putstr ft_putstr_fd ft_strcmp ft_strncmp ft_strlen ft_strcpy ft_strnew ft_strdel ft_strclr ft_strcat ft_strequ ft_strnequ ft_striter ft_striteri  ft_strmap ft_strmapi ft_strncat ft_strncpy ft_strstr ft_strnstr ft_strtrim ft_strsub ft_strlcat ft_strchr ft_strrchr ft_strdup ft_strjoin ft_strsplit ft_toupper ft_tolower
SRCS = $(addsuffix .c, $(FUNCTIONS))
O_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FUNCTIONS)))
PRINT = @echo "\e[0;34mBuilding... \t$(NAME)\t$@\e[0m"

.DEFAULT_GOAL := default
.PHONY: all clean fclean re default

default:
	@$(MAKE) --no-print-directory all

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	$(PRINT)
	@mkdir $(OBJ_DIR)
	@echo "\e[0;32mObject directory is created\e[0m"

$(NAME): $(O_FILES)
	@echo "\e[0;34mArchiving... \t$@\e[0m"
	@ar rc $(NAME) $(O_FILES)
	@ranlib $(NAME)
	@echo "\e[0;32m$@ is archived\e[0m"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	$(PRINT)
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@echo "\e[0;34mCleaning...\e[0m"
	@/bin/rm -fr $(OBJ_DIR)
	@echo "\e[0;32m$(NAME): Object files are removed\e[0m"

fclean: clean
	@echo "\e[0;34mCleaning...\e[0m"
	@/bin/rm -f $(NAME)
	@echo "\e[0;32m$(NAME): Lib and obj files are removed\e[0m"

re: fclean all
