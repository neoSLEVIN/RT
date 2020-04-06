/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 14:39:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 02:30:32 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cam	jc_get_camera(const t_field *parent, const char *child_name)
{
	t_field	cam_field;
	t_cam	cam;

	cam_field = jc_get_field(child_name, parent, json_type_object);
	cam.transform = jc_get_transform(&cam_field, "transform");
	jc_clear_field(&cam_field);
	return (cam);
}
