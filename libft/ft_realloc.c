/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:08:17 by trobbin           #+#    #+#             */
/*   Updated: 2019/11/19 06:05:43 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void		*temp_buf;
	size_t		length;

	if (!ptr)
		return ((ptr = ft_strnew(size)));
	if (!size && ptr)
		ft_memdel(&ptr);
	if ((temp_buf = ft_strnew(size)))
	{
		length = (ft_strlen((const char *)ptr));
		ft_memcpy(temp_buf, ptr, length > size ? size : length);
		ft_memdel(&ptr);
	}
	return (temp_buf);
}
