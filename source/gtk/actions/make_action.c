/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:12:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 07:48:57 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	move_shape(t_rt *rt, INT2 diff)
{

}

void	make_action(t_rt *rt)
{
	if (rt->info->space_key)
		move_cam(rt, GDK_KEY_space);
	if (rt->info->c_key)
		move_cam(rt, GDK_KEY_c);
	if (rt->info->w_key)
		move_cam(rt, GDK_KEY_w);
	if (rt->info->s_key)
		move_cam(rt, GDK_KEY_s);
	if (rt->info->a_key)
		move_cam(rt, GDK_KEY_a);
	if (rt->info->d_key)
		move_cam(rt, GDK_KEY_d);
	if (rt->info->q_key)
		rotate_cam(rt, GDK_KEY_q);
	if (rt->info->e_key)
		rotate_cam(rt, GDK_KEY_e);
	if (rt->info->num_2)
		rotate_cam(rt, GDK_KEY_KP_2);
	if (rt->info->num_4)
		rotate_cam(rt, GDK_KEY_KP_4);
	if (rt->info->num_6)
		rotate_cam(rt, GDK_KEY_KP_6);
	if (rt->info->num_8)
		rotate_cam(rt, GDK_KEY_KP_8);
	if (rt->info->num_decimal)
		rotate_cam(rt, GDK_KEY_KP_Decimal);
	if (rt->info->right_mc)
		rotate_cam_by_mouse(rt,
			i2_sub(rt->info->rmc_current_pos, rt->info->rmc_start_pos));
	if (rt->info->scroll_mc)
		rotate_cam_by_mouse(rt, (INT2){0, 0});
	if (rt->info->left_mc && rt->info->s_marker != NULL)
		move_shape(rt,
			i2_sub(rt->info->lmc_current_pos, rt->info->lmc_start_pos));
}
