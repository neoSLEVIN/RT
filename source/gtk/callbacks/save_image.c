/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:26:07 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:26:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	save_image_as(GtkButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	if (get_new_file_name(&rt->info->image_filename,
						&rt->info->image_file_folder, "Untitled.png"))
	{
		gdk_pixbuf_save(rt->gtk->img.pixbuf, rt->info->image_filename, "png",
						NULL, NULL);
		gtk_widget_set_tooltip_text(rt->gtk->ui.buttons.save_image,
									rt->info->image_filename);
	}
}

void	save_image(GtkButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	if (rt->info->image_filename)
		gdk_pixbuf_save(rt->gtk->img.pixbuf, rt->info->image_filename, "png",
						NULL, NULL);
	else
		save_image_as(button, data);
}
