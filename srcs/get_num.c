#include "../includes/ft_printf.h"

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
		else
			line->num = (intmax_t)va_arg(list, int);
	}
	else if (line->specifier[0] == 'L')
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
