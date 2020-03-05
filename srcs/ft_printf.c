/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:44 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/04 23:38:33 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_str	ln;
	va_list	ap;

	if (!format)
		return(EXIT_FAILURE);
	ln.length = 0;
	init_str(&ln);
	va_start(ap, format);
	parser(&format, &ln, ap);
	va_end(ap);
	ln.length += ln.ptr - ln.str;
	write(STDOUT_FILENO, ln.str, ln.ptr - ln.str);
	return (ln.length);
}
