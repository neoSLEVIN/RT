/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsplit.c                                     :+:      :+:    :+:   */
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
		++num;
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

static t_dlist	*ft_dlstsplit2(char const *s, char c,
								t_dlist **start, size_t len)
{
	t_dlist	*elem;
	char	*str;

	elem = *start;
	while (!ft_is_end(s + len, c))
	{
		s = s + len;
		while (*s && *s == c)
			++s;
		len = ft_len(s, c);
		if (!(str = ft_strsub(s, 0, len)))
			ft_dlstdel(start, ft_del, NULL);
		else if (!(elem->next = ft_dlstnew(str, len + 1)))
			ft_dlstdel(start, ft_del, NULL);
		ft_strdel(&str);
		if (!(*start))
			return (*start);
		elem->next->prev = elem;
		elem = elem->next;
	}
	return (*start);
}

t_dlist			*ft_dlstsplit(char const *s, char c)
{
	t_dlist	*start;
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		++s;
	len = ft_len(s, c);
	if (!(str = ft_strsub(s, 0, len)))
		return (NULL);
	start = ft_dlstnew(str, len + 1);
	ft_strdel(&str);
	if (!start)
		return (NULL);
	return (ft_dlstsplit2(s, c, &start, len));
}
