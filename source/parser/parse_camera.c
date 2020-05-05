/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 14:39:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:37:29 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cam	parse_camera(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	cam_field;
	t_cam		cam;

	cam_field = jc_get_field(child_name, parent, JC_OBJ);
	cam.transform = parse_transform(cam_field, "transform");
	return (cam);
}
