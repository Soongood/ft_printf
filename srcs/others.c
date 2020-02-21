#include "../includes/ft_printf.h"

void	ptr_mv(t_str *line, char letter)
{
	if (line->length++ < BUF_SIZE)
		*line->ptr++ = letter;
//	else
}

void	init_str(t_str *line)
{
	static unsigned int size = sizeof(*line) - BUF_SIZE;

	ft_bzero(line, !line->length ? sizeof(*line) : size + line->length);
	line->ptr = line->str;
	line->letter = 'a';
	line->base = 10;
	line->precision = -1;
}

void sharp(t_str *line)
{
	if (line->type != 'p' && line->type != 'b' && !line->num_u)
		return ;
	if (line->type == 'b' && line->num_u)
		ptr_mv(line, '-');
//		*line->ptr++ = '-';
	ptr_mv(line, '0');
//	*line->ptr++ = '0';
	ptr_mv(line, line->type == 'b' ? 'b' : 'x');
//	*line->ptr++ = line->type == 'b' ? 'b' : 'x';
}

void	loop_w(t_str *line, char num)
{
	if ((line->precision == -1 || (line->type == 'f' && !line->precision)) && !num && line->num < 0)
		ptr_mv(line, '-');
//	 	*line->ptr++ = '-';
	while (line->width-- > line->tmp)
		ptr_mv(line, !num ? '0' : ' ');
//		*line->ptr++ = !num ? '0' : ' ';
	if ((line->precision == -1 || (line->type == 'f' && !line->precision)) && num && line->num < 0)
		ptr_mv(line, '-');
//	 	*line->ptr++ = '-';
}

void	loop_p(t_str *line, char *u_base)
{
	int tmp;
	tmp = line->precision;
	while (line->precision-- > *u_base)
		ptr_mv(line, '0');
//		*line->ptr++ = '0';
	line->precision = (line->num || line->num_u) ? 1 : tmp;
}