/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:25:16 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/24 22:16:42 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_strcopy(char **p, char const *s, char c, int qt)
{
	int	tmp;
	int	length;

	length = 0;
	tmp = -1;
	while (*s)
		if (*s++ != c)
		{
			while (*(s - 1) != c && *(s - 1))
			{
				length++;
				s++;
			}
			if (qt >= ++tmp)
			{
				if (!(p[tmp] = ft_strnew(length)))
				{
					ft_memdelarr((void **)p);
					return ;
				}
				ft_strncpy(p[tmp], s - 1 - length, length);
				length = 0;
			}
		}
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		qt;
	char	**p;

	i = 0;
	qt = -1;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			qt++;
		}
		else
			i++;
	}
	p = (char **)malloc(sizeof(char*) * (qt + 2));
	if (!p)
		return (NULL);
	ft_strcopy(p, s, c, qt);
	p[qt + 1] = NULL;
	return (p);
}
