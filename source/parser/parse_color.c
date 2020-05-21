/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	atoi16(const char *num, const int char_cnt)
{
	int	digit[2];
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (*num >= '0' && *num <= '9')
			digit[i] = *num - 48;
		else if (*num >= 'A' && *num <= 'F')
			digit[i] = *num - 55;
		else if (*num >= 'a' && *num <= 'f')
			digit[i] = *num - 87;
		else
			digit[i] = 0;
		char_cnt == 2 ? ++num : 0;
	}
	return (16 * digit[0] + digit[1]);
}

static int	is_valid_hex(const char *str)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(str);
	if (len != 6 && len != 3 && len != 1)
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]) &&
			(str[i] < 'A' || str[i] > 'f' || (str[i] > 'F' && str[i] < 'a')))
			return (0);
	return (1);
}

static int	str_to_rgb(FLT3 *col, const char *str)
{
	size_t	len;

	if (!is_valid_hex(str))
		return (0);
	len = ft_strlen(str);
	if (len == 1)
	{
		col->x = atoi16(str, 1) / 255.0;
		col->y = atoi16(str, 1) / 255.0;
		col->z = atoi16(str, 1) / 255.0;
	}
	else if (len == 3)
	{
		col->x = atoi16(str, 1) / 255.0;
		col->y = atoi16(&str[1], 1) / 255.0;
		col->z = atoi16(&str[2], 1) / 255.0;
	}
	else if (len == 6)
	{
		col->x = atoi16(str, 2) / 255.0;
		col->y = atoi16(&str[2], 2) / 255.0;
		col->z = atoi16(&str[4], 2) / 255.0;
	}
	return (1);
}

FLT3		parse_color(const JC_FIELD parent, const char *child_name)
{
	char	*str_color;
	FLT3	color;

	str_color = jc_get_string(parent, child_name, FALSE);
	if (!str_to_rgb(&color, str_color))
		parse_error(jc_full_name(parent), child_name,
			"Incorrect format of color");
	ft_strdel(&str_color);
	return (color);
}

FLT3		parse_color_or_default(const JC_FIELD parent,
							const char *child_name, char *default_color)
{
	char	*str_color;
	FLT3	color;

	str_color = jc_get_string(parent, child_name, TRUE);
	if (!str_color)
		str_color = default_color;
	if (!str_to_rgb(&color, str_color))
		parse_error(jc_full_name(parent), child_name,
					"Incorrect format of color");
	if (str_color != default_color)
		ft_strdel(&str_color);
	return (color);
}
