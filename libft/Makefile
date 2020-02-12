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
FLAGS = -Wall -Wextra -Werror
FUNCTIONS = ft_atoi ft_bzero ft_isascii ft_isdigit ft_isalpha ft_isalnum ft_isblank ft_islower ft_isupper ft_isprint ft_itoa ft_lstadd ft_lstaddback ft_lstdel ft_lstdelone ft_lstiter ft_lstnew ft_lstmap ft_memalloc ft_memdel ft_memdelarr ft_memchr ft_memcmp ft_memcpy ft_memccpy ft_memset ft_memmove ft_putchar ft_putchar_fd ft_putnbr ft_putnbr_fd ft_putendl ft_putendl_fd ft_putstr ft_putstr_fd ft_strcmp ft_strncmp ft_strlen ft_strcpy ft_strnew ft_strdel ft_strclr ft_strcat ft_strequ ft_strnequ ft_striter ft_striteri  ft_strmap ft_strmapi ft_strncat ft_strncpy ft_strstr ft_strnstr ft_strtrim ft_strsub ft_strlcat ft_strchr ft_strrchr ft_strdup ft_strjoin ft_strsplit ft_toupper ft_tolower
O_FILES = $(addsuffix .o, $(FUNCTIONS))

all: $(NAME)

$(NAME): $(O_FILES)
	ar rc $(NAME) $(O_FILES)
	ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	/bin/rm -f $(addsuffix .o,$(FUNCTIONS))

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
