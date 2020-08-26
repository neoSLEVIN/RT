/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 04:52:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/27 05:18:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	move_shape_by_camera_movement(t_rt *rt, guint key)
{
	DTO_CAM	*cam;
	FLT3	*shape_pos;

	cam = &rt->ocl->dto.cam;
	if (!rt->info->s_marker || !rt->info->s_marker->dto)
		return ;
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
	move_sections_by_camera_movement(rt->info->s_marker->dto, cam, key);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_pos);
	rt->info->update_s_sec = TRUE;
}

static cl_float	get_angle_to_move_shape(cl_float default_angle, guint key,
											INT2 axis)
{
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_6 || key == GDK_KEY_q)
		default_angle *= -1.0f;
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		default_angle *= -axis.y;
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
		default_angle *= -axis.x;
	return (default_angle);
}

void	move_shape_by_camera_rotating(t_rt *rt, guint key)
{
	FLT3		v_shape;
	FLT3		v_shape_old;
	DTO_CAM		*cam;
	cl_float	angle;

	cam = &rt->ocl->dto.cam;
	ASSERT_SHAPE_VOID(rt->info->s_marker);
	v_shape = v3_sub(rt->info->s_marker->dto->transform.position, cam->origin);
	v_shape_old = v_shape;
	angle = get_angle_to_move_shape(RAD, key, rt->info->axis);
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		v_shape = v3_rot_v(v_shape, cam->right, angle);
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
		v_shape = v3_rot_v(v_shape, cam->upguide, angle);
	else if (key == GDK_KEY_q || key == GDK_KEY_e)
		v_shape = v3_rot_v(v_shape, cam->forward, angle);
	else if (key == GDK_KEY_KP_Decimal)
		v_shape = v3_rot_v(v_shape, cam->upguide, PI);
	else
		return ;
	rt->info->s_marker->dto->transform.position = v3_add(cam->origin, v_shape);
	move_sections_by_mouse(v3_sub(v_shape, v_shape_old),
		rt->info->s_marker->dto->sections);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_pos);
	rt->info->update_s_sec = TRUE;
}

void	move_shape_by_mouse(t_rt *rt, INT2 diff)
{
	FLT3	v_shape;
	FLT3	v_shape_old;
	DTO_CAM	*cam;
	FLT2	angle;

	if (!rt->info->s_marker || !rt->info->s_marker->dto)
		return ;
	cam = &rt->ocl->dto.cam;
	v_shape = v3_sub(rt->info->s_marker->dto->transform.position, cam->origin);
	v_shape_old = v_shape;
	angle = get_angle_by_diff(diff, rt->info->axis,
							(INT2){cam->screen_w, cam->screen_h});
	(rt->info->axis.x == 1 && !rt->info->right_mc) ? angle.x *= -1 : 0;
	(rt->info->axis.y == 1 && !rt->info->right_mc) ? angle.y *= -1 : 0;
	(angle.x) ? v_shape = v3_rot_v(v_shape, cam->upguide, angle.x) : v_shape;
	(angle.y) ? v_shape = v3_rot_v(v_shape, cam->right, angle.y) : v_shape;
	(rt->info->scroll_cnt) ? v_shape = v3_add(v_shape,
		v3_scale(cam->forward, rt->info->scroll_cnt * 4)) : v_shape;
	rt->info->s_marker->dto->transform.position = v3_add(cam->origin, v_shape);
	rt->info->scroll_cnt = 0;
	rt->info->lmc_start_pos = rt->info->lmc_current_pos;
	move_sections_by_mouse(v3_sub(v_shape, v_shape_old),
		rt->info->s_marker->dto->sections);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_pos);
	rt->info->update_s_sec = TRUE;
}

void	rotate_shape(t_rt *rt, guint key)
{
	FLT3		*shape_dir;
	DTO_CAM		*cam;
	cl_float	angle;

	ASSERT_SHAPE_VOID(rt->info->s_marker);
	cam = &rt->ocl->dto.cam;
	angle = RAD * 2;
	if (key == GDK_KEY_k || key == GDK_KEY_l || key == GDK_KEY_u)
		angle *= -1.0f;
	if (key == GDK_KEY_k || key == GDK_KEY_i)
		angle *= -rt->info->axis.y;
	else if (key == GDK_KEY_j || key == GDK_KEY_l)
		angle *= -rt->info->axis.x;
	shape_dir = &rt->info->s_marker->dto->transform.direction;
	if (key == GDK_KEY_k || key == GDK_KEY_i)
		*shape_dir = v3_rot_v(*shape_dir, cam->right, angle);
	else if (key == GDK_KEY_j || key == GDK_KEY_l)
		*shape_dir = v3_rot_v(*shape_dir, cam->upguide, angle);
	else if (key == GDK_KEY_u || key == GDK_KEY_o)
		*shape_dir = v3_rot_v(*shape_dir, cam->forward, angle);
	else
		return ;
	rotate_sections(rt->info->s_marker->dto, cam, angle, key);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_rot);
	rt->info->update_s_sec = TRUE;
}
