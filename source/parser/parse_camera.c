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
	cam.transform = parse_transform(cam_field, "transform");
	if (jc_is_null(jc_get_field(
			jc_get_field(cam_field, "transform", JC_OBJ), "direction", JC_ARR)))
		cam.transform.direction = (FLT3){0.0f, 0.0f, 1.0f};
	return (cam);
}
