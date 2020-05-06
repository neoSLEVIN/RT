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
	gtk->rt.buffer =
		(guchar*)malloc(sizeof(guchar) * gtk->rt.rows * gtk->rt.stride);
	if (!gtk->rt.buffer)
		ft_error("Can't allocate memory");
	ft_bzero(gtk->rt.buffer,
			 sizeof(guchar) * gtk->rt.rows * gtk->rt.stride);
	gtk->rt.pixbuf =
		gdk_pixbuf_new_from_data(gtk->rt.buffer, GDK_COLORSPACE_RGB, FALSE, 8,
								 gtk->rt.cols, gtk->rt.rows, gtk->rt.stride, free_pixels, NULL);
	gtk->rt.image = GTK_IMAGE(gtk_image_new_from_pixbuf(gtk->rt.pixbuf));
	gtk->rt.pixbuf = gtk_image_get_pixbuf(gtk->rt.image);
	gdk_pixbuf_fill(gtk->rt.pixbuf, 0);
	gtk->rt.buffer = gdk_pixbuf_get_pixels(gtk->rt.pixbuf);
	gtk->h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk->button = gtk_button_new_with_label("Update");
}
