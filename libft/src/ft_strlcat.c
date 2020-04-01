/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 16:19:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/03/29 16:57:41 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	i = 1;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	while (*dst && i++)
		dst++;
	while (*src && (i++ < size))
		*dst++ = *src++;
	*dst = '\0';
	return (len_dst <= size ? (len_dst + len_src) : (size + len_src));
}
