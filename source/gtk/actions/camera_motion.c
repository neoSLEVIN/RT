/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:32 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	do_rotate_camera(DTO_CAM *cam, cl_float angle, _Bool *update_cam,
								guint key)
{
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
		cam->forward = v3_scale(cam->forward, -1.0);
		cam->right = v3_scale(cam->right, -1.0);
	}
	else
		return ;
	cam->target = v3_add(cam->origin, cam->forward);
	cam->up = v3_cross(cam->right, cam->forward);
	*update_cam = TRUE;
}

void		rotate_camera(t_rt *rt, guint key)
{
	cl_float	angle;

	angle = rt->scene->angle;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_6 || key == GDK_KEY_q)
		angle *= -1.0f;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		angle *= -rt->info->axis.y;
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
		angle *= -rt->info->axis.x;
	do_rotate_camera(&rt->ocl->dto.cam, angle, &rt->info->update_cam, key);
	if (key == GDK_KEY_KP_Decimal)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_dec);
}

void		rotate_camera_by_mouse(t_rt *rt, INT2 diff)
{
	DTO_CAM	*cam;
	FLT2	angle;

	cam = &rt->ocl->dto.cam;
	angle = get_angle_by_diff(diff, rt->info->axis,
							(INT2){cam->screen_w, cam->screen_h});
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
	cam->target = v3_add(cam->origin, cam->forward);
	cam->up = v3_cross(cam->right, cam->forward);
	rt->info->rmc_start_pos = rt->info->rmc_current_pos;
	rt->info->update_cam = TRUE;
}

void		move_camera(t_rt *rt, guint key)
{
	DTO_CAM		*cam;
	cl_float	step;

	cam = &rt->ocl->dto.cam;
	step = rt->scene->step;
	if (key == GDK_KEY_space)
		cam->origin = v3_add(cam->origin, v3_scale(cam->upguide, step));
	else if (key == GDK_KEY_c)
		cam->origin = v3_sub(cam->origin, v3_scale(cam->upguide, step));
	else if (key == GDK_KEY_w)
		cam->origin = v3_add(cam->origin, v3_scale(cam->forward, step * 2));
	else if (key == GDK_KEY_s)
		cam->origin = v3_sub(cam->origin, v3_scale(cam->forward, step * 2));
	else if (key == GDK_KEY_d)
		cam->origin = v3_add(cam->origin, v3_scale(cam->right, step));
	else if (key == GDK_KEY_a)
		cam->origin = v3_sub(cam->origin, v3_scale(cam->right, step));
	else
		return ;
	cam->target = v3_add(cam->origin, cam->forward);
	rt->info->update_cam = TRUE;
}
