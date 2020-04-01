/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 02:02:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/01/12 23:02:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dlist **adlst, void (*del)(void *, size_t),
					void (*del_data)(void *))
{
	t_dlist	*tmp;

	if (del)
	{
		while (*adlst)
		{
			tmp = *adlst;
			*adlst = (*adlst)->next;
			ft_dlstdelone(&tmp, del, del_data);
		}
	}
}
