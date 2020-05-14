/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/14 04:02:16 by cschoen          ###   ########.fr       */
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
	trans.direction = v3_norm(trans.direction);
	if (v3_length(trans.direction) == 0.0f)
		parse_error(jc_full_name(transform_field), "direction",
			" Length of the vector must be positive.");
	trans.rotation = jc_get_float_or_default(transform_field, "rotation", 0.0f);
	trans.rotation = deg_to_rad(trans.rotation);
	return (trans);
}
