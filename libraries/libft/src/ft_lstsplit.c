/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s, char c)
{
	size_t	num;

	num = 0;
	while (*s && *s++ != c)
		num++;
	return (num);
}

static _Bool	ft_is_end(char const *s, char c)
{
	while (*s && *s == c)
		++s;
	if (!*s)
		return (1);
	return (0);
}

t_list			*ft_lstsplit(char const *s, char c)
{
	t_list	*elem;
	char	*str;
	size_t	len;

	elem = NULL;
	if (s == NULL)
		return (NULL);
	while (*s && *s == c)
		++s;
	len = ft_len(s, c);
	if (!(str = ft_strsub(s, 0, len)))
		return (NULL);
	if (!(elem = ft_lstnew(str, len + 1)))
	{
		ft_strdel(&str);
		return (NULL);
	}
	ft_strdel(&str);
	if (ft_is_end(s + len, c))
		elem->next = NULL;
	else if (!(elem->next = ft_lstsplit(s + len, c)))
		ft_lstdelone(&elem, ft_del);
	return (elem);
}
