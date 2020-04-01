/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:08:50 by cschoen           #+#    #+#             */
/*   Updated: 2019/10/13 16:46:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	start;
	size_t			finish;
	size_t			len;

	if (s == NULL)
		return (NULL);
	if ((len = ft_strlen(s)) == 0)
		return (ft_strnew(0));
	start = 0;
	finish = len - 1;
	while ((s[start] >= '\t' && s[start] <= '\r') || s[start] == ' ')
		++start;
	while ((s[finish] >= '\t' && s[finish] <= '\r') || s[finish] == ' ')
		--finish;
	if (start <= finish)
		return (ft_strsub(s, start, finish - start + 1));
	else
		return (ft_strnew(0));
	return (NULL);
}
