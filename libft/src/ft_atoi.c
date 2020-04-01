/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 22:46:56 by cschoen           #+#    #+#             */
/*   Updated: 2019/07/14 22:21:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	num;
	int				sign;
	int				stop_loop;

	num = 0;
	stop_loop = 0;
	sign = 1;
	while ((*str >= '\t' && *str <= '\r') || (*str == ' '))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (ft_isdigit(*str) && stop_loop++ < 19)
	{
		num *= 10;
		if (stop_loop == 19 && ((9223372036854775807 - num) < (*str - '0')))
			return (sign < 0 ? 0 : -1);
		num += *str++ - '0';
	}
	if (stop_loop == 20)
		return (sign < 0 ? 0 : -1);
	return ((int)(num * sign));
}
