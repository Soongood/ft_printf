/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 22:26:53 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/17 23:04:40 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *p;

	p = dst;
	while (len--)
	{
		if (*src)
			*dst++ = *src++;
		else
			*dst++ = '\0';
	}
	return (p);
}
