/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:52 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/04 18:20:05 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	handler(t_str *ln, va_list list)
{
	if (ln->ty == 's')
		return (s_type(ln, va_arg(list, char *)));
	if (ln->ty == 'c' || ln->ty == 'b')
		return (c_type(ln, va_arg(list, int)));
	if (ln->ty == 'p')
		return (p_type(ln, (uintmax_t)va_arg(list, void *)));
	if ((ln->ty == 'x' || ln->ty == 'X' || ln->ty == 'o' || ln->ty == 'u'))
	{
		get_num_u(ln, list);
		if (ln->ty == 'o' && (ln->base = 8))
			ln->pre -= !ln->pre && !ln->num_u && ln->fl == (ln->fl | SHARP) ? 1 : NOTHING;
		else if ((ln->ty == 'x' || ln->ty == 'X') && (ln->base = 16))
			ln->letter = ln->ty == 'X' ? 'A' : 'a';
		return (u_type(ln, u_base(ln)));
	}
	get_num(ln, list);
	if (ln->ty == 'd' || ln->ty == 'i')
	{
		if (ln->num < 0)
			ft_abs(ln);
		return (i_type(ln, base(ln)));
	}
	if (ln->ty == 'f')
		return (f_type(ln));
	return (EXIT_SUCCESS);
}
