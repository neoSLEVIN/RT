/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		len++;
	}
	if (n < 0)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	int		sign;
	char	*str;
	char	*rev;
	char	*start_rev;

	sign = 1;
	if ((rev = ft_strnew(ft_intlen(n))) == NULL)
		return (NULL);
	start_rev = rev;
	if (n < 0)
		sign = -1;
	if (n == 0)
		*rev++ = '0';
	while (n != 0)
	{
		*rev++ = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		*rev++ = '-';
	str = ft_strrev(rev - ft_strlen(start_rev));
	ft_strdel(&start_rev);
	return (str);
}
