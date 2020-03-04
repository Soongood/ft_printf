/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:55 by trobbin           #+#    #+#             */
/*   Updated: 2020/02/27 16:15:45 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_specifier(char chunk)
{
	return (chunk == 'l' || chunk == 'h');
}

int		is_type(char chunk)
{
	return (chunk == 'p' || chunk == 'c' || chunk == 's' ||
			chunk == 'd' || chunk == 'i' || chunk == 'o' ||
			chunk == 'u' || chunk == 'x' || chunk == 'X' ||
			chunk == 'f' || chunk == 'b');
}

void	is_flags(t_str *ln, const char **chunk)
{
	while (**chunk == ' ' || **chunk == '#' ||
			**chunk == '+' || **chunk == '-' || **chunk == '0')
	{
		if (**chunk == '-')
			ln->fl |= MINUS;
		else if (**chunk == '+')
			ln->fl |= PLUS;
		else if (**chunk == ' ')
			ln->fl |= SPACE;
		else if (**chunk == '0')
			ln->fl |= ZERO;
		else if (**chunk == '#')
			ln->fl |= SHARP;
		(*chunk)++;
	}
}
