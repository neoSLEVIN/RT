/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 16:57:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	free_pixels(guchar *pixels, gpointer data)
{
	free(pixels);
}

static void	gtk_set_image_dependencies(t_gtk *gtk, cl_char4 *dto_buffer)
{
	gtk->buffer = (unsigned char *)dto_buffer;
	gtk->pixbuf = gdk_pixbuf_new_from_data(gtk->buffer, GDK_COLORSPACE_RGB,
		TRUE, 8, COLS, ROWS, COLS * 4, free_pixels, NULL);
	gtk->image = GTK_IMAGE(gtk_image_new_from_pixbuf(gtk->pixbuf));
	gtk->pixbuf = gtk_image_get_pixbuf(gtk->image);
	gdk_pixbuf_fill(gtk->pixbuf, 0);
	gtk->buffer = gdk_pixbuf_get_pixels(gtk->pixbuf);
}

void		gtk_set_objects(t_gtk *gtk, cl_char4 *dto_buffer)
{
	gtk->h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk->image_event_box = gtk_event_box_new();
	gtk_set_image_dependencies(gtk, dto_buffer);
	gtk->button = gtk_button_new_with_label("Update");
}
