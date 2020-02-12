#include "../includes/ft_printf.h"

static void     parser_one(const char **chunk, t_str *line)
{
	char	i;
	char	tmp[5];
	long	result;

	i = 0;
	result = 0;
	is_flags(line, chunk);
	ft_bzero(&tmp, sizeof(tmp));
	while (ft_isdigit(**chunk))
	{
		*(tmp + i) = *(*chunk)++;
		result = 10 * result + (*(tmp + i++) - '0');
	}
	if (*tmp)
		line->width = result, ft_bzero(&tmp, i);
	i = 0;
	result = 0;
	if (**chunk == '.' ? *(*(chunk))++ : NOTHING)
		while (ft_isdigit(**chunk))
		{
			*(tmp + i) = *(*chunk)++;
			result = 10 * result + (*(tmp + i++) - '0');
		}
	line->precision = result;
}

static int      parser_sec(t_str *line, const char **chunk)
{
	if (is_type(**chunk))
		line->type[0] = *(*chunk)++;
	else if (*(*chunk + 1))
	{
		if (is_specifier(**chunk) && (**chunk == *(*chunk + 1)) && is_type(*(*chunk + 2)))
			line->specifier[1] = *(*chunk)++;
		else if ((is_specifier(**chunk) || (**chunk) == 'L') && is_type(*(*chunk + 1)))
			;
		else
			return (EXIT_FAILURE);
		line->specifier[0] = *(*chunk)++;
		line->type[0] = *(*chunk)++;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void            parsing(const char **chunk, t_str *line, va_list list)
{
	parser_one(chunk, line);
	if (!(parser_sec(line, chunk)))
		if (handler(line, list))
			;//handler_bonus;
}
