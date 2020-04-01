/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:05:23 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 21:03:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned const char	*ps1;
	unsigned const char	*ps2;

	ps1 = (unsigned const char *)s1;
	ps2 = (unsigned const char *)s2;
	if (len == 0)
		return (0);
	while (len--)
	{
		if (!*ps1 || !*ps2)
			return (*ps1 - *ps2);
		if (*ps1++ != *ps2++)
			return (ps1[-1] - ps2[-1]);
	}
	return (ps1[-1] - ps2[-1]);
}
