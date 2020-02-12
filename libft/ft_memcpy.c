/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 00:29:36 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/17 21:33:00 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *p;

	p = dst;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*(unsigned char*)dst++ = *(unsigned char*)src++;
	return (p);
}
