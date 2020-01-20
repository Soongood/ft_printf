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
	uint8_t				flags;
	int					width;
	int					precision;
	char				specifier[2];
	char				type[1];
}						t_str; // не забыть выровнять

int		is_flags(t_str *line, char *chunk)
{
	int i;

	i = 0;
	while (chunk[i] == ' ' || chunk[i] == '#' || chunk[i] == '+' || chunk[i] == '-' || chunk[i] == '0')
	{
		if (chunk[i] == '-')
			line->flags |= MINUS;
		if (chunk[i] == '+')
			line->flags |= PLUS;
		if (chunk[i] != ' ')
			line->flags |= SPACE;
		if (chunk[i] != '0')
			line->flags |= ZERO;
		if (chunk[i] != '#')
			line->flags |= SHARP;
		i++;
	}
	return (i);
}

void	parser_one(char *chunk, t_str *line, int *shift)
{
	int		i;
	int		j;
	char	tmp[5];

	i = 0;
	j = 0;
	ft_bzero(&tmp, sizeof(tmp));
	j = is_flags(line, chunk);
	i = 0;
	while (ft_isdigit(chunk[j]))
		tmp[i++] = chunk[j++];
	*tmp ? line->width = ft_atoi(tmp), ft_bzero(&tmp, i) : 0;
	i = 0;
	if (chunk[j] == '.')
		while (ft_isdigit(chunk[++j]))
			tmp[i++] = chunk[j];
	line->precision = ft_atoi(tmp);
	*shift += j;
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

int		parser_sec(t_str *line, char *chunk, int *shift)
{
	int i;

	i = 0;
	if (is_type(chunk[i++]))
		line->type[0] = chunk[0];
	else if (chunk[i++])
		{
			if (is_specifier(chunk[0]) && (chunk[0] == chunk[1]) && is_type(chunk[i]))
				line->specifier[1] = (chunk[1]);
			else if ((is_specifier(chunk[0]) || chunk[0] == 'L') && is_type(chunk[i - 1]))
				i--;
			else
				return (1);
			line->specifier[0] = chunk[0];
			line->type[0] = chunk[i++];
		}
		else
			return (1);
	*shift += i;
	return (0);
}

void	c_type(t_str line, va_list list)
{
	char	letter;

	letter = va_arg(list, int);
	if (line.width)
		if(line.flags == (line.flags | MINUS))
			write(1, &letter, 1);
	while (--line.width > 0)
		write(1, " ", 1);
	if(line.flags == (line.flags | MINUS))
		return ;
	write(1, &letter, 1);
}

void	handler(t_str line, va_list list)
{
	if (*line.type == 'c')
		c_type(line, list);
	// if (*line.type == 'd' || *line.type == 'i')
	// 	*shift = d_type(line, list);
	// if (*line.type == 's')
	// 	*shift = s_type(line, list);
	// if (*line.type == 'o')
	// 	*shift = o_type(line, list);
	// if (*line.type == 'f')
	// 	*shift = f_type(line, list);
	// if (*line.type == 'u')
	// 	*shift = u_type(line, list);
	// if (*line.type == 'p')
	// 	*shift = p_type(line, list);
	// if (*line.type == 'x' || *line.type == 'X')
	// 	*shift = x_type(line, list);
}

int		parsing(char *chunk, t_str line, va_list list)
{
	int shift;
	
	shift = 0;
	parser_one(chunk, &line, &shift);
	if (!(parser_sec(&line, chunk + shift, &shift)))
		handler(line, list);
	return (shift);
}

int	ft_printf(const char *format, ...)
{
	int		size;
	char	*tmp;
	t_str	line;
	va_list	ap;

	size = 0;
	tmp = format;
	ft_bzero(&line, sizeof(line));
	va_start(ap, format);
	while (*format)
		if (*format++ != '%')
			size++;
		else if (*format == '%' && tmp++ && format++)
				size++;
		else
		{
			write(1, tmp, size);
			size = 0;
			format += parsing(format, line, ap);
			tmp = format;
		}
	va_end(ap);
	write(1, tmp, size);
	return (0);
}

int		main()
{
	char number = 348;

	ft_printf("%-4cf\n", number);
	printf("%4cf\n", number);
	printf("%-4cf\n", number); 
	return (0);
}
