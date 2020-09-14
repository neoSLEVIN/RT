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
	char	*filename;

	(void)button;
	rt = (t_rt*)data;
	filename = NULL;
	if (save_file_name(GTK_WINDOW(rt->gtk->window), &filename,
						IMAGES_PATH, "Untitled.png"))
	{
		(rt->info->image_filename) ? ft_strdel(&rt->info->image_filename) : 0;
		rt->info->image_filename = filename;
		gdk_pixbuf_save(rt->gtk->img.pixbuf, rt->info->image_filename, "png",
						NULL, NULL);
		gtk_widget_set_tooltip_text(rt->gtk->ui.buttons.save_image,
									rt->info->image_filename);
	}
	else
		(filename) ? ft_strdel(&filename) : 0;
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
