/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pft_clean_big(t_double *num)
{
	int	i;

	i = -1;
	num->big[0] += 1;
	while (num->big[++i] > '9')
	{
		num->big[i] -= 10;
		if (num->big[i + 1])
			num->big[i + 1] += 1;
	}
}

static void	pft_clean_little(t_double *num, char *rc)
{
	*rc += 1;
	while (*rc > '9')
	{
		*rc -= 10;
		if (*(rc + 1))
		{
			++rc;
			*rc += 1;
		}
		else
			pft_clean_big(num);
	}
}

static void	pft_round_big(t_double *num, int little_len)
{
	char	c;

	c = num->little[little_len - 1];
	num->little[little_len - 1] = 'R';
	if (c > '5')
		return (pft_clean_big(num));
	if (c == '5')
	{
		if ((little_len == 1) && ((num->big[0] - 48) % 2))
			return (pft_clean_big(num));
		else if (little_len > 1)
			while (--little_len)
				if (num->little[little_len - 1] > '0')
					return (pft_clean_big(num));
		if (!little_len && ((num->big[0] - 48) % 2))
			return (pft_clean_big(num));
	}
}

static void	pft_round_little(t_double *num, int little_len, int precision)
{
	char	*rc;
	char	c;

	rc = &num->little[little_len - precision];
	c = num->little[little_len - precision - 1];
	num->little[little_len - precision - 1] = 'R';
	if (c > '5')
		return (pft_clean_little(num, rc));
	if (c == '5')
	{
		if ((little_len - precision == 1) && ((*rc - 48) % 2))
			return (pft_clean_little(num, rc));
		else if (little_len - precision > 1)
			while (++precision && (precision != little_len))
				if (num->little[little_len - precision - 1] > '0')
					return (pft_clean_little(num, rc));
		if (!(little_len - precision) && ((num->little[0] - 48) % 2))
			return (pft_clean_little(num, rc));
	}
}

void		pft_round_f(t_double *num, int precision)
{
	int	little_len;

	little_len = ft_strlen(num->little);
	if (precision == 0)
		pft_round_big(num, little_len);
	else if (little_len > precision)
		pft_round_little(num, little_len, precision);
}
