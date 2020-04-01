/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 02:02:08 by cschoen           #+#    #+#             */
/*   Updated: 2020/01/12 23:17:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_dlist **adlst, void (*del)(void *, size_t),
					void (*del_data)(void *))
{
	if (*adlst != NULL && del != NULL)
	{
		del((*adlst)->content, (*adlst)->content_size);
		(*adlst)->content = NULL;
		if (del_data)
			del_data((*adlst)->data);
		(*adlst)->data = NULL;
		free(*adlst);
		*adlst = NULL;
	}
}
