/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:55:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 05:35:08 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

float	jc_get_float(const t_field *parent, const char *child_name)
{
	json_object	*float_obj;
	char		*field_name;
	double		res;

	float_obj = jc_get_obj_by_key(child_name, parent);
	field_name = jc_parent_dot_child(parent->full_name, child_name);
	if (json_object_get_type(float_obj) != json_type_double &&
		json_object_get_type(float_obj) != json_type_int)
	{
		ft_printf("Error:\tThe value type must be an int or double: %s",
				field_name);
		exit(1);
	}
	res = json_object_get_double(float_obj);
	if (res < (-MAX_FLOAT) || res > (MAX_FLOAT) ||
		(res > (-MIN_FLOAT) && res < (MIN_FLOAT) && res != 0.0))
	{
		ft_printf("Error:\tIncorrect value of float: %s", field_name);
		exit(1);
	}
	ft_strdel(&field_name);
	return ((float)res);
}
