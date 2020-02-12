/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:17:39 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/22 21:07:54 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_length(int n)
{
	int i;

	i = 1;
	if (n < 0)
		i++;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	int		len;
	char	*p;
	long	temp;

	temp = n;
	len = ft_length(n) - 1;
	p = ft_strnew(len + 1);
	if (!p)
		return (NULL);
	if (n < 0)
	{
		p[0] = '-';
		temp *= -1;
	}
	while (len >= 0)
	{
		if (temp <= 9)
		{
			p[len--] = '0' + temp;
			break ;
		}
		p[len--] = '0' + temp % 10;
		temp /= 10;
	}
	return (p);
}
