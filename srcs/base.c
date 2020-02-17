#include "../includes/ft_printf.h"

char	u_base(t_str *line)
{
	uintmax_t tmp;

	line->tmp = 1;
	tmp = line->num_u;
	while (tmp /= line->base)
		line->tmp++;
	return (line->tmp);
}

char	base(t_str *line)
{
	intmax_t tmp;

	line->tmp = 1;
	tmp = line->num;
	while (tmp /= line->base)
		line->tmp++;
	return (line->tmp);
}

int		base_num_u(t_str *line, uintmax_t number)
{
	char		num;

	if (number >= (uintmax_t)line->base)
		base_num_u(line, number / line->base);
	num = number % line->base;
	if (line->precision || (!line->precision && (line->num)))
		*line->ptr++ = (num >= 10) ? line->letter + num - 10 : '0' + num;
	else if (line->flags == (line->flags | PLUS) && !line->precision)
		*line->ptr++ = ' ';
	else
	 	line->width++;
	return (EXIT_SUCCESS);
}

int		base_num(t_str *line, intmax_t number)
{
	if (number >= line->base)
		base_num(line, number / line->base);
	if ((line->precision || (!line->precision && (line->num))) || *line->type == 'f')
		*line->ptr++ = '0' + number % line->base;
	else if (!line->num && !line->num_u && line->flags == (line->flags | PLUS) && line->width)
	{
		line->ptr--;
		*line->ptr++ = ' ';
		*line->ptr++ = '+';
	}
	else
	 	line->width++;
	return (EXIT_SUCCESS);
}
