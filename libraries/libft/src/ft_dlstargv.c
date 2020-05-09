/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstargv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstargv(int argc, char **argv, int first_index, int last_index)
{
	t_dlist	*start;
	t_dlist	*elem;
	size_t	len;

	if (argc <= 0 || first_index < 0 || first_index > last_index ||
		last_index >= argc || !argv || !argv[first_index])
		return (NULL);
	len = ft_strlen(argv[first_index]);
	if (!(elem = ft_dlstnew(argv[first_index], len + 1)))
		return (NULL);
	start = elem;
	while (first_index++ < last_index)
	{
		len = ft_strlen(argv[first_index]);
		if (!(elem->next = ft_dlstnew(argv[first_index], len + 1)))
		{
			ft_dlstdel(&start, ft_del, NULL);
			return (NULL);
		}
		elem->next->prev = elem;
		elem = elem->next;
	}
	return (start);
}
