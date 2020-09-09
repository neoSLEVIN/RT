/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:12:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 21:37:58 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	make_move_camera_with_shape(t_rt *rt)
{
	(rt->info->space_key) ? move_camera_with_shape(rt, GDK_KEY_space) : 0;
	(rt->info->c_key) ? move_camera_with_shape(rt, GDK_KEY_c) : 0;
	(rt->info->w_key) ? move_camera_with_shape(rt, GDK_KEY_w) : 0;
	(rt->info->s_key) ? move_camera_with_shape(rt, GDK_KEY_s) : 0;
	(rt->info->a_key) ? move_camera_with_shape(rt, GDK_KEY_a) : 0;
	(rt->info->d_key) ? move_camera_with_shape(rt, GDK_KEY_d) : 0;
}

static void	make_rotate_camera_with_shape(t_rt *rt)
{
	(rt->info->q_key) ? rotate_camera_with_shape(rt, GDK_KEY_q) : 0;
	(rt->info->e_key) ? rotate_camera_with_shape(rt, GDK_KEY_e) : 0;
	(rt->info->num_2) ? rotate_camera_with_shape(rt, GDK_KEY_KP_2) : 0;
	(rt->info->num_4) ? rotate_camera_with_shape(rt, GDK_KEY_KP_4) : 0;
	(rt->info->num_6) ? rotate_camera_with_shape(rt, GDK_KEY_KP_6) : 0;
	(rt->info->num_8) ? rotate_camera_with_shape(rt, GDK_KEY_KP_8) : 0;
	(rt->info->num_dec) ? rotate_camera_with_shape(rt, GDK_KEY_KP_Decimal) : 0;
}

static void	make_rotate_shape(t_rt *rt)
{
	ASSERT_SHAPE_VOID(rt->info->s_marker);
	(rt->info->i_key) ? rotate_shape(rt, GDK_KEY_i) : 0;
	(rt->info->j_key) ? rotate_shape(rt, GDK_KEY_j) : 0;
	(rt->info->k_key) ? rotate_shape(rt, GDK_KEY_k) : 0;
	(rt->info->l_key) ? rotate_shape(rt, GDK_KEY_l) : 0;
	(rt->info->u_key) ? rotate_shape(rt, GDK_KEY_u) : 0;
	(rt->info->o_key) ? rotate_shape(rt, GDK_KEY_o) : 0;
}

static void	make_mouse_action_on_camera_and_shape(t_rt *rt)
{
	if (rt->info->right_mc)
		rotate_camera_by_mouse_with_shape(rt);
	else if (rt->info->left_mc && rt->info->s_marker && rt->info->s_marker->dto)
		move_shape_by_mouse(rt,
			i2_sub(rt->info->lmc_current_pos, rt->info->lmc_start_pos));
	if (!rt->info->left_mc && rt->info->scroll_cnt &&
			rt->info->s_marker && rt->info->s_marker->dto)
		change_shape_param(rt);
}

void		make_action(t_rt *rt)
{
	restart_position(rt);
	make_move_camera_with_shape(rt);
	make_rotate_camera_with_shape(rt);
	make_mouse_action_on_camera_and_shape(rt);
	make_rotate_shape(rt);
	make_update_args(rt);
	g_idle_add(update_shape_widget, rt);
}
