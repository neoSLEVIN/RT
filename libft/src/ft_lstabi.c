/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstabi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 19:58:13 by cschoen           #+#    #+#             */
/*   Updated: 2019/02/13 13:51:10 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstabi(t_list **alst, t_list *cur, size_t n)
{
	t_list	*start;

	start = NULL;
	if (cur != NULL && alst != NULL)
	{
		start = *alst;
		if (n == 0 || *alst == NULL)
			ft_lstadd(alst, cur);
		else
		{
			while (--n && (*alst)->next != NULL)
				*alst = (*alst)->next;
			cur->next = (*alst)->next;
			(*alst)->next = cur;
			*alst = start;
		}
	}
}
