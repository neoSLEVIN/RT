/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_array_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:43:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 16:43:37 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	jc_get_array_length(const t_field *field)
{
	if (json_object_get_type(field->obj) == json_type_null)
		return 0;
	if (json_object_get_type(field->obj) != json_type_array)
	{
		ft_printf("Error:\tBad field type:\n%s%s\n%s%s\n%s%s\n",
				"\tField: ", field->full_name,
				"\tExpected type: ", json_type_to_name(json_type_array),
				"\tParsed type: ",
				json_type_to_name(json_object_get_type(field->obj)));
		exit(1);
	}
	return (json_object_array_length(field->obj));
}
