/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_with_shape.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 07:24:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 07:24:03 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	move_camera_with_shape(t_rt *rt, guint key)
{
	if (rt->info->left_mc && rt->info->s_marker && rt->info->s_marker->dto)
		move_shape_by_camera_movement(rt, key);
	move_camera(rt, key);
}

void	rotate_camera_with_shape(t_rt *rt, guint key)
{
	if (rt->info->left_mc && rt->info->s_marker && rt->info->s_marker->dto)
		move_shape_by_camera_rotating(rt, key);
	rotate_camera(rt, key);
}

void	rotate_camera_by_mouse_with_shape(t_rt *rt)
{
	INT2	diff;

	diff = i2_sub(rt->info->rmc_current_pos, rt->info->rmc_start_pos);
	if (rt->info->left_mc && rt->info->s_marker && rt->info->s_marker->dto)
	{
		move_shape_by_mouse(rt, diff);
		rt->info->lmc_current_pos = rt->info->rmc_current_pos;
	}
	rotate_camera_by_mouse(rt, diff);
}
