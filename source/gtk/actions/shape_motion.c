/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 04:52:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 07:02:45 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	move_shape_by_camera_movement(t_rt *rt, guint key)
{
	DTO_CAM	*cam;
	FLT3	*shape_pos;

	cam = &rt->ocl->dto.cam;
	shape_pos = &rt->info->s_marker->dto->transform.position;
	if (key == GDK_KEY_space)
		*shape_pos = v3_add(*shape_pos, v3_scale(cam->upguide, STEP));
	else if (key == GDK_KEY_c)
		*shape_pos = v3_sub(*shape_pos, v3_scale(cam->upguide, STEP));
	else if (key == GDK_KEY_w)
		*shape_pos = v3_add(*shape_pos, v3_scale(cam->forward, STEP * 2));
	else if (key == GDK_KEY_s)
		*shape_pos = v3_sub(*shape_pos, v3_scale(cam->forward, STEP * 2));
	else if (key == GDK_KEY_d)
		*shape_pos = v3_add(*shape_pos, v3_scale(cam->right, STEP));
	else if (key == GDK_KEY_a)
		*shape_pos = v3_sub(*shape_pos, v3_scale(cam->right, STEP));
	else
		return ;
	rt->info->update_shapes = TRUE;
}

void	move_shape_by_camera_rotating(t_rt *rt, guint key)
{
	FLT3		v_shape;
	DTO_CAM		*cam;
	cl_float	angle;

	cam = &rt->ocl->dto.cam;
	v_shape = v3_sub(rt->info->s_marker->dto->transform.position, cam->origin);
	angle = RAD;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_6 || key == GDK_KEY_q)
		angle *= -1.0f;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		angle *= -rt->info->axis.y;
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
		angle *= -rt->info->axis.x;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		v_shape = v3_rot_v(v_shape, cam->right, angle);
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
		v_shape = v3_rot_v(v_shape, cam->upguide, angle);
	else if (key == GDK_KEY_q || key == GDK_KEY_e)
		v_shape = v3_rot_v(v_shape, cam->forward, angle);
	else if (key == GDK_KEY_KP_Decimal)
		v_shape = v3_scale(v_shape, -1.0);
	else
		return ;
	rt->info->s_marker->dto->transform.position = v3_add(cam->origin, v_shape);
	rt->info->update_shapes = TRUE;
}

void	move_shape_by_mouse(t_rt *rt, INT2 diff)
{
	FLT3	v_shape;
	DTO_CAM	*cam;
	FLT2	angle;

	cam = &rt->ocl->dto.cam;
	v_shape = v3_sub(rt->info->s_marker->dto->transform.position, cam->origin);
	angle = (FLT2){(cl_float)diff.x / COLS * PI / 4 * rt->info->axis.x,
				(cl_float)diff.y / ROWS * PI / 6 * rt->info->axis.y};
	(rt->info->axis.x == 1 && !rt->info->right_mc) ? angle.x *= -1 : 0;
	(rt->info->axis.y == 1 && !rt->info->right_mc) ? angle.y *= -1 : 0;
	if (angle.x)
		v_shape = v3_rot_v(v_shape, cam->upguide, angle.x);
	if (angle.y)
		v_shape = v3_rot_v(v_shape, cam->right, angle.y);
	if (rt->info->scroll_mc)
		v_shape = v3_scale(v_shape, -1.0f);
	rt->info->s_marker->dto->transform.position = v3_add(cam->origin, v_shape);
	rt->info->lmc_start_pos = rt->info->lmc_current_pos;
	rt->info->update_shapes = TRUE;
}
