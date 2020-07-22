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

void	gtk_set_textures_tree(t_gtk_textures *textures, const char *name,
							PPM_IMG *ppm)
{
	textures->expander = gtk_expander_new_with_mnemonic(name);
	textures->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(
		textures->scrolled_window), 200);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
		textures->scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	textures->store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	while (ppm)
	{
		gtk_tree_store_append(textures->store, &textures->iter, NULL);
		gtk_tree_store_set(textures->store, &textures->iter,
						   0, ppm->name,
						   1, ppm->path,
						   -1);
		ppm = ppm->next;
	}
	textures->tree =
		gtk_tree_view_new_with_model(GTK_TREE_MODEL(textures->store));
	gtk_widget_set_margin_bottom(GTK_WIDGET(textures->tree), 10);
	textures->renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(textures->tree),
		0, "Name", textures->renderer, "text", 0, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(textures->tree),
		1, "Path", textures->renderer, "text", 1, NULL);
}
