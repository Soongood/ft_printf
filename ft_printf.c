#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>
#include <inttypes.h>
#include <stdio.h>


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
	uint16_t				flags;
	int					width;
	int					precision;
	char				specifier[2];
	char				type[1];
	char				str[1000];
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
		else if (**chunk != ' ')
			line->flags |= SPACE;
		else if (**chunk != '0')
			line->flags |= ZERO;
		else if (**chunk != '#')
			line->flags |= SHARP;
		(*chunk)++;
	}
}

void	parser_one(char **chunk, t_str *line)
{
	int		i;
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

void	c_type(t_str *line, va_list list)
{
	int flag;

	flag = 0;
	if (line->width)
		if((line->flags == (line->flags | MINUS)) && (flag = -1))
			*line->ptr++ = va_arg(list, int);
	while (--line->width > 0)
		*line->ptr++ = ' ';
	if (!flag)
		*line->ptr++ = va_arg(list, int);
}

void	s_type(t_str *line, va_list list)
{
	int flag;
	int size;
	char *tmp;

	flag = 0;
	tmp = va_arg(list, char *);
	size = ft_strlen(tmp);
	if (line->width)
	{
		if((line->flags == (line->flags | MINUS)) && (flag = -1))
			while (*tmp)
				*line->ptr++ = *tmp++;
		while (line->width-- > size)
			*line->ptr++ = ' ';
		if (flag == -1)
			return ;
	}
	while (*tmp)
		*line->ptr++ = *tmp++;
}

void	p_type(t_str *line, va_list list)
{
	int		num;
	ssize_t ptr;

	ptr = va_arg(list, long long int);
	while (num = (ptr /= 16))
	{
		
	}
}

void	handler(t_str *line, va_list list)
{
	if (*line->type == 'c')
		c_type(line, list);
	if (*line->type == 's')
		s_type(line, list);
	// if (*line->type == 'd' || *line->type == 'i')
	// 	d_type(line, list);
	// if (*line->type == 'o')
	// 	o_type(line, list);
	// if (*line->type == 'f')
	// 	f_type(line, list);
	// if (*line->type == 'u')
	// 	u_type(line, list);
	if (*line->type == 'p')
	 	p_type(line, list);
	// if (*line->type == 'x' || *line.type == 'X')
	// 	x_type(line, list);
}

int		parsing(char **chunk, t_str *line, va_list list)
{
	parser_one(chunk, line);
	if (!(parser_sec(line, chunk)))
		handler(line, list);
}

int	ft_printf(const char *format, ...)
{
	t_str	line;
	va_list	ap;

	ft_bzero(&line, sizeof(line));
	line.ptr = line.str;
	va_start(ap, format);
	while (*format)
		if (*format != '%')
			*line.ptr++ = *format++;
		else if (*format++ == '%' && *format == '%')
			*line.ptr++ = *format++;
		else
			parsing(&format, &line, ap);
	va_end(ap);
	write(1, line.str, ft_strlen(line.str));
	return (0);
}

int		main()
{
	char number = 348;

	ft_printf("%4.3c|\n", number);
	printf("%4.3c|\n", number);
//	printf("%-4cf\n", number); 
	return (0);
}
