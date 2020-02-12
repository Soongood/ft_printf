/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 00:22:42 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/20 00:22:44 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		index;
	long	temp;

	index = 1;
	temp = n;
	if (temp < 0)
	{
		ft_putchar_fd('-', fd);
		temp *= -1;
	}
	while (n /= 10)
		index *= 10;
	while (index)
	{
		if (index == 1)
		{
			ft_putchar_fd('0' + temp, fd);
			break ;
		}
		ft_putchar_fd('0' + temp / index, fd);
		temp %= index;
		index /= 10;
	}
}
