/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 06:17:02 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	free_pixels(guchar *pixels, gpointer data)
{
	(void)data;
	free(pixels);
}

static void	gtk_set_image_with_dependencies(t_gtk *gtk, cl_char4 *dto_buffer)
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

void		gtk_set_settings_objects(t_gtk_settings *settings, t_rt *rt)
{
	GtkAdjustment	*fps_adj;

	settings->expander = gtk_expander_new_with_mnemonic("_Settings");
	settings->grid = gtk_grid_new();
	settings->fps_label = gtk_label_new("FPS:");
	gtk_widget_set_hexpand(settings->fps_label, FALSE);
	fps_adj = gtk_adjustment_new(rt->scene->fps, 0.5, 80.0, 0.5,1.0, 0);
	settings->fps_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, fps_adj);
	gtk_scale_set_digits(GTK_SCALE(settings->fps_scale), 1);
	gtk_widget_set_hexpand(settings->fps_scale, TRUE);
	settings->y_axis = gtk_check_button_new_with_label("Invert Y-axis");
	gtk_widget_set_halign(settings->y_axis, GTK_ALIGN_CENTER);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(settings->y_axis), FALSE);
	settings->separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_widget_set_valign(settings->separator, GTK_ALIGN_FILL);
	gtk_widget_set_halign(settings->separator, GTK_ALIGN_CENTER);
	settings->x_axis = gtk_check_button_new_with_label("Invert X-axis");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(settings->x_axis), FALSE);
}

static void	gtk_set_texture_tree(t_texture_tree *tree, t_rt *rt)
{
	TEXTURE	*temp;

	temp = rt->scene->textures;

	tree->expander = gtk_expander_new_with_mnemonic("_Textures");
	tree->store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	while (temp)
	{
		gtk_tree_store_append(tree->store, &tree->iter, NULL);
		gtk_tree_store_set(tree->store, &tree->iter,
						0, temp->name,
						1, temp->path,
						-1);
		temp = temp->next;
	}
	tree->view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(tree->store));
	tree->renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree->view),
												0,
												"Name", tree->renderer,
												"text", 0,
												NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree->view),
												1,
												"Path", tree->renderer,
												"text", 1,
												NULL);
}

void		gtk_set_objects(t_gtk *gtk, t_rt *rt)
{
	gtk->window_h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_image_with_dependencies(gtk, rt->ocl->dto.buffer);
	gtk->ui.grid = gtk_grid_new();
	gtk_set_texture_tree(&gtk->ui.texture, rt);
	gtk_set_settings_objects(&gtk->ui.settings, rt);
	gtk->button = gtk_button_new_with_label("Update");
}
