/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_calculator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pft_calc_pos_power(char *summand, char *temp, int power)
{
	int	stack;
	int	i;

	(summand[0] == '0' && summand[1] == '\0') ? (summand[0] = '1') : 0;
	(power > 0) ? ft_bzero(temp, FT_NUM_LENGTH) : 0;
	while (power > 0)
	{
		ft_strcpy(temp, summand);
		stack = 0;
		i = -1;
		while (temp[++i] && (i < (FT_NUM_LENGTH - 1)))
		{
			summand[i] = (temp[i] - 48) * 2 + 48 + stack;
			stack = (summand[i] > '9') ? 1 : 0;
			(summand[i] > '9') ? (summand[i] -= 10) : 0;
		}
		if (stack)
			summand[i] += (summand[i] ? 1 : '1');
		--power;
	}
}

void	pft_calc_neg_power(char *summand, char *temp, int power)
{
	int	i;
	int	stack;

	(summand[0] == '0' && summand[1] == '\0') ? ++power : 0;
	(summand[0] == '0' && summand[1] == '\0') ? (summand[0] = '5') : 0;
	(power < 0) ? ft_bzero(temp, FT_NUM_LENGTH) : 0;
	while (power < 0)
	{
		i = -1;
		stack = 0;
		ft_strcpy(temp, summand);
		while (temp[++i] && (i < (FT_NUM_LENGTH - 1)))
		{
			summand[i] = ((temp[i] - 48) * 5 + stack) % 10 + 48;
			stack = ((temp[i] - 48) * 5 + stack) / 10;
		}
		summand[i] += stack + (summand[i] ? 0 : '0');
		++power;
	}
}

void	pft_calculate_sum_big(char *dst, char *src)
{
	int	i;
	int	stack;

	i = -1;
	stack = 0;
	while (src[++i] && (i < FT_NUM_LENGTH - 1))
	{
		dst[i] = (dst[i] ? dst[i] : 48) + (src[i] - 48) + stack;
		stack = (dst[i] > '9') ? 1 : 0;
		(dst[i] > '9') ? (dst[i] -= 10) : 0;
	}
	if (stack)
		dst[i] += dst[i] ? 1 : '1';
}

void	pft_calculate_sum_little(char *dst, char *src)
{
	int		i;
	int		stack;
	size_t	diff;
	size_t	dst_len;

	i = -1;
	stack = 0;
	dst_len = ft_strlen(dst);
	diff = ft_strlen(src) - dst_len;
	if (diff)
		while (dst_len--)
			dst[dst_len + diff] = dst[dst_len];
	while (diff--)
		dst[diff] = '0';
	while (src[++i] && (i < FT_NUM_LENGTH - 1))
	{
		dst[i] = (dst[i] ? dst[i] : 48) + (src[i] - 48) + stack;
		stack = (dst[i] > '9') ? 1 : 0;
		(dst[i] > '9') ? (dst[i] -= 10) : 0;
	}
	if (stack)
		dst[i] += dst[i] ? 1 : '1';
}
