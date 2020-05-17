/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:12:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 07:23:58 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	make_action(t_rt *rt)
{
	(rt->info->space_key) ? move_camera_with_shape(rt, GDK_KEY_space) : 0;
	(rt->info->c_key) ? move_camera_with_shape(rt, GDK_KEY_c) : 0;
	(rt->info->w_key) ? move_camera_with_shape(rt, GDK_KEY_w) : 0;
	(rt->info->s_key) ? move_camera_with_shape(rt, GDK_KEY_s) : 0;
	(rt->info->a_key) ? move_camera_with_shape(rt, GDK_KEY_a) : 0;
	(rt->info->d_key) ? move_camera_with_shape(rt, GDK_KEY_d) : 0;
	(rt->info->q_key) ? rotate_camera_with_shape(rt, GDK_KEY_q) : 0;
	(rt->info->e_key) ? rotate_camera_with_shape(rt, GDK_KEY_e) : 0;
	(rt->info->num_2) ? rotate_camera_with_shape(rt, GDK_KEY_KP_2) : 0;
	(rt->info->num_4) ? rotate_camera_with_shape(rt, GDK_KEY_KP_4) : 0;
	(rt->info->num_6) ? rotate_camera_with_shape(rt, GDK_KEY_KP_6) : 0;
	(rt->info->num_8) ? rotate_camera_with_shape(rt, GDK_KEY_KP_8) : 0;
	if (rt->info->num_decimal)
		rotate_camera_with_shape(rt, GDK_KEY_KP_Decimal);
	if (rt->info->right_mc || rt->info->scroll_mc)
		rotate_camera_by_mouse_with_shape(rt);
	else if (rt->info->left_mc && rt->info->s_marker != NULL)
		move_shape_by_mouse(rt,
			i2_sub(rt->info->lmc_current_pos, rt->info->lmc_start_pos));
	(rt->info->update_cam) ? update_cam_arg(rt->ocl, &rt->info->update_cam) : 0;
	(rt->info->update_shapes) ? update_shapes_arg(rt->ocl,
						&rt->info->update_s_cnt, &rt->info->update_shapes) : 0;
}
