/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/11 06:50:57 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

# define STEP 0.5

void	update_cam(t_rt *rt)
{
	int	err;

	err = clSetKernelArg(rt->ocl->kernel, 4, sizeof(DTO_CAM),
						&(rt->ocl->dto.cam));
	check_error_cl(err,"clSetKernelArg", "cam");
}

void	move_cam(t_rt *rt, guint key)
{
	DTO_CAM	*cam;

	cam = &rt->ocl->dto.cam;
	if (key == GDK_KEY_space)
		cam->origin = v3_add(cam->origin, v3_scale(cam->upguide, STEP));
	else if (key == GDK_KEY_c)
		cam->origin = v3_sub(cam->origin, v3_scale(cam->upguide, STEP));
	else if (key == GDK_KEY_w)
		cam->origin = v3_add(cam->origin, v3_scale(cam->forward, STEP * 2));
	else if (key == GDK_KEY_s)
		cam->origin = v3_sub(cam->origin, v3_scale(cam->forward, STEP * 2));
	else if (key == GDK_KEY_d)
		cam->origin = v3_add(cam->origin, v3_scale(cam->right, STEP));
	else if (key == GDK_KEY_a)
		cam->origin = v3_sub(cam->origin, v3_scale(cam->right, STEP));
	else
		return ;
	cam->target = v3_add(cam->origin, cam->forward);
	rt->scene->cam.transform.position = cam->origin;
	update_cam(rt);
}

void	rotate_cam(t_rt *rt, guint key)
{
	DTO_CAM		*cam;
	cl_float	angle;

	angle = RAD;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_6 || key == GDK_KEY_q)
		angle *= -1.0f;
	cam = &rt->ocl->dto.cam;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
	{
		cam->forward = v3_rot_v(cam->forward, cam->right, angle);
		cam->upguide = v3_rot_v(cam->upguide, cam->right, angle);
	}
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
	{
		cam->forward = v3_rot_v(cam->forward, cam->upguide, angle);
		cam->right = v3_rot_v(cam->right, cam->upguide, angle);
	}
	else if (key == GDK_KEY_q || key == GDK_KEY_e)
	{
		cam->upguide = v3_rot_v(cam->upguide, cam->forward, angle);
		cam->right = v3_rot_v(cam->right, cam->forward, angle);
	}
	else
		return ;
	cam->target = v3_add(cam->origin, cam->forward);
	cam->up = v3_cross(cam->right, cam->forward);
	rt->scene->cam.transform.direction = cam->forward;
	update_cam(rt);
}
