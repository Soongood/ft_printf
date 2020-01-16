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
	char				flags[5];
	char				width[5];
	char				precision[5];
	char				size[3];
	char				type[2];
}						t_str;


void	parse_flags(char *chunk, char *flags, int *shift)
{
	while (*chunk == ' ' || *chunk == '#' || *chunk == '+' || *chunk == '-' || *chunk == '0')
	{
		*flags++ = *chunk++;
		*shift += 1;
	}
}

void	parse_width(char *chunk, char *width, int *shift)
{
	while (ft_isdigit(*chunk))
	{
		*width++ = *chunk++;
		*shift += 1;
	}
}

void	parse_precision(char *chunk, char *precision, int *shift)
{
	if (*chunk++ == '.')
	{
		while (ft_isdigit(*chunk))
		{
			*precision++ = chunk++;
			*shift += 1;
		}
		*shift += 1;
	}
}

int		is_type(char *chunk)
{
	return (*chunk == 'p' || *chunk == 'c' || *chunk == 's');
}

int		is_type_com(char *chunk)
{
	return (*chunk == 'd' || *chunk == 'i' || *chunk == 'o' || *chunk == 'u' || *chunk == 'x' || *chunk == 'X');
}

int		is_type_f(char *chunk)
{
	return (*chunk == 'f');
}

void	parse_s(t_str line, char *chunk, int *shift, va_list *list)
{
	int i;

	i = 0;
	if (is_type(chunk[i]) || is_type_com(chunk[i]) || is_type_f(chunk[i++]))
		handle();
	else 
	{
		while (chunk[i] && i < 3)
		{
			if (i == 1 && chunk[0] == 'l' && (is_type_f(chunk[i]) || is_type_com(chunk[i])))
			{
				handle();
				i++;
				break;
			}
			if (i == 1 && chunk[0] == 'L' && is_type_f(chunk[i]))
			{
				handle();
				i++;
				break;
			}
			else if (chunk[0] == chunk[1])
		}
	}
	*shift += i;
}

int		parse(char *chunk, t_str line, va_list *list)
{
	int shift;
	
	shift = 0;
	parse_flags(chunk, line.flags, &shift);
	parse_width(chunk + shift, line.width, &shift);
	parse_precision(chunk + shift, line.precision, &shift);
	parse_s(line, chunk + shift, &shift, list);
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
	va_start(ap, format);
	while (*format)
	{
		if (*format++ != '%')
			size++;
		else
		{
			write(1, tmp, size);
			size = 0;
			ft_bzero(&line, sizeof(line));
			format += parse(format, line, &ap);
			tmp = format;
		}
	}
	va_end(ap);
	write(1, tmp, size);
	return (0);
}

int		main()
{
	int number = 120;

	ft_printf("%c", number);
//	printf(" %zz%zz %i\n", number); 
	return (0);
}
