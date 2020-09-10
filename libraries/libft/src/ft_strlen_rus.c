/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_rus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 11:21:45 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/06 11:21:46 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_rus(const char *s)
{
	size_t	len;
	size_t	non_ascii_cnt;

	len = 0;
	non_ascii_cnt = 0;
	while (*s)
	{
		++len;
		if (*s++ < 0)
			++non_ascii_cnt;
	}
	return (len - non_ascii_cnt / 2);
}
