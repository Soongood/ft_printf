#include "../includes/ft_printf.h"

void	init_str(t_str *line)
{
	static unsigned int size = sizeof(*line) - BUF_SIZE;

	if (!line->length)
		ft_bzero(line, sizeof(*line));
	else
		ft_bzero(line, line->length <= BUF_LIMIT ? size + line->length : sizeof(*line));	
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
	ptr_mv(line, '0');
	ptr_mv(line, line->type == 'b' ? 'b' : 'x');
}

void	loop_w(t_str *line, char num)
{
	if ((line->precision == -1 || (line->type == 'f' && !line->precision)) && !num && line->num < 0)
		ptr_mv(line, '-');
	while (line->width-- > line->tmp)
		ptr_mv(line, !num ? '0' : ' ');
	if ((line->precision == -1 || (line->type == 'f' && !line->precision)) && num && line->num < 0)
		ptr_mv(line, '-');
}

void	loop_p(t_str *line, char *u_base)
{
	int tmp;
	tmp = line->precision;
	while (line->precision-- > *u_base)
		ptr_mv(line, '0');
	line->precision = (line->num || line->num_u) ? 1 : tmp;
}