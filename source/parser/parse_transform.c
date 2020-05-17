/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/15 20:47:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

TRANSFORM	parse_transform(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	transform_field;
	TRANSFORM	trans;

	transform_field = jc_get_field(parent, child_name, JC_OBJ);
	trans.position = parse_cl_float3(transform_field, "position");
	trans.direction = parse_cl_float3_or_default(transform_field, "direction",
		(FLT3){0.0f, 1.0f, 0.0f});
	trans.direction = v3_norm(trans.direction);
	if (v3_length(trans.direction) == 0.0f)
		parse_error(jc_full_name(transform_field), "direction",
			"The vector must not be a zero vector.");
	trans.rotation = parse_cl_float3_or_default(transform_field, "rotation",
		(FLT3){0.0f, 0.0f, 0.0f});
	return (trans);
}
