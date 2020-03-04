/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:06:46 by trobbin           #+#    #+#             */
/*   Updated: 2020/02/27 16:13:10 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		binary(t_str *ln, int *letter)
{
	if (letter < 0)
	{
		ln->num_u = ~*letter + 1;
		ln->fl &= 253;
		ln->num = 1;
	}
	else
		ln->num_u = *letter;
	p_type(ln, ln->num_u);
	return (EXIT_SUCCESS);
}
