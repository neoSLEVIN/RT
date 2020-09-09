/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scale_moved.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:22 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	display_width_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->cam.display.x = gtk_range_get_value(range);
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov,
				rt->scene->cam.display);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
}

void	display_height_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->cam.display.y = gtk_range_get_value(range);
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov,
				rt->scene->cam.display);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
}
