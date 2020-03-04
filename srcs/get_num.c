/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:48 by trobbin           #+#    #+#             */
/*   Updated: 2020/02/27 18:23:17 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			get_res(const char **chunk)
{
	char	i;
	char	tmp[5];
	long	result;

	i = 0;
	result = 0;
	ft_bzero(&tmp, sizeof(tmp));
	while (ft_isdigit(**chunk))
	{
		*(tmp + i) = *(*chunk)++;
		result = 10 * result + (*(tmp + i++) - '0');
	}
	return (result);
}

void		get_num(t_str *ln, va_list list)
{
	if (ln->ty != 'f')
	{
		if (ln->specifier[0] == 'l')
			ln->num = (ln->specifier[1] == 'l') ?
				(intmax_t)va_arg(list, long long int) :
					(intmax_t)va_arg(list, long int);
		else if (ln->specifier[0] == 'h')
			ln->num = ln->specifier[1] == 'h' ?
				(intmax_t)((char)va_arg(list, int)) :
					(intmax_t)((short)va_arg(list, int));
		else
			ln->num = (intmax_t)va_arg(list, int);
	}
	else if (ln->specifier[0] == 'L')
		ln->num_d = va_arg(list, long double);
	else
		ln->num_d = va_arg(list, double);
}

void		get_num_u(t_str *ln, va_list list)
{
	if ((ln->specifier[0] == 'l') || (ln->specifier[0] == 'L'))
		ln->num_u = ((ln->specifier[1] == 'l') || (ln->specifier[0] == 'L')) ?
			(uintmax_t)va_arg(list, unsigned long long int) :
				(uintmax_t)va_arg(list, unsigned long int);
	else if (ln->specifier[0] == 'h')
		ln->num_u = ln->specifier[1] == 'h' ?
			(uintmax_t)((unsigned char)va_arg(list, unsigned int)) :
				(uintmax_t)((unsigned short)va_arg(list, unsigned int));
	else
		ln->num_u = (uintmax_t)va_arg(list, unsigned int);
}
