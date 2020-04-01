/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 13:35:44 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 20:11:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned const char	*psrc;
	unsigned char		*pdst;
	unsigned char		pc;

	pc = (unsigned char)c;
	pdst = (unsigned char *)dst;
	psrc = (unsigned const char *)src;
	while (n--)
	{
		*pdst = *psrc;
		if (*psrc == pc)
		{
			pdst++;
			return ((void *)pdst);
		}
		pdst++;
		psrc++;
	}
	return (NULL);
}
