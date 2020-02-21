#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		length;
	t_str	line;
	va_list	ap;

	length = 0;
	line.length = 0;
	init_str(&line);
	va_start(ap, format);
	while (*format)
		if (*format != '%' || (*format++ == '%' && *format == '%'))
		{
			*line.ptr++ = *format++;
			line.length++; // чек на переполнение, написать функцию + смещение указателя на начало
		}
		// else if (*format++ == '%' && *format == '%')
		// {
		// 	*line.ptr++ = *format++;
		// }
		else
		{
			parsing(&format, &line, ap);
			length += line.length;
			write(STDOUT_FILENO, line.str, line.length);
			init_str(&line);
		}
	va_end(ap);
	write(STDOUT_FILENO, line.str, line.length);
	return (length);
}
