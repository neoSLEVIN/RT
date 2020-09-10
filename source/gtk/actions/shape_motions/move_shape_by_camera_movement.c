/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_shape_by_camera_movement.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:20:44 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:20:45 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static _Bool	change_vec_by_camera_movement(FLT3 *vec, DTO_CAM *cam,
											guint key, cl_float step)
{
	if (key == GDK_KEY_space)
		*vec = v3_add(*vec, v3_scale(cam->upguide, step));
	else if (key == GDK_KEY_c)
		*vec = v3_sub(*vec, v3_scale(cam->upguide, step));
	else if (key == GDK_KEY_w)
		*vec = v3_add(*vec, v3_scale(cam->forward, step * 2));
	else if (key == GDK_KEY_s)
		*vec = v3_sub(*vec, v3_scale(cam->forward, step * 2));
	else if (key == GDK_KEY_d)
		*vec = v3_add(*vec, v3_scale(cam->right, step));
	else if (key == GDK_KEY_a)
		*vec = v3_sub(*vec, v3_scale(cam->right, step));
	else
		return (FALSE);
	return (TRUE);
}

void			move_shape_by_camera_movement(t_rt *rt, guint key)
{
	DTO_CAM		*cam;
	DTO_SHAPE	*shape;
	cl_float	step;

	cam = &rt->ocl->dto.cam;
	step = rt->scene->step;
	ASSERT_SHAPE_VOID(rt->info->s_marker);
	shape = rt->info->s_marker->dto;
	if (!change_vec_by_camera_movement(&shape->transform.position, cam,
			key, step))
		return ;
	change_vec_by_camera_movement(&shape->transform.dots[0], cam, key, step);
	change_vec_by_camera_movement(&shape->transform.dots[1], cam, key, step);
	change_vec_by_camera_movement(&shape->transform.dots[2], cam, key, step);
	move_sections_by_camera_movement(rt->info->s_marker->dto, cam, key, step);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_pos);
	rt->info->update_s_sec = TRUE;
}
