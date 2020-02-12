/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:53:58 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/21 18:18:48 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *pdst;
	unsigned char *psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	if (dst < src)
		return (ft_memcpy(pdst, psrc, len));
	pdst += len;
	psrc += len;
	while (len--)
		*--pdst = *--psrc;
	return (dst);
}
