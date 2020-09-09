/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_shape_by_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:20:56 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:20:56 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	calculate_v_shape(t_rt *rt, INT2 diff, DTO_CAM *cam, FLT3 *v_shape)
{
	FLT2	angle;

	angle = get_angle_by_diff(diff, rt->info->axis,
							(INT2){cam->screen_w, cam->screen_h});
	(rt->info->axis.x == 1 && !rt->info->right_mc) ? angle.x *= -1 : 0;
	(rt->info->axis.y == 1 && !rt->info->right_mc) ? angle.y *= -1 : 0;
	if (angle.x)
		*v_shape = v3_rot_v(*v_shape, cam->upguide, angle.x);
	if (angle.y)
		*v_shape = v3_rot_v(*v_shape, cam->right, angle.y);
	if (rt->info->scroll_cnt)
		*v_shape =
			v3_add(*v_shape,
				v3_scale(cam->forward,
							rt->info->scroll_cnt * 8 * rt->scene->step));
}

static void	change_triangle_dots_by_mouse(FLT3 *dots, FLT3 diff)
{
	int	i;

	i = -1;
	while (++i < 3)
		dots[i] = v3_add(dots[i], diff);
}

void		move_shape_by_mouse(t_rt *rt, INT2 diff)
{
	FLT3	v_shape;
	FLT3	v_shape_old;
	DTO_CAM	*cam;

	ASSERT_SHAPE_VOID(rt->info->s_marker);
	cam = &rt->ocl->dto.cam;
	v_shape = v3_sub(rt->info->s_marker->dto->transform.position, cam->origin);
	v_shape_old = v_shape;
	calculate_v_shape(rt, diff, cam, &v_shape);
	rt->info->s_marker->dto->transform.position = v3_add(cam->origin, v_shape);
	rt->info->scroll_cnt = 0;
	rt->info->lmc_start_pos = rt->info->lmc_current_pos;
	change_triangle_dots_by_mouse(rt->info->s_marker->dto->transform.dots,
									v3_sub(v_shape, v_shape_old));
	move_sections_by_mouse(v3_sub(v_shape, v_shape_old),
						rt->info->s_marker->dto->sections);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_pos);
	rt->info->update_s_sec = TRUE;
}
