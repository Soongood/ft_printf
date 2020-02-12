#include "ft_printf.h"

int		is_specifier(char chunk)
{
	return (chunk == 'l' || chunk == 'h');
}

int		is_type(char chunk)
{
	return (chunk == 'p' || chunk == 'c' || chunk == 's' ||
			chunk == 'd' || chunk == 'i' || chunk == 'o' ||
			chunk == 'u' || chunk == 'x' || chunk == 'X' ||
			chunk == 'f' || chunk == 'b');
}

void	is_flags(t_str *line, const char **chunk)
{
	while (**chunk == ' ' || **chunk == '#' || **chunk == '+' || **chunk == '-' || **chunk == '0')
	{
		if (**chunk == '-')
			line->flags |= MINUS;
		else if (**chunk == '+')
			line->flags |= PLUS;
		else if (**chunk == ' ')
			line->flags |= SPACE;
		else if (**chunk == '0')
			line->flags |= ZERO;
		else if (**chunk == '#')
			line->flags |= SHARP;
		(*chunk)++;
	}
}