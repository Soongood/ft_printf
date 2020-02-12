/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 22:48:40 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/20 00:15:30 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int		index;
	long	temp;

	index = 1;
	temp = n;
	if (temp < 0)
	{
		ft_putchar('-');
		temp *= -1;
	}
	while (n /= 10)
		index *= 10;
	while (index)
	{
		if (index == 1)
		{
			ft_putchar('0' + temp);
			break ;
		}
		ft_putchar('0' + temp / index);
		temp %= index;
		index /= 10;
	}
}
