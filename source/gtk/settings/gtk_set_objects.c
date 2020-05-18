/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 21:46:11 by cschoen          ###   ########.fr       */
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

void		gtk_set_objects(t_gtk *gtk, t_rt *rt)
{
	gtk->h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk->image_event_box = gtk_event_box_new();
	gtk_widget_set_events(gtk->image_event_box, GDK_SCROLL_MASK);
	gtk_set_image_dependencies(gtk, rt->ocl->dto.buffer);
	gtk->ui_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER(gtk->ui_v_box), 5);
	gtk->fps_h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk->fps_label = gtk_label_new("FPS: ");
	gtk->fps_adj = gtk_adjustment_new(rt->scene->fps, 0.5, 80.0, 0.5, 1.0, 0);
	gtk->fps_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, gtk->fps_adj);
	gtk_scale_set_digits(GTK_SCALE(gtk->fps_scale), 1);
	gtk_widget_set_hexpand(gtk->fps_scale, TRUE);
	gtk_widget_set_valign(gtk->fps_scale, GTK_ALIGN_START);
	gtk->y_axis = gtk_check_button_new_with_label("Invert Y-axis");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk->y_axis), FALSE);
	gtk->x_axis = gtk_check_button_new_with_label("Invert X-axis");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk->x_axis), FALSE);
	gtk->button = gtk_button_new_with_label("Update");
}
