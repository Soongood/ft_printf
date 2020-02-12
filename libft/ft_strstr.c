/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 23:03:25 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/18 00:23:38 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack != *needle)
			haystack++;
		else
		{
			if (!ft_strncmp(haystack, needle, ft_strlen(needle)))
				return ((char *)haystack);
			else
				haystack++;
		}
	}
	return (NULL);
}
