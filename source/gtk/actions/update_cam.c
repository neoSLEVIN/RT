/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/14 03:40:06 by cschoen          ###   ########.fr       */
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
	update_cam(rt);
}

//TODO delete this before defending
void	del_print(t_rt *rt)
{
	cl_float	angle;

	angle = v3_angle_to_xz(rt->ocl->dto.cam.right);
	if (v3_angle_to_xz(rt->ocl->dto.cam.upguide) < 0.0f)
		angle = ((angle < 0) ? -PI : PI) - angle;
	if (angle == 0.0f && rt->ocl->dto.cam.upguide.y == 0.0f)
		angle = -atan2f(rt->ocl->dto.cam.right.z, -rt->ocl->dto.cam.right.x);
	ft_printf("%s\t%f %f %f\n%s\t%f %f %f\n%s\t%f %.20f %f\n%s\t%f %f %f\n%s\t%f\n%s\n",
		"position:",
		rt->ocl->dto.cam.origin.x,
		rt->ocl->dto.cam.origin.y,
		rt->ocl->dto.cam.origin.z,
		"forward:",
		rt->ocl->dto.cam.forward.x,
		rt->ocl->dto.cam.forward.y,
		rt->ocl->dto.cam.forward.z,
		"right:\t",
		rt->ocl->dto.cam.right.x,
		rt->ocl->dto.cam.right.y,
		rt->ocl->dto.cam.right.z,
		"upguide:",
		rt->ocl->dto.cam.upguide.x,
		rt->ocl->dto.cam.upguide.y,
		rt->ocl->dto.cam.upguide.z,
		"angle:\t",
		rad_to_deg(angle),
		"=============================================");
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
	else if (key == GDK_KEY_KP_Decimal)
	{
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->num_decimal);
		cam->forward = v3_scale(cam->forward, -1.0);
		cam->right = v3_scale(cam->right, -1.0);
	}
	else
		return ;
	cam->target = v3_add(cam->origin, cam->forward);
	cam->up = v3_cross(cam->right, cam->forward);
	update_cam(rt);
}
