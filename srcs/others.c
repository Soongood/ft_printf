#include "../includes/ft_printf.h"

void sharp(t_str *line)
{
	*line->ptr++ = '0';
	*line->ptr++ = 'x';
}

void	loop_w(t_str *line, char num)
{
	if (*line->type == 'f' && (line->num < 0) && (line->precision >= 0) && !num)
		*line->ptr++ = '-';
	while (line->width-- > line->tmp)
		*line->ptr++ = num == 1 ? ' ' : '0';
	if (*line->type == 'f' && line->num_u && (line->precision >= 0) && (num == 1))
		*line->ptr++ = '-';
}

void	loop_p(t_str *line, char *u_base)
{
	while (line->precision-- > *u_base)
		*line->ptr++ = '0';
}
