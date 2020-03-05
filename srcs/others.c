/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:18:01 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/05 01:30:15 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	init_str(t_str *ln)
{
	int tmp;
	static unsigned int size = sizeof(*ln) - BUF_SIZE;

	if (!ln->length)
		ft_bzero(ln, sizeof(*ln));
	else
	{
		tmp = ln->length;
		ft_bzero(ln, size + ln->ptr - ln->str);
		ln->length = tmp;
	}
	ln->str_end = ln->str + BUF_SIZE;
	ln->ptr = ln->str;
	ln->letter = 'a';
	ln->base = 10;
	ln->pre = -1;
}

void	sharp(t_str *ln)
{
	if (ln->ty == 'b' && ln->num)
		ptr_mv(ln, '-');
	ptr_mv(ln, '0');
	if (ln->ty == 'o' && ln->num_u)
		ln->pre--;
	if (ln->ty == 'b')
		ptr_mv(ln, 'b');
	else if (ln->ty == 'p' || ln->ty == 'x' || ln->ty == 'X')
		ptr_mv(ln, ln->ty == 'X' ? 'X' : 'x');
}

void	loop_w(t_str *ln, char num)
{
	if ((ln->pre == -1 || (ln->ty == 'f' && !ln->pre)) && !num && ln->num < 0)
		ptr_mv(ln, '-');
	while (ln->width-- > ln->tmp)
		ptr_mv(ln, !num ? '0' : ' ');
	if ((ln->pre == -1 || (ln->ty == 'f' && !ln->pre)) && num && ln->num < 0)
		ptr_mv(ln, '-');
}

void	loop_p(t_str *ln, char *u_base)
{
	int tmp;

	tmp = ln->pre;
	while (ln->pre-- > *u_base)
		ptr_mv(ln, '0');
	ln->pre = (ln->num || ln->num_u) ? 1 : tmp;
}
