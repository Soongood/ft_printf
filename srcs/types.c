/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:18:10 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/05 19:07:15 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		c_type(t_str *ln, int letter)
{
	if (ln->ty == 'b')
		return (binary(ln, &letter));
	if (ln->width)
		if ((ln->fl == (ln->fl | MINUS)) && (ln->letter = 'A'))
			ptr_mv(ln, letter);
	while (--ln->width > 0)
		ptr_mv(ln, ln->fl == (ln->fl | ZERO) && ln->fl != (ln->fl | MINUS)
			? '0' : ' ');
	if (ln->letter == 'a')
	{
		if (letter)
			ptr_mv(ln, letter);
		else if (!ln->prec_f)
			ptr_mv(ln, '\0');
	}
	return (EXIT_SUCCESS);
}

int		s_type(t_str *ln, char *string)
{
	if (!string)
	{
		if (ln->pre == -1)
			ln->pre = 6;
		s_type(ln, "(null)");
		return (EXIT_SUCCESS);
	}
	ln->num = (intmax_t)ft_strlen(string);
	ln->prec_f = ln->pre;
	if (ln->width)
	{
		if ((ln->fl == (ln->fl | MINUS)) && (ln->letter = 'A') && ln->pre)
			while (*string && ln->prec_f--)
				ptr_mv(ln, *string++);
		while ((ln->pre >= 0 && ln->pre < ln->num)
				? ln->width-- > ln->pre : ln->width-- > ln->num)
			ptr_mv(ln, ln->fl == (ln->fl | ZERO) && ln->fl != (ln->fl | MINUS)
				? '0' : ' ');
		if (ln->letter == 'A')
			return (EXIT_SUCCESS);
	}
	while (*string && ln->prec_f--)
		ptr_mv(ln, *string++);
	return (EXIT_SUCCESS);
}

int		p_type(t_str *ln, uintmax_t pointer)
{
	if (ln->ty == 'p')
	{
		ln->num_u = pointer;
		ln->fl |= SHARP;
	}
	ln->base = ln->ty == 'p' ? 16 : 2;
	if (!ln->pre || (ln->fl == (ln->fl | SPACE) && ln->pre == -1))
	{
		if (ln->fl == (ln->fl | SPACE) && ln->pre == -1)
			ln->letter = 'A';
		else if (!ln->pre && !ln->num_u)
			ln->width++;
		ln->pre = 1;
	}
	u_type(ln, u_base(ln));
	return (EXIT_SUCCESS);
}

int		u_type(t_str *ln, char u_base)
{
	ln->tmp = u_base > ln->pre ? u_base : ln->pre;
	ln->tmp += ln->ty == 'o' && ln->fl == (ln->fl | SHARP) && ln->tmp != ln->pre  && ln-> num_u ? 1 : NOTHING;
	ln->tmp += (((ln->ty == 'x' || ln->ty == 'X') && ln->num_u &&
		(ln->fl == (ln->fl | SHARP))) || ln->ty == 'p'
			|| ln->ty == 'b') ? 2 : 0;
	ln->width += !ln->num_u && !ln->pre ? 1 : NOTHING;
	if (ln->fl == (ln->fl | MINUS))
		return (minus_u(ln, u_base));
	if ((ln->pre > 0 || !ln->fl || (ln->fl == (ln->fl | PLUS))) ||
		(ln->width > 0 && ln->fl != (ln->fl | ZERO)))
	{
		loop_w(ln, 1);
		if ((ln->fl == (ln->fl | SHARP) && ln->num_u)
			|| ln->ty == 'p' || ln->ty == 'b')
			sharp(ln);
		loop_p(ln, &u_base);
	}
	else
	{
		if ((ln->fl == (ln->fl | SHARP) && ln->num_u) || ln->ty == 'p' ||
			ln->ty == 'b' || (ln->ty == 'o' && !ln->num_u && !ln->pre))
			sharp(ln);
		loop_w(ln, 0);
	}
	base_num_u(ln, ln->num_u);
	return (EXIT_SUCCESS);
}

int		i_type(t_str *ln, char base)
{
	ln->tmp = base > ln->pre ? base : ln->pre;
	ln->tmp += (ln->fl == (ln->fl | PLUS) || ln->num_u) ? 1 : 0;
	ln->width += !ln->num && !ln->pre && ln->ty != 'f' && ln->fl != (ln->fl | MINUS) ? 1 : NOTHING;
	if ((ln->fl == (ln->fl | SPACE)) && (ln->fl != (ln->fl | PLUS))
		&& (ln->fl != (ln->fl | SHARP)) && !ln->num_u)
	{
		ptr_mv(ln, ' ');
		ln->width--;
	}
	if (ln->fl == (ln->fl | MINUS))
		return (minus_i(ln, base));
	if (ln->pre == -1 && (ln->fl == (ln->fl | ZERO)) &&
		(ln->fl == (ln->fl | PLUS)) && !ln->num_u && (ln->letter = 'A'))
		ptr_mv(ln, '+');
	loop_w(ln, (ln->pre == -1 && (ln->fl == (ln->fl | ZERO))) ? 0 : 1);
	if (ln->num_u && ln->ty != 'f' && ln->pre != -1)
		ptr_mv(ln, '-');
	if (ln->fl == (ln->fl | PLUS) && !ln->num_u && (ln->letter == 'a'))
		ptr_mv(ln, '+');
	if (ln->pre || (ln->fl == (ln->fl | ZERO)))
		loop_p(ln, &base);
	if (!(intmax_t)ln->num_d && ln->num < 0)
		ln->num = 0;
	!ln->num_u ? base_num(ln, ln->num) : base_num_u(ln, ln->num_u);
	return (EXIT_SUCCESS);
}
