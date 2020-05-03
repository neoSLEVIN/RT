/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:05:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/03 04:03:44 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_transform	parse_transform(const t_jc_field *parent, const char *child_name)
{
	t_jc_field	transform_field;
	t_transform	trans;

	transform_field = jc_get_field(child_name, parent, JC_OBJ);
	trans.position = jc_get_cl_float3(&transform_field, "position");
	trans.direction = jc_get_cl_float3(&transform_field, "direction");
	trans.rotation = jc_get_cl_float3(&transform_field, "rotation");
	jc_clear_field(&transform_field);
	return (trans);
}
