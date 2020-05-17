/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 06:43:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	move_camera(t_rt *rt, guint key)
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
	rt->info->update_cam = TRUE;
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
}

void	rotate_camera(t_rt *rt, guint key)
{
	DTO_CAM		*cam;
	cl_float	angle;

	angle = RAD;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_6 || key == GDK_KEY_q)
		angle *= -1.0f;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		angle *= -rt->info->axis.y;
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
		angle *= -rt->info->axis.x;
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
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_decimal);
		cam->forward = v3_scale(cam->forward, -1.0);
		cam->right = v3_scale(cam->right, -1.0);
	}
	else
		return ;
	cam->target = v3_add(cam->origin, cam->forward);
	cam->up = v3_cross(cam->right, cam->forward);
	rt->info->update_cam = TRUE;
}

void	rotate_camera_by_mouse(t_rt *rt, INT2 diff)
{
	DTO_CAM	*cam;
	FLT2	angle;

	cam = &rt->ocl->dto.cam;
	angle = (FLT2){(cl_float)diff.x / COLS * PI / 4 * rt->info->axis.x,
				(cl_float)diff.y / ROWS * PI / 6 * rt->info->axis.y};
	if (angle.x)
	{
		cam->forward = v3_rot_v(cam->forward, cam->upguide, angle.x);
		cam->right = v3_rot_v(cam->right, cam->upguide, angle.x);
	}
	if (angle.y)
	{
		cam->forward = v3_rot_v(cam->forward, cam->right, angle.y);
		cam->upguide = v3_rot_v(cam->upguide, cam->right, angle.y);
	}
	if (rt->info->scroll_mc)
	{
		cam->forward = v3_scale(cam->forward, -1.0f);
		cam->right = v3_scale(cam->right, -1.0f);
	}
	cam->target = v3_add(cam->origin, cam->forward);
	cam->up = v3_cross(cam->right, cam->forward);
	rt->info->rmc_start_pos = rt->info->rmc_current_pos;
	rt->info->update_cam = TRUE;
}
