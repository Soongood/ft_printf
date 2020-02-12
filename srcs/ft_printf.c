#include "../includes/ft_printf.h"
#include <stdio.h>

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
