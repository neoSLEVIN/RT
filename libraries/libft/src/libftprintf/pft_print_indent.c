/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_indent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:01:01 by cschoen           #+#    #+#             */
/*   Updated: 2019/11/30 20:28:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pft_print_indent(t_print *print, char c, int cnt)
{
	if (cnt <= 0)
		return ;
	print->len += cnt;
	while (cnt--)
		write(print->fd, &c, 1);
}
