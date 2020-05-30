/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jcp_print_bad_type_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 22:30:29 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/15 22:30:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jcp_parser.h"

void	jcp_print_bad_parent_type_error(const JCP_OBJ *obj,
											JC_TYPE allowed_types)
{
	char	*allowed_types_str;
	char	*field_types_str;

	allowed_types_str = jcp_str_of_types(allowed_types);
	field_types_str = jcp_str_of_types(obj == NULL ? JC_NULL : obj->type);
	if (allowed_types_str == NULL || field_types_str == NULL)
	{
		ft_printf("Error:\tBad parent field type:\n%s%s\n",
				"\tField: ", (obj == NULL) ? NULL : obj->full_name);
		exit(1);
	}
	ft_printf("Error:\tBad parent field type:\n%s%s\n%s%s\n%s%s\n",
			"\tField: ", (obj == NULL) ? NULL : obj->full_name,
			"\tExpected type: ", allowed_types_str,
			"\tParsed type: ", field_types_str);
	ft_strdel(&allowed_types_str);
	ft_strdel(&field_types_str);
	exit(1);
}

void	jcp_print_bad_type_error(const JCP_OBJ *obj, JC_TYPE allowed_types)
{
	char	*allowed_types_str;
	char	*field_types_str;

	allowed_types_str = jcp_str_of_types(allowed_types);
	field_types_str = jcp_str_of_types(obj == NULL ? JC_NULL : obj->type);
	if (allowed_types_str == NULL || field_types_str == NULL)
	{
		ft_printf("Error:\tBad field type:\n%s%s\n",
			"\tField: ", (obj == NULL) ? NULL : obj->full_name);
		exit(1);
	}
	ft_printf("Error:\tBad field type:\n%s%s\n%s%s\n%s%s\n",
		"\tField: ", (obj == NULL) ? NULL : obj->full_name,
		"\tExpected type: ", allowed_types_str,
		"\tParsed type: ", field_types_str);
	ft_strdel(&allowed_types_str);
	ft_strdel(&field_types_str);
	exit(1);
}
