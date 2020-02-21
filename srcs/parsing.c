#include "../includes/ft_printf.h"

static void     parser_one(const char **chunk, t_str *line, va_list list)
{
	is_flags(line, chunk);
	line->width = (**chunk == '*' && (*chunk)++) ? va_arg(list, int) : get_res(chunk);
	if (**chunk == '.' && (*chunk)++)
		line->precision = (**chunk == '*' && (*chunk)++) ? va_arg(list, int) : get_res(chunk);
	if (line->width < 0)
	{
		line->width = ~line->width + 1;
		line->flags |= MINUS;
	}
	if (line->precision < -1)
			line->precision = -1;
}

static int      parser_sec(t_str *line, const char **chunk)
{
	if (is_type(**chunk))
		line->type = *(*chunk)++;
	else if (*(*chunk + 1))
	{
		if (is_specifier(**chunk) && (**chunk == *(*chunk + 1)) && is_type(*(*chunk + 2)))
			line->specifier[1] = *(*chunk)++;
		else if ((is_specifier(**chunk) || (**chunk) == 'L') && is_type(*(*chunk + 1)))
			;
		else
			return (EXIT_FAILURE);
		line->specifier[0] = *(*chunk)++;
		line->type = *(*chunk)++;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	parsing(const char **chunk, t_str *line, va_list list)
{
	parser_one(chunk, line, list);
	if (!(parser_sec(line, chunk)))
		handler(line, list);
}
