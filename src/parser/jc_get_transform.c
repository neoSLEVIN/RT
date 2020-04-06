/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:05:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 01:15:56 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_transform	jc_get_transform(const t_field *parent, const char *child_name)
{
	t_field		transform_field;
	t_transform	transform;

	transform_field = jc_get_field(child_name, parent, json_type_object);
	transform.position = jc_get_cl_float3(&transform_field, "position");
	transform.direction = jc_get_cl_float3(&transform_field, "direction");
	transform.rotation = jc_get_cl_float3(&transform_field, "rotation");
	jc_clear_field(&transform_field);
	return (transform);
}
