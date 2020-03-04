# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/17 15:48:48 by trobbin           #+#    #+#              #
#    Updated: 2020/02/27 13:50:45 by trobbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJ_DIR = obj/
SRCS_DIR = srcs/
FLAGS = -Wall -Wextra -Werror
FUNCTIONS = ft_atoi ft_bzero ft_isascii ft_isdigit ft_isalpha ft_isalnum ft_isblank ft_islower ft_isupper ft_isprint ft_itoa ft_lstadd ft_lstaddback ft_lstdel ft_lstdelone ft_lstiter ft_lstnew ft_lstmap ft_memalloc ft_memdel ft_memdelarr ft_memchr ft_memcmp ft_memcpy ft_memccpy ft_memset ft_memmove ft_putchar ft_putchar_fd ft_putnbr ft_putnbr_fd ft_putendl ft_putendl_fd ft_putstr ft_putstr_fd ft_strcmp ft_strncmp ft_strlen ft_strcpy ft_strnew ft_strdel ft_strclr ft_strcat ft_strequ ft_strnequ ft_striter ft_striteri  ft_strmap ft_strmapi ft_strncat ft_strncpy ft_strstr ft_strnstr ft_strtrim ft_strsub ft_strlcat ft_strchr ft_strrchr ft_strdup ft_strjoin ft_strsplit ft_toupper ft_tolower
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FUNCTIONS)))
O_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FUNCTIONS)))
vpath %.c $(SRCS_DIR)
vpath %.h includes/
BLUE = \x1B[34m
GREEN = \x1B[32m
PRINT = echo "$(BLUE)Building... \t$(NAME)\t$@\x1B[0m"

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(O_FILES)
	@echo "$(BLUE)Archiving... \t$@\x1B[0m"
	@ar rc $(NAME) $(O_FILES)
	@ranlib $(NAME)
	@echo "$(GREEN)$@ is archived\x1B[0m"

$(OBJ_DIR):
	@$(PRINT)
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)Object directory is created\x1B[0m"

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	@$(PRINT)
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@echo "$(BLUE)Cleaning...\x1B[0m"
	@/bin/rm -fr $(OBJ_DIR)
	@echo "$(GREEN)$(NAME): Object files are removed\x1B[0m"

fclean: clean
	@echo "$(BLUE)Cleaning...\x1B[0m"
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)$(NAME): Lib and obj files are removed\x1B[0m"

re: fclean all
