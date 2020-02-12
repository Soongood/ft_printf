/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:24:16 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/24 21:27:18 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstaddback(t_list *head, t_list *elem)
{
	t_list *ptr;

	if (!elem)
		return (NULL);
	if (head)
	{
		ptr = head;
		while (head->next)
			head = head->next;
		head->next = elem;
		return (ptr);
	}
	return (elem);
}
