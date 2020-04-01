/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:56:50 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 20:17:56 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*ps;
	unsigned char		pc;

	pc = (unsigned char)c;
	ps = (unsigned const char *)s;
	while (n--)
	{
		if (*ps == pc)
			return ((void *)ps);
		ps++;
	}
	return (NULL);
}
