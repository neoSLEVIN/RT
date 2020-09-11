/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_update_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:12 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	make_update_args(t_rt *rt)
{
	if (rt->info->update_cam)
	{
		update_cam_arg(rt->ocl, &rt->info->update_cam);
		g_idle_add(update_camera_widget, rt);
	}
	if (rt->info->update_shapes)
		update_shapes_arg(rt->ocl,
			&rt->info->update_s_cnt, &rt->info->update_shapes);
	if (rt->info->update_lights)
		update_lights_arg(rt->ocl,
			&rt->info->update_l_cnt, &rt->info->update_lights);
	if (rt->info->update_off_points)
		update_off_points_arg(rt->ocl, &rt->info->update_off_points);
}
