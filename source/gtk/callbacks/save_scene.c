/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:26:20 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:26:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	save_scene_as(GtkButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	if (get_new_file_name(&rt->info->scene_filename,
						&rt->info->scene_file_folder, "Untitled.json"))
	{
		g_idle_add(serialize_scene_to_json, rt);
		gtk_widget_set_tooltip_text(rt->gtk->ui.buttons.save_scene,
									rt->info->scene_filename);
	}
}

void	save_scene(GtkButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	if (rt->info->scene_filename)
		g_idle_add(serialize_scene_to_json, rt);
	else
		save_scene_as(button, data);
}
