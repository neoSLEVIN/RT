/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_cl_float3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 19:42:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 01:34:38 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "jc_parser.h"

cl_float3	jc_get_cl_float3(const t_jc_field *parent, const char *child_name)
{
	t_jc_field	clf3_field;
	cl_float3	clf3;

	clf3_field = jc_get_field(child_name, parent, JC_ARR);
	if (jc_get_array_length(&clf3_field) != 3)
	{
		ft_printf("%zu\n", jc_get_array_length(&clf3_field));
		ft_printf("Error:\t%s%s\n", clf3_field.full_name,
			" must be an array and have only three float elements");
		exit(1);
	}
	clf3.x = jc_get_float_idx(&clf3_field, 0);
	clf3.y = jc_get_float_idx(&clf3_field, 1);
	clf3.z = jc_get_float_idx(&clf3_field, 2);
	jc_clear_field(&clf3_field);
	return (clf3);
}
