/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:16:53 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/04 18:16:51 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		minus_i(t_str *ln, char base)
{
	if (ln->fl == (ln->fl | PLUS) && !ln->num_u)
		ptr_mv(ln, '+');
	if (ln->num_u)
		ptr_mv(ln, '-');
	loop_p(ln, &base);
	!ln->num_u ? base_num(ln, ln->num) : base_num_u(ln, ln->num_u);
	loop_w(ln, 1);
	return (EXIT_SUCCESS);
}

int		minus_u(t_str *ln, char u_base)
{
	if ((ln->fl == (ln->fl | SHARP) && ln->num_u)
		|| ln->ty == 'p' || ln->ty == 'b')
		sharp(ln);
	loop_p(ln, &u_base);
	base_num_u(ln, ln->num_u);
	loop_w(ln, 1);
	return (EXIT_SUCCESS);
}
