/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_calculate_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pft_calculate_long_big(t_double *num)
{
	int	last_power;
	int	cur_power;
	int	power;
	int	i;

	i = -1;
	last_power = 0;
	power = (short)((num->exp) - (unsigned short)0x3FFF);
	cur_power = power - 63;
	if (cur_power < 0)
	{
		i = -cur_power - 1;
		cur_power = 0;
	}
	--cur_power;
	while (++cur_power <= power && ++i < 64)
		if ((num->mantissa >> i) & (unsigned long long)(1))
		{
			pft_calc_pos_power(num->summand, num->temp,
				cur_power - last_power);
			pft_calculate_sum_big(num->big, num->summand);
			last_power = cur_power;
		}
	ft_bzero(num->summand, FT_NUM_LENGTH);
	ft_bzero(num->temp, FT_NUM_LENGTH);
}

static void	pft_calculate_long_little(t_double *num)
{
	int	last_power;
	int	cur_power;
	int	power;
	int	i;

	ft_strcpy(num->summand, "0");
	ft_strcpy(num->temp, "0");
	i = 64;
	power = (short)(num->exp - (unsigned short)0x3FFF);
	cur_power = power;
	if (cur_power >= 0)
	{
		i = 63 - cur_power;
		cur_power = -1;
	}
	last_power = 0;
	++cur_power;
	while ((--cur_power >= (power - 63)) && (--i >= 0))
		if ((num->mantissa >> i) & (unsigned long long)(1))
		{
			pft_calc_neg_power(num->summand, num->temp,
				cur_power - last_power);
			pft_calculate_sum_little(num->little, num->summand);
			last_power = cur_power;
		}
}

static void	pft_calculate_big(t_double *num)
{
	int	last_power;
	int	cur_power;
	int	power;
	int	i;

	i = -1;
	last_power = 0;
	power = (short)((num->exp >> 4) - (unsigned short)0x3FF);
	cur_power = power - 52;
	if (cur_power < 0)
	{
		i = -cur_power - 1;
		cur_power = 0;
	}
	--cur_power;
	while (++cur_power <= power && ++i < 53)
		if ((num->mantissa >> i) & (unsigned long long)(1))
		{
			pft_calc_pos_power(num->summand, num->temp,
				cur_power - last_power);
			pft_calculate_sum_big(num->big, num->summand);
			last_power = cur_power;
		}
	ft_bzero(num->summand, FT_NUM_LENGTH);
	ft_bzero(num->temp, FT_NUM_LENGTH);
}

static void	pft_calculate_little(t_double *num)
{
	int	last_power;
	int	cur_power;
	int	power;
	int	i;

	ft_strcpy(num->summand, "0");
	ft_strcpy(num->temp, "0");
	i = 53;
	power = (short)((num->exp >> 4) - (unsigned short)0x3FF);
	cur_power = power;
	if (cur_power >= 0)
	{
		i = 52 - cur_power;
		cur_power = -1;
	}
	last_power = 0;
	++cur_power;
	while ((--cur_power >= (power - 52)) && (--i >= 0))
		if ((num->mantissa >> i) & (unsigned long long)(1))
		{
			pft_calc_neg_power(num->summand, num->temp,
				cur_power - last_power);
			pft_calculate_sum_little(num->little, num->summand);
			last_power = cur_power;
		}
}

void		pft_calculate_f(t_double *num, _Bool is_long)
{
	if (is_long)
	{
		num->sign = (*((unsigned char*)&num->ld + 9)) >> 7;
		num->exp = (*((unsigned short*)&num->ld + 4) & (unsigned short)0x7FFF);
		num->mantissa = (*((unsigned long long*)&num->ld));
	}
	else
	{
		num->sign = (*((unsigned char*)&num->d + 7)) >> 7;
		num->exp = (*((unsigned short*)&num->d + 3) & (unsigned short)0x7FF0);
		num->mantissa = (*((unsigned long long*)&num->d) &
			(unsigned long long)0xFFFFFFFFFFFFF);
		(num->exp) ? (num->mantissa |= (((unsigned long long)1) << 52)) : 0;
	}
	pft_is_inf_nan(num, is_long);
	if ((!num->exp && !num->mantissa) || num->is_inf || num->is_nan)
		return ;
	if (is_long && !(((num->exp < (unsigned short)0x3FFF) ||
		(num->exp == (unsigned short)0x3FFF &&
			(num->mantissa < (unsigned long long)0x8000000000000000)))))
		pft_calculate_long_big(num);
	else if (!is_long && !(num->exp < (unsigned long long)0x3FF0))
		pft_calculate_big(num);
	is_long ? pft_calculate_long_little(num) : pft_calculate_little(num);
}
