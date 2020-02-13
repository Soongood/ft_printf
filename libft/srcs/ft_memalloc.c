/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:16:11 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/24 18:27:34 by trobbin          ###   ########.fr       */
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
