/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:15:58 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 20:27:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*buff;

	buff = dst;
	while (*src && len)
	{
		*dst++ = *src++;
		len--;
	}
	while (len)
	{
		*dst++ = '\0';
		len--;
	}
	return (buff);
}
