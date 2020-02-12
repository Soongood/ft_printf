/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:03:45 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/24 18:58:06 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*p;

	i = 0;
	if (!s || ft_strlen(s) < start)
		return (NULL);
	p = ft_strnew(len);
	if (!p)
		return (NULL);
	while (len--)
	{
		p[i] = s[start];
		start++;
		i++;
	}
	return (p);
}
