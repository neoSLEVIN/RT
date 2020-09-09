/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_shape_by_camera_rotating.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:20:50 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:20:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

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

static _Bool	change_vec_by_camera_rotating(FLT3 *vec, DTO_CAM *cam,
											guint key, cl_float angle)
{
	if (key == GDK_KEY_KP_2 || key == GDK_KEY_KP_8)
		*vec = v3_rot_v(*vec, cam->right, angle);
	else if (key == GDK_KEY_KP_4 || key == GDK_KEY_KP_6)
		*vec = v3_rot_v(*vec, cam->upguide, angle);
	else if (key == GDK_KEY_q || key == GDK_KEY_e)
		*vec = v3_rot_v(*vec, cam->forward, angle);
	else if (key == GDK_KEY_KP_Decimal)
		*vec = v3_rot_v(*vec, cam->upguide, PI);
	else
		return (FALSE);
	return (TRUE);
}

static void		change_triangle_dots_by_camera_rotating(FLT3 diff, FLT3 *dots)
{
	int	i;

	i = -1;
	while (++i < 3)
		dots[i] = v3_add(dots[i], diff);
}

void			move_shape_by_camera_rotating(t_rt *rt, guint key)
{
	FLT3		v_shape;
	FLT3		v_shape_old;
	DTO_CAM		*cam;
	cl_float	angle;

	cam = &rt->ocl->dto.cam;
	ASSERT_SHAPE_VOID(rt->info->s_marker);
	v_shape = v3_sub(rt->info->s_marker->dto->transform.position, cam->origin);
	v_shape_old = v_shape;
	angle = get_angle_to_move_shape(rt->scene->angle, key, rt->info->axis);
	if (!change_vec_by_camera_rotating(&v_shape, cam, key, angle))
		return ;
	rt->info->s_marker->dto->transform.position = v3_add(cam->origin, v_shape);
	change_triangle_dots_by_camera_rotating(v3_sub(v_shape, v_shape_old),
									rt->info->s_marker->dto->transform.dots);
	move_sections_by_mouse(v3_sub(v_shape, v_shape_old),
						rt->info->s_marker->dto->sections);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_pos);
	rt->info->update_s_sec = TRUE;
}
