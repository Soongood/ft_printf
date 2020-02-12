#include "ft_printf.h"

int		handler(t_str *line, va_list list)
{
	if (*line->type == 's')
		return (s_type(line, va_arg(list, char *)));
	if (*line->type == 'c')
		return (c_type(line, va_arg(list, int)));
	if (*line->type == 'p')
		return (p_type(line, (uintmax_t)va_arg(list, void *)));
	if ((*line->type == 'x' || *line->type == 'X' || *line->type == 'o' || *line->type == 'u'))
	{
		get_num_u(line, list);
		if (*line->type == 'o')
			line->base = 8;
		else if ((*line->type == 'x' || *line->type == 'X') && (line->base = 16))
				if (*line->type == 'X')
					line->letter = 'A';
		return (u_type(line, u_base(line)));
	}
	get_num(line, list);
	if (*line->type == 'd' || *line->type == 'i')
	{
		if (line->num < 0)
			ft_abs(line);
		return (i_type(line, base(line)));
	}
	if (*line->type == 'f')
		return (f_type(line));
	return (OK);
}