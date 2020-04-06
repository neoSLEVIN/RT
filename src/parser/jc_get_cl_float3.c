/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_cl_float3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 19:42:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 01:15:56 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

cl_float3	jc_get_cl_float3(const t_field *parent, const char *child_name)
{
	t_field		clf3_field;
	cl_float3	clf3;

	clf3_field = jc_get_field(child_name, parent, json_type_object);
	clf3.x = jc_get_float(&clf3_field, "x");
	clf3.y = jc_get_float(&clf3_field, "y");
	clf3.z = jc_get_float(&clf3_field, "z");
	jc_clear_field(&clf3_field);
	return (clf3);
}
