/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:31:53 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:31:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static cl_float	get_cam_rotation(DTO_CAM *cam)
{
	cl_float	angle;

	angle = v3_angle_to_xz(cam->right);
	if (v3_angle_to_xz(cam->upguide) < 0.0f)
		angle = ((angle < 0) ? -PI : PI) - angle;
	if (angle == 0.0f && cam->upguide.y == 0.0f)
		angle = -atan2f(cam->right.z, -cam->right.x);
	return (angle);
}

void			s_camera_obj(t_serializer *s, DTO_CAM *dto, CAMERA *cam)
{
	s_open_obj_with_name(s, "camera");
	s_name(s, "position");
	s_float3(s, dto->origin);
	s_comma(s);
	s_name(s, "direction");
	s_float3(s, v3_norm(dto->forward));
	s_comma(s);
	s_name(s, "rotation");
	s_float(s, rad_to_deg(get_cam_rotation(dto)));
	s_comma(s);
	s_name(s, "display");
	s_int2(s, cam->display);
	s_comma(s);
	s_name(s, "fov");
	s_int(s, cam->fov);
	s_comma(s);
	s_name(s, "fps");
	s_int(s, cam->fps);
	s_close_obj(s);
}
