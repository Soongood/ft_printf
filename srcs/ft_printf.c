#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		length;
	t_str	line;
	va_list	ap;

	line.length = 0;
	init_str(&line);
	va_start(ap, format);
	while (*format)
		if (*format != '%' || (*format++ == '%' && *format == '%'))
		{
			if (line.length == BUF_LIMIT)
				print_buf(&line);
			*line.ptr++ = *format++;
			line.length++;
		}
		else
		{
			parsing(&format, &line, ap);
			write(STDOUT_FILENO, line.str, line.length <= BUF_LIMIT ? line.length : ft_strlen(line.str));
			init_str(&line);
		}
	va_end(ap);
	write(STDOUT_FILENO, line.str, line.length <= BUF_LIMIT ? line.length : ft_strlen(line.str));
	return (line.length);
}
