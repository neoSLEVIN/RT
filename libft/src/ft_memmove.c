/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:04:40 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/31 15:14:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	unsigned const char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned const char *)src;
	if (dst == NULL && src == NULL && len > 0)
		return (NULL);
	if (len == 0 || dst == src)
		return (dst);
	if (dst < src)
	{
		while (len--)
			*pdst++ = *psrc++;
	}
	else
	{
		while (len)
		{
			pdst[len - 1] = psrc[len - 1];
			len--;
		}
	}
	return (dst);
}
