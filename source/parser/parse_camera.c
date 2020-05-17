/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/15 22:22:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

CAMERA	parse_camera(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	cam_field;
	CAMERA		cam;

	cam_field = jc_get_field(parent, child_name, JC_OBJ);
	cam.dto = NULL;
	cam.position = parse_cl_float3(cam_field, "position");
	cam.direction = parse_cl_float3_or_default(cam_field, "direction",
					(FLT3){0.0f, 0.0f, 1.0f});
	cam.direction = v3_norm(cam.direction);
	if (v3_length(cam.direction) == 0.0f)
		parse_error(jc_full_name(cam_field), "direction",
					"The vector must not be a zero vector.");
	cam.rotation = jc_get_float_or_default(cam_field, "rotation", 0.0f);
	cam.rotation = deg_to_rad(cam.rotation);
	return (cam);
}
