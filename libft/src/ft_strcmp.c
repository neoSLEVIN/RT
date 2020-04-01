/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:00:21 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/30 21:01:07 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned const char	*ps1;
	unsigned const char	*ps2;

	ps1 = (unsigned const char *)s1;
	ps2 = (unsigned const char *)s2;
	if (ps1 == ps2)
		return (0);
	while (*ps1 && *ps2 && *ps1 == *ps2)
	{
		ps1++;
		ps2++;
	}
	return (*ps1 - *ps2);
}
