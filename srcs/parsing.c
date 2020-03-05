/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:18:04 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/05 00:14:23 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	void	parser_one(const char **chunk, t_str *ln, va_list list)
{
	is_flags(ln, chunk);
	ln->width = (**chunk == '*' && (*chunk)++) ?
		va_arg(list, int) : get_res(chunk);
	if (**chunk == '.' && (*chunk)++)
		ln->pre = (**chunk == '*' && (*chunk)++) ?
			va_arg(list, int) : get_res(chunk);
	if (ln->width < 0)
	{
		ln->width = ~ln->width + 1;
		ln->fl |= MINUS;
	}
	if (ln->pre < -1)
		ln->pre = -1;
}

static	int		parser_sec(t_str *ln, const char **chunk)
{
	if (is_type(**chunk))
		ln->ty = *(*chunk)++;
	else if (*(*chunk + 1))
	{
		if (is_specifier(**chunk) &&
				(**chunk == *(*chunk + 1)) && is_type(*(*chunk + 2)))
			ln->specifier[1] = *(*chunk)++;
		else if ((is_specifier(**chunk) ||
			(**chunk) == 'L') && is_type(*(*chunk + 1)))
			;
		else
			return (EXIT_FAILURE);
		ln->specifier[0] = *(*chunk)++;
		ln->ty = *(*chunk)++;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void			parser(const char **chunk, t_str *ln, va_list list)
{
	while (**chunk)
		if (**chunk != '%' || (*(*chunk)++ == '%' && **chunk == '%'))
		{
			if (ln->ptr == ln->str_end)
				print_buf(ln);
			*ln->ptr++ = *(*chunk)++;
		}
		else
		{
			parser_one(chunk, ln, list);
			if (!(parser_sec(ln, chunk)))
				handler(ln, list);
			else
			{
				ln->prec_f = 1;
				c_type(ln, **chunk == '%' ? '%' : NOTHING);
			}
			ln->length += ln->ptr - ln->str;
			write(STDOUT_FILENO, ln->str, ln->ptr - ln->str);
			init_str(ln);
		}
}
