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
	char	*filename;

	(void)button;
	rt = (t_rt*)data;
	filename = NULL;
	if (save_file_name(GTK_WINDOW(rt->gtk->window), &filename,
						SCENE_PATH, "Untitled.json"))
	{
		(rt->info->scene_filename) ? ft_strdel(&rt->info->scene_filename) : 0;
		rt->info->scene_filename = filename;
		g_idle_add(serialize_scene_to_json, rt);
		gtk_widget_set_tooltip_text(rt->gtk->ui.buttons.save_scene,
									rt->info->scene_filename);
	}
	else
		(filename) ? ft_strdel(&filename) : 0;
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
