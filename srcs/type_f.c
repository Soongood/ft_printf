/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:18:08 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/05 03:17:12 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_abs(t_str *ln)
{
	ln->num_u = ~ln->num + 1;
}

static void		round_i(t_str *ln)
{
	char					length;

	length = 0;
	ln->ptr -= ln->width <= ln->tmp && ln->width && ln->fl != (ln->fl | SPACE) ? ln->tmp - ln->width + 2 : 1;
	while (*ln->ptr == ' ' && ln->fl == (ln->fl | MINUS))
	{
		ln->ptr--;
		length++;
	}
	while (*ln->ptr == '9' && ++length)
		*ln->ptr-- += 1;
	if (ft_isdigit(*ln->ptr))
		*ln->ptr += 1;
	if (ln->num == 9)
	{
		ln->ptr += ln->width >= 3 && ln->fl != (ln->fl | MINUS) ? 0 : 1;
		ln->width = 0;
		ln->num_u = 10;
		ln->base = 10;
		u_type(ln, ++ln->tmp);
	}
	else
		while (length-- >= 0)
			ptr_mv(ln, *ln->ptr > '9' && (ft_isdigit(*ln->ptr)
				|| *ln->ptr == ':') ? *ln->ptr - 10 : *ln->ptr);
}

static int		fract(t_str *ln, short *nums, int *i)
{
	*(nums + *i) = ln->num_d;
	if (!*i)
	{
		ln->num_d -= nums[0];
		ln->num_d *= 10;
		*(nums + ++(*i)) = ln->num_d;
	}
	while (*(nums + (*i - 1)) >= 9)
		if (*(nums + *i) >= 5)
		{
			*(nums + (*i - 1)) += 1;
			(*i)--;
		}
		else
			break ;
	if (*i)
		nums[*i - 1] += nums[*i] >= 5 ? 1 : 0;
	if (!ln->pre && nums[0] > 5)
	{
		round_i(ln);
		return (0);
	}
	return (1);
}

void			round_f(t_str *ln)
{
	int		i;
	short	nums[250];

	i = 0;
	ft_bzero(nums, sizeof(nums));
	if (ln->pre)
		ptr_mv(ln, '.');
	ln->num_d -= ln->num;
	ln->num_d *= ln->num_u ? -1 : 1;
	while ((ln->num_d *= 10) && ln->prec_f--)
	{
		nums[i++] = ln->num_d;
		ln->num_d -= nums[i - 1];
	}
	if (!fract(ln, nums, &i))
			return ;
	while (ln->prec_f-- > 0)
		nums[i++] = 0;
	nums[ln->pre] = -1;
	i = 0;
	while (nums[i] >= 0)
		ptr_mv(ln, '0' + (nums[i++] % 10));
	if (!ln->base)
		while (ln->width-- > ln->pre + ln->tmp + 1)
			ptr_mv(ln, ' ');
}

int				f_type(t_str *ln)
{
	int						width;

	ln->num = (intmax_t)ln->num_d;
	if (ln->num < 0)
		ft_abs(ln);
	ln->prec_f = ln->pre == -1 ? 6 : ln->pre;
	width = ln->width;
	if (ln->fl == (ln->fl | MINUS))
		ln->width = 1;
	else if (ln->pre)
		ln->width -= ln->pre == -1 ? 7 : ln->pre + 1;
	ln->pre = !ln->prec_f ? 0 : -1;
	i_type(ln, base(ln));
	ln->pre = ln->prec_f;
	if ((ln->fl == (ln->fl | MINUS)) && (ln->fl != (ln->fl | SPACE)))
	{
		ln->ptr -= width ? width - (ln->tmp + ln->prec_f + 1) : 0;
		ln->base = 0;
	}
	ln->width = width;
	round_f(ln);
	return (EXIT_SUCCESS);
}
