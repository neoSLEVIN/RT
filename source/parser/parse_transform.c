/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:05:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:37:29 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

TRANSFORM	parse_transform(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	transform_field;
	TRANSFORM	trans;

	transform_field = jc_get_field(child_name, parent, JC_OBJ);
	trans.position = parse_cl_float3(transform_field, "position");
	trans.direction = parse_cl_float3(transform_field, "direction");
	trans.rotation = parse_cl_float3(transform_field, "rotation");
	// TODO Maybe make rotation as cl_float
	trans.direction = v3_norm(trans.direction);
	return (trans);
}
