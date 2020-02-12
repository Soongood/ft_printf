#include "ft_printf.h"

int	c_type(t_str *line, int letter)
{
	char flag;

	flag = 0;
	if (line->width)
		if((line->flags == (line->flags | MINUS)) && (flag = -1))
			*line->ptr++ = letter;
	while (--line->width > 0)
		*line->ptr++ = ' ';
	if (!flag)
		*line->ptr++ = letter;
	return (OK);
}

int		s_type(t_str *line, char *string)
{
	int		size;
	int		tmp_pre;
	char	flag;

	flag = 0;
	size = ft_strlen(string);
	tmp_pre = line->precision;
	if (line->width)
	{
		if((line->flags == (line->flags | MINUS)) && (flag = -1))
			while (line->precision ? *string && tmp_pre-- : *string)
				*line->ptr++ = *string++;
		while (line->precision ? line->width-- > line->precision : line->width-- > size)
			*line->ptr++ = ' ';
		if (flag == -1)
			return (OK);
	}
	while (line->precision ? *string && tmp_pre-- : *string)
		*line->ptr++ = *string++;
	return (OK);
}

int		p_type(t_str *line, uintmax_t pointer)
{
	char		num;
	static char	rep = 3;

	if (pointer >= 16 && rep++)
		p_type(line, pointer / 16);
	if (rep != 3)
	{
		while (line->width-- > rep)
			*line->ptr++ = ' ';
		sharp(line);
		rep = 3;
	}
	num = pointer % 16;
	*line->ptr++ = (num >= 10) ? line->letter + num - 10 : '0' + num;
	return (OK);
}

int		u_type(t_str *line, char u_base)
{
	line->tmp = u_base > line->precision ? u_base : line->precision;
	line->tmp += ((*line->type == 'x' || *line->type == 'X') && (line->flags == (line->flags | SHARP))) ? 2 : 0;
	if ((line->flags == (line->flags | MINUS)))
	{
		if (((*line->type == 'x' || *line->type == 'X') && (line->flags == (line->flags | SHARP))))
			sharp(line);
		loop_p(line, &u_base);
		base_num_u(line, line->num_u);
		loop_w(line, 1);
		return (OK);
	}
	if (line->precision || !line->flags)
	{
		loop_w(line, 1);
		if ((*line->type == 'x' || *line->type == 'X') && (line->flags == (line->flags | SHARP)))
			sharp(line);
		loop_p(line, &u_base);	
	}
	else
	{
		if (((*line->type == 'x' || *line->type == 'X') && (line->flags == (line->flags | SHARP))))
			sharp(line);
		loop_w(line, 0);
	}
	base_num_u(line, line->num_u);
	return (OK);
}

int		i_type(t_str *line, char base)
{
	line->tmp = base > line->precision ? base : line->precision;
	line->tmp += (line->flags == (line->flags | PLUS) || line->num_u) ? 1 : 0;
	if ((line->flags == (line->flags | SPACE)) && (line->flags != (line->flags | PLUS)) && !line->num_u)
		*line->ptr++ = ' ';
	if ((line->flags == (line->flags | MINUS)))
	{
		if (line->flags == (line->flags | PLUS) && !line->num_u)
			*line->ptr++ = '+';
		if (line->num_u)
			*line->ptr++ = '-';
		loop_p(line, &base);
		!line->num_u ? base_num(line, line->num) : base_num_u(line, line->num_u);
		loop_w(line, 1);
		return (OK);
	}
	if (!line->precision && (line->flags == (line->flags | ZERO)) && (line->flags == (line->flags | PLUS)) && !line->num_u && (line->letter = 'A'))
		*line->ptr++ = '+';
	loop_w(line, (!line->precision && (line->flags == (line->flags | ZERO))) ? 0 : 1);
	 if (line->num_u && *line->type != 'f')
	 	*line->ptr++ = '-';
	if (line->flags == (line->flags | PLUS) && !line->num_u && (line->letter == 'a'))
		*line->ptr++ = '+';
	if (line->precision || (line->flags == (line->flags | ZERO)))
		loop_p(line, &base);	
	!line->num_u ? base_num(line, line->num) : base_num_u(line, line->num_u);
	return (OK);
}