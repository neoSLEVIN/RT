/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cl_float3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

FLT3	parse_cl_float3_or_default(const JC_FIELD parent,
									const char *child_name, FLT3 default_value)
{
	JC_FIELD	clf3_field;
	FLT3		clf3;

	clf3_field = jc_get_field(parent, child_name, (JC_ARR | JC_NULL));
	if (jc_is_null(clf3_field))
		return (default_value);
	if (jc_get_array_length(clf3_field) != 3)
		parse_error(jc_full_name(clf3_field), NULL,
			"Field must be an array and have only three float elements");
	clf3.x = jc_get_float_idx(clf3_field, 0);
	clf3.y = jc_get_float_idx(clf3_field, 1);
	clf3.z = jc_get_float_idx(clf3_field, 2);
	return (clf3);
}

FLT3	parse_cl_float3(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	clf3_field;
	FLT3		clf3;

	clf3_field = jc_get_field(parent, child_name, JC_ARR);
	if (jc_get_array_length(clf3_field) != 3)
		parse_error(jc_full_name(clf3_field), NULL,
			"Field must be an array and have only three float elements");
	clf3.x = jc_get_float_idx(clf3_field, 0);
	clf3.y = jc_get_float_idx(clf3_field, 1);
	clf3.z = jc_get_float_idx(clf3_field, 2);
	return (clf3);
}
