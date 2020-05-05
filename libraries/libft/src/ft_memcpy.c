/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 22:55:49 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 20:10:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*pdst;
	unsigned const char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned const char *)src;
	if (dst == NULL && src == NULL && n > 0)
		return (NULL);
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}
