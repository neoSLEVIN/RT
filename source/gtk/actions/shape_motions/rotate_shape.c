/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 04:52:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:00 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static cl_float	get_angle_for_rotate_shape(t_rt *rt, guint key)
{
	cl_float	angle;

	angle = rt->scene->angle * 2;
	if (key == GDK_KEY_k || key == GDK_KEY_l || key == GDK_KEY_u)
		angle *= -1.0f;
	if (key == GDK_KEY_k || key == GDK_KEY_i)
		angle *= -rt->info->axis.y;
	else if (key == GDK_KEY_j || key == GDK_KEY_l)
		angle *= -rt->info->axis.x;
	return (angle);
}

static _Bool	rotate_transform(DTO_CAM *cam, guint key, cl_float angle,
								TRANSFORM *trans)
{
	if (key == GDK_KEY_k || key == GDK_KEY_i)
	{
		trans->direction = v3_rot_v(trans->direction, cam->right, angle);
		trans->rotation = v3_rot_v(trans->rotation, cam->right, angle);
	}
	else if (key == GDK_KEY_j || key == GDK_KEY_l)
	{
		trans->direction = v3_rot_v(trans->direction, cam->upguide, angle);
		trans->rotation = v3_rot_v(trans->rotation, cam->upguide, angle);
	}
	else if (key == GDK_KEY_u || key == GDK_KEY_o)
	{
		trans->direction = v3_rot_v(trans->direction, cam->forward, angle);
		trans->rotation = v3_rot_v(trans->rotation, cam->forward, angle);
	}
	else
		return (FALSE);
	return (TRUE);
}

static void		rotate_dots(DTO_SHAPE *dto, DTO_CAM *cam, cl_float angle,
							guint key)
{
	int			i;
	FLT3		*dots;
	FLT3		dot_target;
	cl_float	len;

	i = -1;
	dots = dto->transform.dots;
	while (++i < 3)
	{
		dot_target = v3_sub(dots[i], dto->transform.position);
		len = v3_length(v3_sub(dots[i], dto->transform.position));
		if ((key == GDK_KEY_k || key == GDK_KEY_i) && len > 0.01f)
			dot_target = v3_rot_v(dot_target, cam->right, angle);
		else if ((key == GDK_KEY_j || key == GDK_KEY_l) && len > 0.01f)
			dot_target = v3_rot_v(dot_target, cam->upguide, angle);
		else if ((key == GDK_KEY_u || key == GDK_KEY_o) && len > 0.01f)
			dot_target = v3_rot_v(dot_target, cam->forward, angle);
		dots[i] = v3_add(dto->transform.position, dot_target);
	}
}

static void		rotate_points(t_off *off, DTO_CAM *cam, cl_float angle,
								guint key)
{
	int			i;
	FLT3		*points;
	FLT3		dot_target;
	cl_float	len;

	i = -1;
	points = off->points;
	while (++i < off->p_cnt)
	{
		dot_target = points[i];
		len = v3_length(points[i]);
		if ((key == GDK_KEY_k || key == GDK_KEY_i) && len > 0.001f)
			dot_target = v3_rot_v(dot_target, cam->right, angle);
		else if ((key == GDK_KEY_j || key == GDK_KEY_l) && len > 0.001f)
			dot_target = v3_rot_v(dot_target, cam->upguide, angle);
		else if ((key == GDK_KEY_u || key == GDK_KEY_o) && len > 0.001f)
			dot_target = v3_rot_v(dot_target, cam->forward, angle);
		points[i] = dot_target;
	}
}

void			rotate_shape(t_rt *rt, guint key)
{
	DTO_CAM		*cam;
	cl_float	angle;

	ASSERT_SHAPE_VOID(rt->info->s_marker);
	cam = &rt->ocl->dto.cam;
	angle = get_angle_for_rotate_shape(rt, key);
	if (!rotate_transform(cam, key, angle, &rt->info->s_marker->dto->transform))
		return ;
	rotate_dots(rt->info->s_marker->dto, cam, angle, key);
	if (rt->info->s_marker->dto->type == OFF)
	{
		rotate_points(&rt->scene->off, cam, angle, key);
		rt->info->update_off_points = TRUE;
	}
	rotate_sections(rt->info->s_marker->dto, cam, angle, key);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_pos);
	rt->info->update_s_sec = TRUE;
}
