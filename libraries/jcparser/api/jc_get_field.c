/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"
#include "jc_parser.h"

static char	*jcp_str_of_types(JC_TYPE types)
{
	char	*res;
	size_t	len;

	len = 0;
	(types & JC_NULL) ? len += 5 : 0;
	(types & JC_OBJ) ? len += 7 : 0;
	(types & JC_ARR) ? len += 6 : 0;
	(types & JC_ELEM) ? len += 17 : 0;
	(types & JC_BOOL) ? len += 8 : 0;
	(types & JC_INT) ? len += 8 : 0;
	(types & JC_DBL) ? len += 13 : 0;
	(types & JC_STR) ? len += 7 : 0;
	if (len == 0 || !(res = ft_strnew(len + 1)))
		return (NULL);
	ft_strcat(res, "|");
	(types & JC_NULL) ? ft_strcat(res, "null|") : 0;
	(types & JC_OBJ) ? ft_strcat(res, "object|") : 0;
	(types & JC_ARR) ? ft_strcat(res, "array|") : 0;
	(types & JC_ELEM) ? ft_strcat(res, "element of array|") : 0;
	(types & JC_BOOL) ? ft_strcat(res, "boolean|") : 0;
	(types & JC_INT) ? ft_strcat(res, "integer|") : 0;
	(types & JC_DBL) ? ft_strcat(res, "float/double|") : 0;
	(types & JC_STR) ? ft_strcat(res, "string|") : 0;
	return (res);
}

static void	jcp_print_bad_type_error(const JC_FIELD *field,
									JC_TYPE allowed_types)
{
	char	*allowed_types_str;
	char	*field_types_str;

	allowed_types_str = jcp_str_of_types(allowed_types);
	field_types_str =
		jcp_str_of_types(field->obj == NULL ? JC_NULL : field->obj->type);
	if (allowed_types_str == NULL || field_types_str == NULL)
	{
		ft_printf("Error:\tBad field type:\n%s%s\n",
			"\tField: ", field->full_name);
		exit(1);
	}
	ft_printf("Error:\tBad field type:\n%s%s\n%s%s\n%s%s\n",
		"\tField: ", field->full_name,
		"\tExpected type: ", allowed_types_str,
		"\tParsed type: ", field_types_str);
	ft_strdel(&allowed_types_str);
	ft_strdel(&field_types_str);
	exit(1);
}

JC_FIELD	jc_get_field_idx(const size_t index, const JC_FIELD parent,
						JC_TYPE type)
{
	JC_FIELD	field;

	if (parent.full_name == NULL)
		ft_error("NPE: parent name (jc_get_field_idx)");
	if (parent.obj == NULL)
		ft_error("NPE: parent object (jc_get_field_idx)");
	if (index < 0 || index >= parent.obj->cnt_of_nodes)
		ft_error("Index out of range (jc_get_field_idx)");
	field.full_name = jcp_field_with_index(parent.full_name, index);
	field.obj = jcp_get_elem_by_idx(index, parent.obj);
	if (field.obj->full_name)
		ft_strdel(&field.obj->full_name);
	field.obj->full_name = field.full_name;
	if (jc_compare_types(field, type) == FALSE)
		jcp_print_bad_type_error(&field, type);
	return (field);
}

JC_FIELD	jc_get_field(const char *field_name, const JC_FIELD parent,
					JC_TYPE type)
{
	JC_FIELD	field;

	if (parent.full_name == NULL)
		ft_error("NPE: parent name (jc_get_field)");
	if (parent.obj == NULL)
		ft_error("NPE: parent object (jc_get_field)");
	if (field_name == NULL)
		ft_error("NPE: field name (jc_get_field)");
	field.full_name = jcp_parent_dot_child(parent.full_name, field_name);
	field.obj = jcp_get_obj_by_key(field_name, parent.obj);
	if (field.obj->full_name)
		ft_strdel(&field.obj->full_name);
	field.obj->full_name = field.full_name;
	if (jc_compare_types(field, type) == FALSE)
		jcp_print_bad_type_error(&field, type);
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
