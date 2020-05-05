/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:07:36 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 19:18:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;

	new_lst = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = (t_list *)malloc(sizeof(lst));
	if (new_lst == NULL)
		return (NULL);
	new_lst = f(lst);
	if (lst->next != NULL)
	{
		new_lst->next = ft_lstmap(lst->next, f);
		if (new_lst->next == NULL)
		{
			free(new_lst->next);
			free(new_lst);
			new_lst = NULL;
		}
	}
	else
		new_lst->next = NULL;
	return (new_lst);
}
