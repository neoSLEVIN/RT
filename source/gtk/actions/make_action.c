/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:12:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 08:48:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

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
}
