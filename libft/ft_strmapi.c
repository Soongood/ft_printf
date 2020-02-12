/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:54:31 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/19 19:00:40 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*p;

	i = 0;
	if (!s || !f)
		return (NULL);
	p = ft_strnew((size_t)ft_strlen(s));
	if (!p)
		return (NULL);
	else
		while (s[i])
		{
			p[i] = f(i, s[i]);
			i++;
		}
	return (p);
}
