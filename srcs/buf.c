#include "../includes/ft_printf.h"

void    print_buf(t_str *line)
{
    write(STDOUT_FILENO, line->str, BUF_LIMIT);
	ft_bzero(line->str, BUF_SIZE);
	line->ptr = line->str;
}

void	ptr_mv(t_str *line, char letter)
{
	if (line->length == BUF_LIMIT)
        print_buf(line);
	*line->ptr++ = letter;
	line->length++;
}