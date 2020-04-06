/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 02:32:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 04:41:51 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_field	jc_get_nullable_field(const char *field_name, const t_field *parent,
						json_type type)
{
	t_field	field;

	field.obj = jc_get_obj_by_key(field_name, parent);
	field.full_name = jc_parent_dot_child(parent->full_name, field_name);
	if (json_object_get_type(field.obj) != type &&
		json_object_get_type(field.obj) != json_type_null)
	{
		ft_printf("Error:\tBad field type:\n%s%s\n%s%s%s\n%s%s\n",
				"\tField: ", field.full_name,
				"\tExpected type: ", json_type_to_name(type),
				"(can be nullable)",
				"\tParsed type: ",
				json_type_to_name(json_object_get_type(field.obj)));
		exit(1);
	}
	return (field);
}

t_field	jc_get_field_idx(const int index, const t_field *parent,
						json_type type)
{
	t_field	field;

	field.full_name = jc_field_with_index(parent->full_name, index);
	field.obj = json_object_array_get_idx(parent->obj, index);
	if (json_object_get_type(field.obj) != type)
	{
		ft_printf("Error:\tBad field type:\n%s%s\n%s%s\n%s%s\n",
				"\tField: ", field.full_name,
				"\tExpected type: ", json_type_to_name(type),
				"\tParsed type: ",
				json_type_to_name(json_object_get_type(field.obj)));
		exit(1);
	}
	return (field);
}

t_field	jc_get_field(const char *field_name, const t_field *parent,
					json_type type)
{
	t_field	field;

	field.obj = jc_get_obj_by_key(field_name, parent);
	field.full_name = jc_parent_dot_child(parent->full_name, field_name);
	if (json_object_get_type(field.obj) != type)
	{
		ft_printf("Error:\tBad field type:\n%s%s\n%s%s\n%s%s\n",
				"\tField: ", field.full_name,
				"\tExpected type: ", json_type_to_name(type),
				"\tParsed type: ",
				json_type_to_name(json_object_get_type(field.obj)));
		exit(1);
	}
	return (field);
}
