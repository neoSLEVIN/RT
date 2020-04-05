/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_by_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:59:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 05:59:10 by cschoen          ###   ########lyon.fr   */
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

static int	str_to_rgb(t_color *col, const char *str)
{
	size_t	len;

	if (!is_valid_hex(str))
		return (0);
	len = ft_strlen(str);
	if (len == 1)
	{
		col->r = atoi16(str, 1);
		col->g = atoi16(str, 1);
		col->b = atoi16(str, 1);
	}
	else if (len == 3)
	{
		col->r = atoi16(str, 1);
		col->g = atoi16(&str[1], 1);
		col->b = atoi16(&str[2], 1);
	}
	else if (len == 6)
	{
		col->r = atoi16(str, 2);
		col->g = atoi16(&str[2], 2);
		col->b = atoi16(&str[4], 2);
	}
	return (1);
}

t_color		get_color_by_obj(json_object *obj, const char *field_name)
{
	t_color		res;
	const char	*color;

	if (json_object_get_type(obj) != json_type_string)
	{
		ft_printf("Error:\tThe value type must be a string: %s",
				field_name);
		exit(1);
	}
	color = json_object_get_string(obj);
	if (!str_to_rgb(&res, color))
	{
		ft_printf("Error:\tIncorrect format of color: %s", field_name);
		exit(1);
	}
	return (res);
}
