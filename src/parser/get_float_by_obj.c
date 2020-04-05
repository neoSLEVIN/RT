/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float_by_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:55:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 05:55:14 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

float	get_float_by_obj(const json_object *obj, const char *field_name)
{
	double	res;

	if (json_object_get_type(obj) != json_type_double &&
		json_object_get_type(obj) != json_type_int)
	{
		ft_printf("Error:\tThe value type must be an int or double: %s",
				field_name);
		exit(1);
	}
	res = json_object_get_double(obj);
	if (res < (-MAX_FLOAT) || res > (MAX_FLOAT) ||
		(res > (-MIN_FLOAT) && res < (MIN_FLOAT) && res != 0.0))
	{
		ft_printf("Error:\tIncorrect value of float: %s", field_name);
		exit(1);
	}
	return ((float)res);
}
