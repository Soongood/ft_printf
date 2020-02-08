#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <ieee754.h>


/* 
Conversions: 
		1) csp
		2) diouxX with flags hh, h, l and ll.
		3) f with the flags: l and L

You must manage %%
You must manage the flags #0-+ and space
You must manage the minimum field-width
You must manage the precision
*/

typedef struct			s_str
{
	uint16_t			flags;
	intmax_t			num;
	uintmax_t			num_u;
	double				num_d;
	char				tmp;
	int					width;
	int					precision;
	char				base;
	char				letter;
	char				specifier[2];
	char				type[1];
	char				str[5000];
	char				*ptr;
}						t_str; // не забыть выровнять

void	is_flags(t_str *line, char **chunk)
{
	while (**chunk == ' ' || **chunk == '#' || **chunk == '+' || **chunk == '-' || **chunk == '0')
	{
		if (**chunk == '-')
			line->flags |= MINUS;
		else if (**chunk == '+')
			line->flags |= PLUS;
		else if (**chunk == ' ')
			line->flags |= SPACE;
		else if (**chunk == '0')
			line->flags |= ZERO;
		else if (**chunk == '#')
			line->flags |= SHARP;
		(*chunk)++;
	}
}

void	parser_one(char **chunk, t_str *line)
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

int		is_type(char chunk)
{
	return (chunk == 'p' || chunk == 'c' || chunk == 's' ||
			chunk == 'd' || chunk == 'i' || chunk == 'o' ||
			chunk == 'u' || chunk == 'x' || chunk == 'X' ||
			chunk == 'f');
}

int		is_specifier(char chunk)
{
	return (chunk == 'l' || chunk == 'h');
}

int		parser_sec(t_str *line, char **chunk)
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
			return (1);
		line->specifier[0] = *(*chunk)++;
		line->type[0] = *(*chunk)++;
	}
	else
		return (1);
	return (0);
}

int		c_type(t_str *line, int letter)
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
	return (0);
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
			return (0);
	}
	while (line->precision ? *string && tmp_pre-- : *string)
		*line->ptr++ = *string++;
	return (0);
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
	return (0);
}

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

	if (number >= line->base)
		base_num_u(line, number / line->base);
	num = number % line->base;
	*line->ptr++ = (num >= 10) ? line->letter + num - 10 : '0' + num;
	return (0);
}

int		base_num(t_str *line, intmax_t number)
{
	if (number >= line->base)
		base_num(line, number / line->base);
	*line->ptr++ = '0' + number % line->base;
	return (0);
}

void	loop_w(t_str *line, char num)
{
	while (line->width-- > line->tmp)
		*line->ptr++ = num == 1 ? ' ' : '0';
}

void	loop_p(t_str *line, char *u_base)
{
	while (line->precision-- > *u_base)
		*line->ptr++ = '0';
}

void	u_type(t_str *line, char u_base)
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
		return ;
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
}

void	i_type(t_str *line, char base)
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
		return ;
	}
	if (!line->precision && (line->flags == (line->flags | ZERO)) && (line->flags == (line->flags | PLUS)) && !line->num_u && (line->letter = 'A'))
		*line->ptr++ = '+';
	loop_w(line, (!line->precision && (line->flags == (line->flags | ZERO))) ? 0 : 1);
	if (line->num_u)
		*line->ptr++ = '-';
	if (line->flags == (line->flags | PLUS) && !line->num_u && (line->letter == 'a'))
		*line->ptr++ = '+';
	if (line->precision || (line->flags == (line->flags | ZERO)))
		loop_p(line, &base);	
	!line->num_u ? base_num(line, line->num) : base_num_u(line, line->num_u);
}

void	get_num(t_str *line, va_list list)
{
	// if ((line->specifier[0] == 'l') || (line->specifier[0] == 'L') || (line->type[0] == 'f'))
	// 	line->num = ((line->specifier[1] == 'l') || (line->specifier[0] == 'L')) ? 
	// 		(intmax_t)va_arg(list, long long int) : (intmax_t)va_arg(list, long int);
	// else if (line->specifier[0] == 'h')
	// 	line->num = line->specifier[1] == 'h' ? (intmax_t)((char)va_arg(list, int)) : (intmax_t)((short)va_arg(list, int));
	// else
	// 	line->num = (intmax_t)va_arg(list, int);
	if (*line->type != 'f')
	{
		if (line->specifier[0] == 'l')
			line->num = (line->specifier[1] == 'l') ? (intmax_t)va_arg(list, long long int) : (intmax_t)va_arg(list, long int);
		else if (line->specifier[0] == 'h')
			line->num = line->specifier[1] == 'h' ? (intmax_t)((char)va_arg(list, int)) : (intmax_t)((short)va_arg(list, int));
		line->num = (intmax_t)va_arg(list, int);
		return ;
	}
	if (line->specifier[0] == 'L')
		line->num_d = (long double)va_arg(list, long double);
	else
		line->num_d = (double)va_arg(list, double);
}

void	get_num_u(t_str *line, va_list list)
{
	if ((line->specifier[0] == 'l') || (line->specifier[0] == 'L'))
		line->num_u = ((line->specifier[1] == 'l') || (line->specifier[0] == 'L')) ? 
			(uintmax_t)va_arg(list, unsigned long long int) : (uintmax_t)va_arg(list, unsigned long int);
	else if (line->specifier[0] == 'h')
		line->num_u = line->specifier[1] == 'h' ? (uintmax_t)((char)va_arg(list, unsigned int)) : (uintmax_t)((short)va_arg(list, unsigned int));
	else
		line->num_u = (uintmax_t)va_arg(list, unsigned int);
}

void sharp(t_str *line)
{
	*line->ptr++ = '0';
	*line->ptr++ = 'x';
}

void	ft_abs(t_str *line)
{
	line->num_u = ~line->num + 1;
}

void	f_type(t_str *line)
{
	union ieee754_double pre;

	pre.d = line->num_d;
	printf("%u", pre.ieee.exponent);
	
}

void	handler(t_str *line, va_list list)
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
	{
		f_type(line);
		//i_type(line, base(line));
	}
}

int		parsing(char **chunk, t_str *line, va_list list)
{
	parser_one(chunk, line);
	if (!(parser_sec(line, chunk)))
		handler(line, list);
}

int	ft_printf(const char *format, ...)
{
	int		length;
	t_str	line;
	va_list	ap;

	ft_bzero(&line, sizeof(line));
	line.ptr = line.str;
	line.letter = 'a';
	line.base = 10;
	va_start(ap, format);
	while (*format)
		if (*format != '%')
			*line.ptr++ = *format++;
		else if (*format++ == '%' && *format == '%')
			*line.ptr++ = *format++;
		else
			parsing(&format, &line, ap);
	va_end(ap);
	length = ft_strlen(line.str);
	write(1, line.str, length);
	return (length);
}

int		main()
{
//	int   sum = 0;
//	char *arr = "HelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorlHelloWorl";
//	long int x = 9223372036854775808;
	float x = 10.3;
	long int y;

	y = (long int)x;

	printf("%li\n",y);
	
	ft_printf("ft_printf\t\t||%f|\n", x);
	printf("printf\t\t\t||%f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%15f|\n", x);
	printf("printf\t\t\t||%15f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%-15f|\n", x);
	printf("printf\t\t\t||%-15f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%- .15f|\n", x);
	printf("printf\t\t\t||%- .15f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%-0.15f|\n", x);
	printf("printf\t\t\t||%-0.15f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%-025.15f|\n", x);
	printf("printf\t\t\t||%-025.15f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%030.7f|\n", x);
	printf("printf\t\t\t||%030.7f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%0-25.6f|\n", x);
	printf("printf\t\t\t||%0-25.6f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%0+10.14f|\n", x);
	printf("printf\t\t\t||%0+10.14f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%0+15.6f|\n", x);
	printf("printf\t\t\t||%0+15.6f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||% 0.9f|\n", x);
	printf("printf\t\t\t||% 0.9f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%+08f|\n", x);
	printf("printf\t\t\t||%+08f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%+8f|\n", x);
	printf("printf\t\t\t||%+8f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%0 .6f|\n", x);
	printf("printf\t\t\t||%0 .6f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||% +7.9f|\n", x);
	printf("printf\t\t\t||% +7.9f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||% +7.6f|\n", x);
	printf("printf\t\t\t||% +7.6f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%+7.9f|\n", x);
	printf("printf\t\t\t||%+7.9f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%+07.6f|\n", x);
	printf("printf\t\t\t||%+07.6f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%+0f|\n", x);
	printf("printf\t\t\t||%+0f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%0.9f|\n", x);
	printf("printf\t\t\t||%0.9f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%07.6f|\n", x);
	printf("printf\t\t\t||%07.6f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%07.9f|\n", x);
	printf("printf\t\t\t||%07.9f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%0f|\n", x);
	printf("printf\t\t\t||%0f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%9.7f|\n", x);
	printf("printf\t\t\t||%9.7f|\n", x);
	printf("====================================================\n");
	ft_printf("ft_printf\t\t||%9.11f|\n", x);
	printf("printf\t\t\t||%9.11f|\n", x);

/* 	ft_printprintf|f("%li|\n", x);
	ft_printf("%15li|\n", x);
	ft_printf("%-15li|\n", x);
	ft_printf("%- .15li|\n", x);
	ft_printf("%-0.15li|\n", x);
	ft_printf("%-025.15li|\n", x);
	ft_printf("%030.7li|\n", x);
	ft_printf("%0-25.6li|\n", x);
	ft_printf("%0+10.14li|\n", x);
	ft_printf("%0+15.6li|\n", x);
	ft_printf("% 0.9li|\n", x);
	ft_printf("%+08li|\n", x);
	ft_printf("%+8li|\n", x);
	ft_printf("%0 .6li|\n", x);
	ft_printf("% +7.9li|\n", x);
	ft_printf("% +7.6li|\n", x);
	ft_printf("%+7.9li|\n", x);
	ft_printf("%+07.6li|\n", x);
	ft_printf("%+0li|\n", x);
	ft_printf("%0.9li|\n", x);
	ft_printf("%07.6li|\n", x);
	ft_printf("%07.9li|\n", x);
	ft_printf("%0li|\n", x);
	ft_printf("%9.7li|\n", x);
	ft_printf("%9.11li|\n", x); */

//	ft_printf("%-#7i|\n", x);
//	ft_printf("%-07i|\n", x);
//	ft_printf("%-7i|\n", x);
//	ft_printf("%#9.5i|\n", x); 
//	ft_printf("%-#9i|\n", x);
//	ft_printf("%-7.5i|\n", x);
//	ft_printf("%-#.5i|\n", x); 
	// ft_printf("%-#6i|\n", x);
 	// ft_printf("%#9.9i|\n", x);
	// ft_printf("%7.12i|\n", x);
	// ft_printf("%#7.12i|\n", x);
	// ft_printf("%#6.9i|\n", x);
	// ft_printf("%0#9i|\n", x);
	// ft_printf("%0-7.5i|\n", x);
	// ft_printf("%-0.5i|\n", x);
	// ft_printf("%0#15i|\n", x);
	// ft_printf("%0#3i|\n", x);
 	// ft_printf("%0#6i|\n", x); 
 	// ft_printf("%0#9.9i|\n", x);
	// ft_printf("%07.12i|\n", x);
	// ft_printf("%0#7.12i|\n", x);
	// ft_printf("%-0#6.9i|\n", x);
 	// ft_printf("%0#4.9i|\n", x);
	// ft_printf("%0-7.5i|\n", x);
	// ft_printf("%-0.5i|\n", x);
	// ft_printf("%0#15.5i|\n", x);
	// ft_printf("%09.5i|\n", x);
	// ft_printf("%07.12i|\n", x);
	// ft_printf("%0#7.12i|\n", x);
 	// ft_printf("%-0#6.9i|\n", x);
 	// ft_printf("%0#4.9i|\n", x);
	// ft_printf("%0#9.4i|\n", x);
	// ft_printf("% #9.4i|\n", x);
	// ft_printf("% 9.4i|\n", x);
	// ft_printf("%9.4i|\n", x);
	// ft_printf("%9.7i|\n", x);
	// ft_printf("%9.11i|\n", x);
// 	ft_printf("%0#9.4i|\n", x);
//	ft_printf("% #9.4i|\n", x);
//	ft_printf("% 9.4i|\n", x);
//	ft_printf("%9.4i|\n", x);
//	ft_printf("%9.7i|\n", x);
//	ft_printf("%9.11i|\n", x);

	printf("====================================================\n");


/*  printf("%i|\n", x);
	printf("%15i|\n", x);
	printf("%-15i|\n", x);
	printf("%- .15i|\n", x);
	printf("%-0.15i|\n", x);
	printf("%-025.15i|\n", x);
	printf("%030.7i|\n", x);
	printf("%0-25.6i|\n", x);
	printf("%0+10.14i|\n", x);
	printf("%0+15.6i|\n", x);
	printf("% 0.9i|\n", x);
	printf("%+08i|\n", x);
	printf("%+8i|\n", x);
	printf("%0 .6i|\n", x);
	printf("% +7.9i|\n", x);
	printf("% +7.6i|\n", x);
	printf("%+7.9i|\n", x);
	printf("%+07.6i|\n", x);
	printf("%+0i|\n", x);
	printf("%0.9i|\n", x);
	printf("%07.6i|\n", x);
	printf("%07.9i|\n", x);
	printf("%0i|\n", x);
	printf("%9.7i|\n", x);
	printf("%9.11i|\n", x);
 */
/* 	printf("%li|\n", x);
	printf("%15li|\n", x);
	printf("%-15li|\n", x);
	printf("%- .15li|\n", x);
	printf("%-0.15li|\n", x);
	printf("%-025.15li|\n", x);
	printf("%030.7li|\n", x);
	printf("%0-25.6li|\n", x);
	printf("%0+10.14li|\n", x);
	printf("%0+15.6li|\n", x);
	printf("% 0.9li|\n", x);
	printf("%+08li|\n", x);
	printf("%+8li|\n", x);
	printf("%0 .6li|\n", x);
	printf("% +7.9li|\n", x);
	printf("% +7.6li|\n", x);
	printf("%+7.9li|\n", x);
	printf("%+07.6li|\n", x);
	printf("%+0li|\n", x);
	printf("%0.9li|\n", x);
	printf("%07.6li|\n", x);
	printf("%07.9li|\n", x);
	printf("%0li|\n", x);
	printf("%9.7li|\n", x);
	printf("%9.11li|\n", x); */

//	printf("%0 .6i|\n", x);
//	printf("% +7.9i|\n", x);
//	printf("% +7.6i|\n", x);
//	printf("%+7.9i|\n", x);
//	printf("%+07.6i|\n", x);
//	printf("%+0i|\n", x);
//	printf("%0.9i|\n", x);
//	printf("%07.6i|\n", x);
//	printf("%07.9i|\n", x);
//	printf("%0i|\n", x);
//	printf("%i|\n", x);
//	printf("%7i|\n", x);
//	printf("%9.7i|\n", x);
//	printf("%9.11i|\n", x);
//	printf("%-#7i|\n", x);
//	printf("%-07i|\n", x);
//	printf("%-7i|\n", x);
//	printf("%#9.5i|\n", x); 
//	printf("%-#9i|\n", x);
//	printf("%-7.5i|\n", x);
//	printf("%-#.5i|\n", x); 
	// printf("%-#6i|\n", x);
 	// printf("%#9.9i|\n", x);
	// printf("%7.12i|\n", x);
	// printf("%#7.12i|\n", x);
	// printf("%#6.9i|\n", x);
	// printf("%0#9i|\n", x);
	// printf("%0-7.5i|\n", x);
	// printf("%-0.5i|\n", x);
	// printf("%0#15i|\n", x);
	// printf("%0#3i|\n", x);
// 	printf("%0#6i|\n", x); 
 	// printf("%0#9.9i|\n", x);
	// printf("%07.12i|\n", x);
	// printf("%0#7.12i|\n", x);
	// printf("%-0#6.9i|\n", x);
 	// printf("%0#4.9i|\n", x);
	// printf("%0-7.5i|\n", x);
	// printf("%-0.5i|\n", x);
	// printf("%0#15.5i|\n", x);
	// printf("%09.5i|\n", x);
	// printf("%07.12i|\n", x);
	// printf("%0#7.12i|\n", x);
 	// printf("%-0#6.9i|\n", x);
 	// printf("%0#4.9i|\n", x);
	// printf("%0#9.4i|\n", x);
	// printf("% #9.4i|\n", x);
	// printf("% 9.4i|\n", x);
	// printf("%9.4i|\n", x);
	// printf("%9.7i|\n", x);
	// printf("%9.11i|\n", x);
//	printf("%0#9.4i|\n", x);
//	printf("% #9.4i|\n", x);
//	printf("% 9.4i|\n", x);
//	printf("%9.4i|\n", x);
//	printf("%9.7i|\n", x);
//	printf("%9.11i|\n", x);

/*  ft_printf("%-#7X|\n", x);
	ft_printf("%-07X|\n", x);
	ft_printf("%-7X|\n", x);
 	ft_printf("%7X|\n", x);
	ft_printf("%+0x|\n", x);
	ft_printf("%#9.5x|\n", x); 
	ft_printf("%-#9x|\n", x);
	ft_printf("%-7.5x|\n", x);
	ft_printf("%-#.5x|\n", x); 
	ft_printf("%-#6x|\n", x);
 	ft_printf("%#9.9x|\n", x);
	ft_printf("%7.12x|\n", x);
	ft_printf("%#7.12x|\n", x);
	ft_printf("%#6.9x|\n", x);
	ft_printf("%0#9x|\n", x);
	ft_printf("%0-7.5x|\n", x);
	ft_printf("%-0.5x|\n", x);
	ft_printf("%0#15x|\n", x);
	ft_printf("%0#3x|\n", x);
 	ft_printf("%0#6x|\n", x); 
 	ft_printf("%0#9.9x|\n", x);
	ft_printf("%07.12x|\n", x);
	ft_printf("%0#7.12x|\n", x);
	ft_printf("%-0#6.9x|\n", x);
 	ft_printf("%0#4.9x|\n", x);
	ft_printf("%0-7.5x|\n", x);
	ft_printf("%-0.5x|\n", x);
	ft_printf("%0#15.5x|\n", x);
	ft_printf("%09.5x|\n", x);
	ft_printf("%07.12x|\n", x);
	ft_printf("%0#7.12x|\n", x);
 	ft_printf("%-0#6.9x|\n", x);
 	ft_printf("%0#4.9x|\n", x);
	ft_printf("%0#9.4x|\n", x);
	ft_printf("% #9.4x|\n", x);
	ft_printf("% 9.4x|\n", x);
	ft_printf("%9.4x|\n", x);
	ft_printf("%9.7x|\n", x);
	ft_printf("%9.11x|\n", x);
 	ft_printf("%0#9.4x|\n", x);
	ft_printf("% #9.4x|\n", x);
	ft_printf("% 9.4x|\n", x);
	ft_printf("%9.4x|\n", x);
	ft_printf("%9.7x|\n", x);
	ft_printf("%9.11x|\n", x);
	printf("====================================================\n", x);
  	printf("%-#7X|\n", x);
	printf("%-07X|\n", x);
	printf("%-7X|\n", x);
 	printf("%7X|\n", x);
	printf("%+0x|\n", x);
	printf("%#9.5x|\n", x); 
	printf("%-#9x|\n", x);
	printf("%-7.5x|\n", x);
	printf("%-#.5x|\n", x);
	printf("%-#6x|\n", x);
	printf("%#9.9x|\n", x);
	printf("%7.12x|\n", x);
	printf("%#7.12x|\n", x);
	printf("%#6.9x|\n", x);
	printf("%0#9x|\n", x);
	printf("%0-7.5x|\n", x);
	printf("%-0.5x|\n", x);
	printf("%0#15x|\n", x);
	printf("%0#3x|\n", x);
	printf("%0#6x|\n", x);
 	printf("%0#9.9x|\n", x);
	printf("%07.12x|\n", x);
	printf("%0#7.12x|\n", x);
	printf("%-0#6.9x|\n", x);
 	printf("%0#4.9x|\n", x);
	 printf("%0-7.5x|\n", x);
	 printf("%-0.5x|\n", x);
	 printf("%0#15.5x|\n", x);
	 printf("%09.5x|\n", x);
	 printf("%07.12x|\n", x);
	 printf("%0#7.12x|\n", x);
 	printf("%-0#6.9x|\n", x);
 	printf("%0#4.9x|\n", x);
	printf("%0#9.4x|\n", x);
	printf("% #9.4x|\n", x);
	printf("% 9.4x|\n", x);
	printf("%9.4x|\n", x);
	printf("%9.7x|\n", x);
	printf("%9.11x|\n", x);
 	printf("%0#9.4x|\n", x);
	printf("% #9.4x|\n", x);
	printf("% 9.4x|\n", x);
	printf("%9.4x|\n", x);
	printf("%9.7x|\n", x);
	printf("%9.11x|\n", x); */

	
//	printf("%9.4x|\n", x);
//	printf("%9.7x|\n", x);
//	printf("%9.11x|\n", x);

//	sum = ft_printf("%-200.16s|\n", arr);
//	printf("sum = %i|\n", sum);
//	sum = printf("%-200.16s|\n", arr);
//	printf("sum = %i|\n", sum);
//	printf("%-4cf\n", number); 
	return (0);
}
