/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:56:14 by cschoen           #+#    #+#             */
/*   Updated: 2018/12/31 17:25:53 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*new_b;
	unsigned char	new_c;

	i = 0;
	new_b = (unsigned char *)b;
	new_c = (unsigned char)c;
	while (len--)
		new_b[i++] = new_c;
	return (b);
}
