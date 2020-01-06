#include "ft_printf.h"
#include <stdarg.h>
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

/* typedef struct			s_struct
{
	struct	s_struct	*next;
	int					precision;
	int					f_width;
	char				*flags;
	char				*length;
	char				type;
	char				str_out;
}						t_struct;
*/

int		ft_parse_flags(char **chunk)
{
	int shift;

	shift = 0;
	while (**chunk == SPACE || **chunk == SHARP || **chunk == PLUS || **chunk == MINUS || **chunk == ZERO)
	{
		**chunk++;
		shift++;
	}
	return (shift);
}
int		ft_parse_width(char *chunk)
{
	int shift;

	shift = 0;
	while (ft_isdigit(*chunk))
	{
		chunk++;
		shift++;
	}
	return (shift);
}
int		ft_parse_precision(char *chunk)
{
	int shift;

	shift = 0;
	if (*chunk++ == '.')
	{
		while (ft_isdigit(*chunk))
		{
			chunk++;
			shift++;
		}
	}
	return (shift);
}

 int		ft_parse_type(char *chunk)
{
	return (1);
}

int		ft_parse_number(char **chunk)
{
	static int shift = 0;
	
	shift += ft_parse_flags(chunk);
	shift += ft_parse_width(chunk + shift);
	shift += ft_parse_precision(chunk + shift);
	shift += ft_parse_type(chunk + shift);
	return (shift);
}

void	ft_parse_line(const char *format)
{
	char **tmp;
	
	while (*format)
	{
		if (*format != '%')
			format++;
		else
		{
			format += 1;
			tmp = &format;
			format += ft_parse_number(tmp);
		}
	}
}

int		ft_printf(const char *format, ...)
{
	ft_parse_line(format);
}

int		main()
{
	int number = 1231425;
	ft_printf("sdkfjf %+-123.3i");
	//printf(" %45 \n", number); 
return (0);
}
