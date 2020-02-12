/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:25:07 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/19 18:53:14 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			p[i] = f(s[i]);
			i++;
		}
	return (p);
}
