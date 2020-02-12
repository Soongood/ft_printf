/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:42:26 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/21 16:22:23 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t tmp;

	tmp = 0;
	while (*dst && tmp < size)
	{
		tmp += 1;
		dst++;
	}
	while (*src && ((tmp + 1) < size))
	{
		*dst++ = *src++;
		tmp++;
	}
	if (tmp < size)
		*dst = '\0';
	return (tmp + ft_strlen(src));
}
