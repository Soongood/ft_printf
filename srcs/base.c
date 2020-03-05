/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:35 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/04 23:24:24 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	u_base(t_str *ln)
{
	uintmax_t tmp;

	ln->tmp = 1;
	tmp = ln->num_u;
	while (tmp /= ln->base)
		ln->tmp++;
	return (ln->tmp);
}

char	base(t_str *ln)
{
	intmax_t tmp;

	ln->tmp = 1;
	tmp = ln->num;
	while (tmp /= ln->base)
		ln->tmp++;
	return (ln->tmp);
}

int		base_num_u(t_str *ln, uintmax_t number)
{
	char		num;

	if (number >= (uintmax_t)ln->base)
		base_num_u(ln, number / ln->base);
	num = number % ln->base;
	if (ln->ty == 'p' && ln->pre == 1 && !ln->num_u && ln->letter != 'A')
		return (EXIT_SUCCESS);
	if (ln->pre || (!ln->pre && (ln->num || ln->num_u)))
		ptr_mv(ln, (num >= 10) ? ln->letter + num - 10 : '0' + num);
	return (EXIT_SUCCESS);
}

int		base_num(t_str *ln, intmax_t number)
{
	if (number >= ln->base)
		base_num(ln, number / ln->base);
	if ((ln->pre || (!ln->pre && (ln->num))) || ln->ty == 'f')
		ptr_mv(ln, '0' + number % ln->base);
	else
		ln->width++;
	return (EXIT_SUCCESS);
}
