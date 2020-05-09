/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*start;
	char	*str;

	start = NULL;
	str = NULL;
	if (s != NULL && f != NULL)
	{
		str = ft_strnew(ft_strlen(s));
		if (str == NULL)
			return (NULL);
		start = str;
		while (*s)
			*str++ = f(*s++);
		*str = '\0';
	}
	return (start);
}
