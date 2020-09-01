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

static void	init_default_transform(TRANSFORM *transform)
{
	transform->position = (FLT3){0.0f, 0.0f, 0.0f};
	transform->direction = (FLT3){0.0f, 1.0f, 0.0f};
	transform->rotation = (FLT3){0.0f, 0.0f, 0.0f};
}

TRANSFORM	set_triangle_position_to_transform(TRANSFORM *transform, FLT3 *dots)
{
	transform->position =
		v3_scale(v3_add(v3_add(dots[0], dots[1]), dots[2]), 1.0f / 3.0f);
	return (*transform);
}

TRANSFORM	parse_transform(const JC_FIELD parent, const char *child_name,
							SHAPE_TYPE type, FLT3 *params)
{
	JC_FIELD	transform_field;
	TRANSFORM	trans;

	init_default_transform(&trans);
	if (type == TRIANGLE)
		return (set_triangle_position_to_transform(&trans, params));
	transform_field = jc_get_field(parent, child_name, JC_OBJ);
	trans.position = parse_cl_float3(transform_field, "position");
	trans.direction = parse_cl_float3_or_default(transform_field, "direction",
		(FLT3){0.0f, 1.0f, 0.0f});
	trans.direction = v3_norm(trans.direction);
	if (v3_length(trans.direction) == 0.0f)
		parse_error(jc_full_name(transform_field), "direction",
			"The vector must not be a zero vector.");
	if (type == CAPPEDPLANE)
	{
		//TODO complete validation
		trans.rotation = parse_cl_float3_or_default(transform_field, "rotation",
							(FLT3){0.0f, 0.0f, 0.0f});
		trans.rotation = v3_norm(trans.rotation);
	}
	return (trans);
}
