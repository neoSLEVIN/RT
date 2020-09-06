/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_texture_tab_widgets.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:15 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:15 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_texture_list(GtkComboBoxText *filter_combo,
								PPM_IMG *textures)
{
	gtk_combo_box_text_append_text(filter_combo, "Lines");
	gtk_combo_box_text_append_text(filter_combo, "Checker");
	gtk_combo_box_text_append_text(filter_combo, "Noise");
	gtk_combo_box_text_append_text(filter_combo, "Wood");
	gtk_combo_box_text_append_text(filter_combo, "NO TEXTURES");
	while (textures)
	{
		gtk_combo_box_text_append_text(filter_combo, textures->name);
		textures = textures->next;
	}
}

static void	gtk_set_normals_list(GtkComboBoxText *filter_combo,
								PPM_IMG *normals)
{
	gtk_combo_box_text_append_text(filter_combo, "NO NORMALS");
	while (normals)
	{
		gtk_combo_box_text_append_text(filter_combo, normals->name);
		normals = normals->next;
	}
}

void		gtk_set_texture_tab_widgets(t_texture_tab *texture_tab,
										PPM_IMG *textures, PPM_IMG *normals)
{
	texture_tab->label = gtk_label_new("Texture");
	texture_tab->grid = gtk_grid_new();
	texture_tab->texture_label = gtk_label_new("Texture:");
	texture_tab->normals_label = gtk_label_new("Normal map:");
	texture_tab->texture_combo = gtk_combo_box_text_new();
	texture_tab->normals_combo = gtk_combo_box_text_new();
	gtk_widget_set_margin_start(texture_tab->texture_label, 5);
	gtk_widget_set_margin_start(texture_tab->normals_label, 5);
	gtk_widget_set_margin_top(texture_tab->texture_label, 5);
	gtk_widget_set_margin_top(texture_tab->texture_combo, 5);
	gtk_widget_set_margin_top(texture_tab->normals_label, 5);
	gtk_widget_set_margin_top(texture_tab->normals_combo, 5);
	gtk_widget_set_margin_end(texture_tab->normals_label, 5);
	gtk_widget_set_margin_end(texture_tab->texture_label, 5);
	gtk_set_texture_list(GTK_COMBO_BOX_TEXT(texture_tab->texture_combo),
						textures);
	gtk_set_normals_list(GTK_COMBO_BOX_TEXT(texture_tab->normals_combo),
						normals);
	gtk_combo_box_set_active(GTK_COMBO_BOX(texture_tab->texture_combo), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(texture_tab->normals_combo), 0);
}
