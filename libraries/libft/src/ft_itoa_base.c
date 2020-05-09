/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_get_char(int mod, char c)
{
	char	new_c;

	if (mod > 36)
		return (0);
	new_c = '0';
	while (mod--)
	{
		++new_c;
		if (new_c == ':')
			new_c = c;
	}
	return (new_c);
}

static int	ft_get_len(uintmax_t num, uintmax_t base)
{
	int	len;

	len = 1;
	while ((num /= base) > 0)
		++len;
	return (len);
}

char		*ft_itoa_base(uintmax_t num, uintmax_t base, char c)
{
	char	*str;
	int		mod;
	int		len;

	if (base <= 1)
		return (NULL);
	if (num == 0)
		return (ft_strdup("0"));
	len = ft_get_len(num, base);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		mod = num % base;
		num /= base;
		if (!(str[len] = ft_get_char(mod, c)))
		{
			ft_strdel(&str);
			return (NULL);
		}
	}
	return (str);
}
