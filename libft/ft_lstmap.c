/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 12:46:31 by trobbin           #+#    #+#             */
/*   Updated: 2019/09/24 21:27:24 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_del(void *content, size_t cont_size)
{
	ft_memset(content, 0, cont_size);
	free(content);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*head;

	if (!lst || !f)
		return (NULL);
	if (!(head = f(lst)))
		return (NULL);
	while ((lst = lst->next))
	{
		if ((tmp = f(lst)))
			ft_lstaddback(head, tmp);
		else
		{
			ft_lstdel(&head, ft_del);
			return (NULL);
		}
	}
	return (head);
}
