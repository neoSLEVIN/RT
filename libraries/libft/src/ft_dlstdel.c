/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
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
