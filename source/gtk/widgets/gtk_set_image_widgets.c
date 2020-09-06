/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_image_widgets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:10:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	free_pixels(guchar *pixels, gpointer data)
{
	(void)data;
	free(pixels);
}

void		gtk_set_image_with_dependencies(t_gtk *gtk, cl_uchar4 *dto_buffer)
{
	gtk->img.image_event_box = gtk_event_box_new();
	gtk_widget_set_events(gtk->img.image_event_box, GDK_SCROLL_MASK);
	gtk->img.buffer = (unsigned char *)dto_buffer;
	gtk->img.pixbuf = gdk_pixbuf_new_from_data(gtk->img.buffer,
		GDK_COLORSPACE_RGB, TRUE, 8, COLS, ROWS, COLS * 4, free_pixels, NULL);
	gtk->img.image = GTK_IMAGE(gtk_image_new_from_pixbuf(gtk->img.pixbuf));
	gtk->img.pixbuf = gtk_image_get_pixbuf(gtk->img.image);
	gdk_pixbuf_fill(gtk->img.pixbuf, 0);
	gtk->img.buffer = gdk_pixbuf_get_pixels(gtk->img.pixbuf);
}
