/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:23:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 00:12:34 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	free_pixels(guchar *pixels, gpointer data)
{
	free(pixels);
}

void		gtk_set_objects(GTK_DATA *gtk)
{
	gtk->img.buffer =
		(guchar*)malloc(sizeof(guchar) * gtk->img.rows * gtk->img.stride);
	if (!gtk->img.buffer)
		ft_error("Can't allocate memory");
	ft_bzero(gtk->img.buffer,
		sizeof(guchar) * gtk->img.rows * gtk->img.stride);
	gtk->img.pixbuf =
		gdk_pixbuf_new_from_data(gtk->img.buffer, GDK_COLORSPACE_RGB, FALSE, 8,
			gtk->img.cols, gtk->img.rows, gtk->img.stride, free_pixels, NULL);
	gtk->img.image = GTK_IMAGE(gtk_image_new_from_pixbuf(gtk->img.pixbuf));
	gtk->img.pixbuf = gtk_image_get_pixbuf(gtk->img.image);
	gdk_pixbuf_fill(gtk->img.pixbuf, 0);
	gtk->img.buffer = gdk_pixbuf_get_pixels(gtk->img.pixbuf);
	gtk->h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk->button = gtk_button_new_with_label("Update");
}
