/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/24 14:23:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"
#include "jc_parser.h"

JC_FIELD	jc_get_field_idx(const JC_FIELD parent, const size_t index,
						JC_TYPE type)
{
	JC_FIELD	field;

	if (parent.full_name == NULL)
		ft_error("NPE: parent name (jc_get_field_idx)");
	if (parent.obj == NULL)
		ft_error("NPE: parent object (jc_get_field_idx)");
	if (jc_compare_types(parent, JC_ARR) == FALSE)
		jcp_print_bad_parent_type_error(parent.obj, JC_ARR);
	if (index < 0 || index >= parent.obj->cnt_of_nodes)
		ft_error("Index out of range (jc_get_field_idx)");
	field.full_name = jcp_field_with_index(parent.full_name, index);
	field.obj = jcp_get_elem_by_idx(index, parent.obj);
	if (field.obj->full_name)
		ft_strdel(&field.obj->full_name);
	field.obj->full_name = field.full_name;
	if (type == JC_ANY)
		return (field);
	if (jc_compare_types(field, type) == FALSE)
		jcp_print_bad_type_error(field.obj, type);
	return (field);
}

JC_FIELD	jc_get_field(const JC_FIELD parent, const char *field_name,
					JC_TYPE type)
{
	JC_FIELD	field;

	if (parent.full_name == NULL)
		ft_error("NPE: parent name (jc_get_field)");
	if (parent.obj == NULL)
		ft_error("NPE: parent object (jc_get_field)");
	if (field_name == NULL)
		ft_error("NPE: field name (jc_get_field)");
	if (jc_compare_types(parent, JC_OBJ) == FALSE)
		jcp_print_bad_parent_type_error(parent.obj, JC_OBJ);
	field.full_name = jcp_parent_dot_child(parent.full_name, field_name);
	field.obj = jcp_get_obj_by_key(field_name, parent.obj);
	if (field.obj->full_name)
		ft_strdel(&field.obj->full_name);
	field.obj->full_name = field.full_name;
	if (type == JC_ANY)
		return (field);
	if (jc_compare_types(field, type) == FALSE)
		jcp_print_bad_type_error(field.obj, type);
	return (field);
}

JC_FIELD	jc_get_json_field(const char *file_name, size_t max_size)
{
	char		*parsed_text;
	JC_FIELD	json_field;

	parsed_text = ft_get_text_file(file_name, max_size);
	if (*parsed_text == '\0')
	{
		ft_printf("Error:\tEmpty file \"%s\"\n", file_name);
		exit(1);
	}
	if (!(json_field.full_name = ft_strdup("JSON")))
		ft_error("Can't allocate memory");
	json_field.obj = jcp_get_main_object(parsed_text);
	json_field.obj->full_name = json_field.full_name;
	return (json_field);
}
