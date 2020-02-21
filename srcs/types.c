#include "../includes/ft_printf.h"

int	c_type(t_str *line, int letter)
{
	if (line->type == 'b')
	{
		if (letter < 0)
		{
			line->num_u = ~letter + 1;
			line->flags &= 253;
		}
		if (!letter)
				sharp(line);
		line->base = 2;
		p_type(line, line->num_u ? line->num_u : (uintmax_t)letter);
		return (EXIT_SUCCESS);
	}
	if (line->width)
		if((line->flags == (line->flags | MINUS)) && (line->letter = 'A'))
			ptr_mv(line, letter);
//			*line->ptr++ = letter;
	while (--line->width > 0)
		ptr_mv(line, ' ');
//		*line->ptr++ = ' ';
	if ((line->letter == 'a'))
		if (letter)
			ptr_mv(line, letter);
//			*line->ptr++ = letter;
	return (EXIT_SUCCESS);
}

int		s_type(t_str *line, char *string)
{
	if (!string)
	{
		line->precision = line->precision < 6 && line->precision != -1 ? 0 : 6;
		s_type(line, "(null)");
		return (EXIT_SUCCESS);
	}
	line->num = (intmax_t)ft_strlen(string);
	line->prec_f = line->precision;
	if (line->width)
	{
		if((line->flags == (line->flags | MINUS)) && (line->letter = 'A') && line->precision)
			while (*string && line->prec_f--)
				ptr_mv(line, *string++);
//				*line->ptr++ = *string++;
		while ((line->precision >= 0 && line->precision < line->num) ? line->width-- > line->precision : line->width-- > line->num)
			ptr_mv(line, ' ');
//			*line->ptr++ = ' ';
		if (line->letter == 'A')
			return (EXIT_SUCCESS);
	}
	while (*string && line->prec_f--)
		ptr_mv(line, *string++);
//		*line->ptr++ = *string++;
	return (EXIT_SUCCESS);
}

int		p_type(t_str *line, uintmax_t pointer)
{
	static char	rep = 3;

	line->base = line->type == 'b' ? 2 : 16;
	if (pointer >= (uintmax_t)line->base && rep++)
		p_type(line, pointer / line->base);
	if (rep != 3)
	{
		while (((line->flags != (line->flags | ZERO) || ((line->flags == (line->flags | ZERO) && line->precision < line->width && line->precision != -1))) &&
				(((line->flags == (line->flags | PLUS)) || (line->flags == (line->flags | SPACE))) ? --line->width > rep : line->width-- > rep)))
			ptr_mv(line, ' ');
//			*line->ptr++ = ' ';
		if ((line->flags == (line->flags | PLUS)) || (line->flags == (line->flags | SPACE)))
			ptr_mv(line, line->flags == (line->flags | PLUS) ? '+' : ' ');
//			*line->ptr++ = line->flags == (line->flags | PLUS) ? '+' : ' ';
		sharp(line);
		while (((line->flags == (line->flags | ZERO)) && line->precision == -1 ? line->width-- > rep : line->precision-- > rep - 2))
			ptr_mv(line, '0');
//			*line->ptr++ = '0';
		rep = 3;
	}
	if (!pointer && line->type != 'b')
	{
		line->precision = 5;
		s_type(line, "(nil)");
		return (EXIT_SUCCESS);
	}
	line->tmp = pointer % line->base;
	ptr_mv(line, (line->tmp >= 10) ? line->letter + line->tmp - 10 : '0' + line->tmp);
//	*line->ptr++ = (line->tmp >= 10) ? line->letter + line->tmp - 10 : '0' + line->tmp;
	return (EXIT_SUCCESS);
}

int		u_type(t_str *line, char u_base)
{
	line->tmp = u_base > line->precision ? u_base : line->precision;
	line->tmp += ((line->type == 'x' || line->type == 'X') && line->num_u && (line->flags == (line->flags | SHARP))) ? 2 : 0;
	if ((line->flags == (line->flags | MINUS)))
	{
		if (((line->type == 'x' || line->type == 'X') && (line->flags == (line->flags | SHARP))))
			sharp(line);
		loop_p(line, &u_base);
		base_num_u(line, line->num_u);
		loop_w(line, 1);
		return (EXIT_SUCCESS);
	}
	if (line->precision > 0 || !line->flags || (line->flags == (line->flags | PLUS)))
	{
		loop_w(line, 1);
		if ((line->type == 'x' || line->type == 'X') && (line->flags == (line->flags | SHARP)))
			sharp(line);
		loop_p(line, &u_base);	
	}
	else
	{
		if (((line->type == 'x' || line->type == 'X') && (line->flags == (line->flags | SHARP))))
			sharp(line);
		loop_w(line, 0);
	}
	base_num_u(line, line->num_u);
	return (EXIT_SUCCESS);
}

int		i_type(t_str *line, char base)
{
	line->tmp = base > line->precision ? base : line->precision;
	line->tmp += (line->flags == (line->flags | PLUS) || line->num_u) ? 1 : 0;
	if ((line->flags == (line->flags | SPACE)) && (line->flags != (line->flags | PLUS)) && (line->flags != (line->flags | SHARP)) && !line->num_u)
	{
		ptr_mv(line, ' ');
//		*line->ptr++ = ' ';
		line->width--;
	}
	if ((line->flags == (line->flags | MINUS)))
	{
		if (line->flags == (line->flags | PLUS) && !line->num_u)
			ptr_mv(line, '+');
//			*line->ptr++ = '+';
		if (line->num_u)
			ptr_mv(line, '-');
//			*line->ptr++ = '-';
		loop_p(line, &base);
		!line->num_u ? base_num(line, line->num) : base_num_u(line, line->num_u);
		loop_w(line, 1);
		return (EXIT_SUCCESS);
	}
	if (line->precision == -1 && (line->flags == (line->flags | ZERO)) && (line->flags == (line->flags | PLUS)) && !line->num_u && (line->letter = 'A'))
		ptr_mv(line, '+');
//		*line->ptr++ = '+';
	loop_w(line, (line->precision == -1 && (line->flags == (line->flags | ZERO))) ? 0 : 1);
	if (line->num_u && line->type != 'f' && line->precision != -1)
		ptr_mv(line, '-');	
//		*line->ptr++ = '-';
	if (line->flags == (line->flags | PLUS) && !line->num_u && (line->letter == 'a'))
		ptr_mv(line, '+');
//		*line->ptr++ = '+';
	if (line->precision || (line->flags == (line->flags | ZERO)))
		loop_p(line, &base);
	!line->num_u ? base_num(line, line->num) : base_num_u(line, line->num_u);
	return (EXIT_SUCCESS);
}
