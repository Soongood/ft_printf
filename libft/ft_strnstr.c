/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:54:06 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/24 16:39:15 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	bg;
	size_t	sm;

	if (!*needle)
		return ((char *)hay);
	bg = ft_strlen(hay);
	sm = ft_strlen(needle);
	while (*hay && len)
	{
		if (*hay != *needle)
			hay++;
		else if (bg-- >= sm && len >= sm)
		{
			if (!ft_memcmp(hay, needle, sm))
				return ((char *)hay);
			else
				hay++;
		}
		len--;
	}
	return (NULL);
}
