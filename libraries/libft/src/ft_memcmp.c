/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:40:41 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 20:21:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*ps1;
	unsigned const char	*ps2;

	ps1 = (unsigned const char *)s1;
	ps2 = (unsigned const char *)s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*ps1++ != *ps2++)
			return (ps1[-1] - ps2[-1]);
	}
	return (ps1[-1] - ps2[-1]);
}
