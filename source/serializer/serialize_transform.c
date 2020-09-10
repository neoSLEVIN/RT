/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:30 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static cl_float	get_shape_rotation_angle(TRANSFORM *trans)
{
	cl_float	angle;
	FLT3		upguide;

	angle = v3_angle_to_xz(trans->rotation);
	upguide = v3_norm(v3_cross(trans->rotation, trans->direction));
	if (v3_angle_to_xz(upguide) < 0.0f)
		angle = ((angle < 0) ? -PI : PI) - angle;
	if (angle == 0.0f && upguide.y == 0.0f)
		angle = -atan2f(trans->rotation.z, -trans->rotation.x);
	return (angle);
}

static void		s_triangle_dots(t_serializer *s, FLT3 *dots)
{
	s_open_obj_with_name(s, "dots");
	s_name(s, "a");
	s_float3(s, dots[0]);
	s_comma(s);
	s_name(s, "b");
	s_float3(s, dots[1]);
	s_comma(s);
	s_name(s, "c");
	s_float3(s, dots[2]);
	s_close_obj(s);
}

void			s_transform_obj(t_serializer *s, TRANSFORM *transform,
								SHAPE_TYPE type)
{
	if (type == TRIANGLE)
		return (s_triangle_dots(s, transform->dots));
	s_open_obj_with_name(s, "transform");
	s_name(s, "position");
	s_float3(s, transform->position);
	s_comma(s);
	s_name(s, "direction");
	s_float3(s, v3_norm(transform->direction));
	if (type == CAPPEDPLANE || type == BOX)
	{
		s_comma(s);
		s_name(s, "rotate angle");
		s_float(s, rad_to_deg(get_shape_rotation_angle(transform)));
	}
	s_close_obj(s);
}
