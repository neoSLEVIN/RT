/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:02:33 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/14 15:08:34 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*start;
	char			*str;

	index = 0;
	start = NULL;
	str = NULL;
	if (s != NULL && f != NULL)
	{
		str = ft_strnew(ft_strlen(s));
		if (str == NULL)
			return (NULL);
		start = str;
		while (*s)
			*str++ = f(index++, *s++);
		*str = '\0';
	}
	return (start);
}
