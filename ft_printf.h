#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MINUS 1
# define PLUS 2
# define SPACE 4
# define SHARP 8
# define ZERO 16

#include "libft.h"

int ft_printf(const char *format, ...);

#endif