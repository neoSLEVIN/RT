/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*rev;
	char	*start_rev;
	size_t	len;

	len = 0;
	rev = NULL;
	start_rev = NULL;
	if (str != NULL)
	{
		len = ft_strlen(str);
		if ((rev = ft_strnew(len)) != NULL)
		{
			start_rev = rev;
			while (*str)
				str++;
			str--;
			while (len--)
				*rev++ = *str--;
			*rev = '\0';
		}
	}
	return (start_rev);
}
