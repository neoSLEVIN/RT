/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcnt(const char *str, const char *re)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	if (!str || !re)
		return (0);
	if (!*re && *str)
		return (1);
	while (*str)
	{
		i = -1;
		while (re[++i])
			while (*str == re[i] && str++)
				i = 0;
		*str ? ++cnt : 0;
		i = 0;
		while (*str && *str != re[i])
		{
			i = 0;
			while (re[i] && *str != re[i])
				++i;
			!re[i] ? ++str : 0;
		}
	}
	return (cnt);
}
