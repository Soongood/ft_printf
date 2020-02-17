#include "../includes/ft_printf.h"

void sharp(t_str *line)
{
	if (*line->type != 'p' && !line->num_u)
		return ;
	*line->ptr++ = '0';
	*line->ptr++ = 'x';
}

void	loop_w(t_str *line, char num)
{
	if ((line->precision == -1 || (*line->type == 'f' && !line->precision)) && !num && line->num < 0)
	 	*line->ptr++ = '-';
	while (line->width-- > line->tmp)
		*line->ptr++ = !num ? '0' : ' ';
	if ((line->precision == -1 || (*line->type == 'f' && !line->precision)) && num && line->num < 0)
	 	*line->ptr++ = '-';
}

void	loop_p(t_str *line, char *u_base)
{
	int tmp;
	tmp = line->precision;
	while (line->precision-- > *u_base)
		*line->ptr++ = '0';
	line->precision = (line->num || line->num_u) ? 1 : tmp;
}