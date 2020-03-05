/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobbin <trobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:17:41 by trobbin           #+#    #+#             */
/*   Updated: 2020/03/04 23:36:00 by trobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_buf(t_str *ln)
{
	write(STDOUT_FILENO, ln->str, BUF_SIZE);
	ft_bzero(ln->str, BUF_SIZE);
	ln->ptr = ln->str;
	ln->length += BUF_SIZE;
}

void	ptr_mv(t_str *ln, char letter)
{
	if (ln->ptr == ln->str_end)
		print_buf(ln);
	*ln->ptr++ = letter;
}
