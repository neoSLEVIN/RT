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

static void			init_default_transform(TRANSFORM *transform)
{
	transform->position = (FLT3){0.0f, 0.0f, 0.0f};
	transform->direction = (FLT3){0.0f, 1.0f, 0.0f};
	transform->rotation = (FLT3){1.0f, 0.0f, 0.0f};
	transform->angle = 0;
}

static void			init_transform_dots(TRANSFORM *trans, FLT3 *dots)
{
	FLT3		forward;
	FLT3		right;
	FLT3		upguide;
	cl_float	rot_y;

	forward = v3_norm(trans->direction);
	rot_y = atan2f(forward.x, forward.z);
	right = (FLT3){-1.0f, 0.0f, 0.0f};
	right = v3_rot_y(right, rot_y);
	right = v3_rot_v(right, forward, -trans->angle);
	upguide = v3_norm(v3_cross(right, forward));
	dots[0] = v3_add(trans->position, right);
	dots[1] = v3_add(trans->position, upguide);
	dots[2] = v3_sub(v3_sub(v3_scale(trans->position, 3.0f), dots[0]), dots[1]);
}

static TRANSFORM	parse_triangle_dots(const JC_FIELD shape_field,
										TRANSFORM *trans)
{
	JC_FIELD	dots_field;

	dots_field = jc_get_field(shape_field, "dots", JC_OBJ);
	trans->dots[0] = parse_cl_float3(dots_field, "a");
	trans->dots[1] = parse_cl_float3(dots_field, "b");
	trans->dots[2] = parse_cl_float3(dots_field, "c");
	trans->position =
		v3_scale(v3_add(v3_add(trans->dots[0], trans->dots[1]), trans->dots[2]),
				1.0f / 3.0f);
	return (*trans);
}

static void			parse_rotation(const JC_FIELD transform_field,
										TRANSFORM *trans)
{
	cl_float	rot_y;

	trans->angle =
		jc_get_float_or_default(transform_field, "rotate angle", 0.0f);
	trans->angle = deg_to_rad(trans->angle);
	rot_y = atan2f(trans->direction.x, trans->direction.z);
	trans->rotation = v3_rot_y(trans->rotation, rot_y);
	trans->rotation =
		v3_rot_v(trans->rotation, trans->direction, -trans->angle);
	trans->rotation = v3_norm(trans->rotation);
}

TRANSFORM			parse_transform(const JC_FIELD parent,
									const char *child_name, SHAPE_TYPE type)
{
	JC_FIELD	transform_field;
	TRANSFORM	trans;

	init_default_transform(&trans);
	if (type == TRIANGLE)
		return (parse_triangle_dots(parent, &trans));
	transform_field = jc_get_field(parent, child_name, JC_OBJ);
	trans.position = parse_cl_float3(transform_field, "position");
	trans.direction = parse_cl_float3_or_default(transform_field, "direction",
		(FLT3){0.0f, 1.0f, 0.0f});
	trans.direction = v3_norm(trans.direction);
	if (v3_length(trans.direction) == 0.0f)
		parse_error(jc_full_name(transform_field), "direction",
			"The vector must not be a zero vector.");
	parse_rotation(transform_field, &trans);
	init_transform_dots(&trans, trans.dots);
	return (trans);
}
