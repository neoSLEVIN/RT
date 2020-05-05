/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 19:45:05 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/31 17:30:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ic;

	ic = (unsigned char)c;
	while (*s && *s != ic)
		s++;
	if (*s == ic)
		return ((char *)s);
	return (NULL);
}
