/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:44 by trobbin           #+#    #+#             */
/*   Updated: 2020/02/27 15:51:57 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_str	ln;
	va_list	ap;
	int		ln_len;

	ln.length = 0;
	ln_len = 0;
	init_str(&ln);
	va_start(ap, format);
	parser(&format, &ln, ap, &ln_len);
	ln_len += ln.length;
	va_end(ap);
	write(STDOUT_FILENO, ln.str, ln.length <= BUF_LIMIT ?
		ln.length : (int)ft_strlen(ln.str));
	return (ln_len);
}
