/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:38:54 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/24 20:46:01 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t		i;
	size_t		size;

	i = 0;
	if (!s)
		return (NULL);
	while (ft_isblank(s[i]) || s[i] == '\n')
		i++;
	if (!s[i])
		return (ft_strnew(0));
	size = ft_strlen(s);
	while (ft_isblank(s[size - 1]) || s[size - 1] == '\n')
		size--;
	return (ft_strsub(s, i, size - i));
}
