/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:12:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 02:12:41 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	make_action(t_rt *rt)
{
	if (rt->info->w_key)
		move_cam(rt, 'w');
	if (rt->info->s_key)
		move_cam(rt, 's');
	if (rt->info->a_key)
		move_cam(rt, 'a');
	if (rt->info->d_key)
		move_cam(rt, 'd');
	if (rt->info->q_key)
		move_cam(rt, 'q');
	if (rt->info->e_key)
		move_cam(rt, 'e');
	if (rt->info->num_2)
		rotate_cam(rt, GDK_KEY_KP_2);
	if (rt->info->num_4)
		rotate_cam(rt, GDK_KEY_KP_4);
	if (rt->info->num_6)
		rotate_cam(rt, GDK_KEY_KP_6);
	if (rt->info->num_8)
		rotate_cam(rt, GDK_KEY_KP_8);
}
