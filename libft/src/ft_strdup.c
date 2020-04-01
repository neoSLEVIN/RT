/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 22:55:02 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 20:23:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new_str;
	char	*start;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	start = new_str;
	if (new_str == NULL)
		return (NULL);
	while (*s1)
		*new_str++ = *s1++;
	*new_str = '\0';
	return (start);
}
