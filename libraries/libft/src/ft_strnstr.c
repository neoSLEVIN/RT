/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:09:41 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/31 15:09:23 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_haystack;
	size_t	len_needle;
	size_t	i;

	i = 0;
	len_haystack = ft_strlen(haystack);
	len_needle = ft_strlen(needle);
	while (i + len_needle <= len && i + len_needle <= len_haystack)
	{
		if (ft_strncmp(haystack, needle, len_needle) == 0)
			return ((char *)haystack);
		i++;
		haystack++;
	}
	return (NULL);
}
