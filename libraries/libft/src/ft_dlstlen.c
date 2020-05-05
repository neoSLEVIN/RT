/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 01:53:54 by cschoen           #+#    #+#             */
/*   Updated: 2019/12/10 02:01:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_dlstlen(t_dlist *lst)
{
	t_dlist	*tmp;
	size_t	len;

	tmp = lst;
	len = 1;
	if (!tmp)
		return (0);
	while ((tmp = tmp->next))
		++len;
	return (len);
}
