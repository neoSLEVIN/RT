/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

CAMERA	parse_camera(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	cam_field;
	CAMERA		cam;

	cam_field = jc_get_field(child_name, parent, JC_OBJ);
	cam.transform = parse_transform(cam_field, "transform");
	// TODO validation for params
	return (cam);
}
