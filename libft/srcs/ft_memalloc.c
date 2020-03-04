/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:16:11 by trobbin           #+#    #+#             */
/*   Updated: 2020/02/27 14:03:54 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void *p;

	p = (void *)malloc(sizeof(*p) * size);
	if (p)
		ft_bzero(p, size);
	return (p);
}
