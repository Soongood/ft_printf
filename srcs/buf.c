/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:41 by trobbin           #+#    #+#             */
/*   Updated: 2020/02/27 15:05:21 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_buf(t_str *ln)
{
	write(STDOUT_FILENO, ln->str, BUF_LIMIT);
	ft_bzero(ln->str, BUF_SIZE);
	ln->ptr = ln->str;
}

void	ptr_mv(t_str *ln, char letter)
{
	if (ln->length == BUF_LIMIT)
		print_buf(ln);
	*ln->ptr++ = letter;
	ln->length++;
}
