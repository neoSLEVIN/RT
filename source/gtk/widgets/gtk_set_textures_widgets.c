/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_textures_widgets.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:22:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/24 18:36:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_textures_loop(t_gtk_textures *textures, PPM_IMG *ppm)
{
	while (ppm)
	{
		gtk_tree_store_append(textures->store, &textures->iter, NULL);
		gtk_tree_store_set(textures->store, &textures->iter,
						PPM_NAME_COL, ppm->name,
						PPM_PATH_COL, ppm->path,
						PPM_POINTER_COL, ppm,
						-1);
		ppm = ppm->next;
	}
}

static void	gtk_insert_columns_in_textures_tree(t_gtk_textures *textures)
{
	textures->renderer = gtk_cell_renderer_text_new();
	textures->pixbuf_renderer = gtk_cell_renderer_pixbuf_new();
	g_object_set(textures->pixbuf_renderer, "icon-name", "window-close", NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(textures->tree),
		PPM_NAME_COL, "Name", textures->renderer, "text", PPM_NAME_COL, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(textures->tree),
		PPM_PATH_COL, "Path", textures->renderer, "text", PPM_PATH_COL, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(textures->tree),
		PPM_DELETE_COL, "Delete", textures->pixbuf_renderer, NULL);
}

void		gtk_set_textures_tree(t_gtk_textures *textures, const char *name,
							PPM_IMG *ppm)
{
	textures->expander = gtk_expander_new_with_mnemonic(name);
	textures->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(
		textures->scrolled_window), 110);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
		textures->scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	textures->store = gtk_tree_store_new(PPM_COL_CNT,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER);
	textures->model = GTK_TREE_MODEL(textures->store);
	gtk_set_textures_loop(textures, ppm);
	textures->tree =
		gtk_tree_view_new_with_model(GTK_TREE_MODEL(textures->store));
	gtk_widget_set_margin_bottom(GTK_WIDGET(textures->tree), 10);
	gtk_insert_columns_in_textures_tree(textures);
	textures->path = NULL;
}
