/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
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
