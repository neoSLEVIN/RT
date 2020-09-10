/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_sections_tab_tree_widgets.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:08 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_tree_view_insert_section_type_column(t_section_tab *section)
{
	GtkTreeIter	iter;

	section->type_store = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_list_store_append(section->type_store, &iter);
	gtk_list_store_set(section->type_store, &iter, 0, "PLANE", -1);
	gtk_list_store_append(section->type_store, &iter);
	gtk_list_store_set(section->type_store, &iter, 0, "SPHERE", -1);
	g_object_set(section->combo_renderer, "model", section->type_store,
		"text-column", 0, "has-entry", FALSE, "editable", TRUE, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(section->tree),
		SEC_TYPE_COL, "Type", section->combo_renderer,
		"text", SEC_TYPE_COL, NULL);
}

static void	gtk_insert_columns_in_sections_tree(t_section_tab *section)
{
	section->toggle_on_renderer = gtk_cell_renderer_toggle_new();
	section->combo_renderer = gtk_cell_renderer_combo_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(section->tree),
		SEC_ON_COL, "On/Off", section->toggle_on_renderer,
		"active", SEC_ON_COL, NULL);
	gtk_tree_view_insert_section_type_column(section);
}

static void	gtk_insert_rows_in_sections_tree(t_section_tab *section_tab,
												SECTION *shape_sections)
{
	SECTION	*section;
	int		i;

	i = -1;
	while (++i < SECTION_CNT)
	{
		section = &shape_sections[i];
		gtk_tree_store_append(section_tab->store, &section_tab->iter[i], NULL);
		gtk_tree_store_set(section_tab->store, &section_tab->iter[i],
			SEC_ON_COL, section->on,
			SEC_TYPE_COL, (section->type == PLANE) ? "PLANE" : "SPHERE",
			SEC_POINTER_COL, section,
			-1);
	}
}

void		gtk_set_sections_tab_tree_widgets(t_section_tab *tab,
												SECTION *shape_sections)
{
	tab->store = gtk_tree_store_new(SEC_COL_CNT,
		G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_POINTER);
	tab->model = GTK_TREE_MODEL(tab->store);
	gtk_insert_rows_in_sections_tree(tab, shape_sections);
	tab->tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(tab->store));
	gtk_widget_set_margin_bottom(GTK_WIDGET(tab->tree), 10);
	gtk_insert_columns_in_sections_tree(tab);
	tab->select = gtk_tree_view_get_selection(GTK_TREE_VIEW(tab->tree));
	gtk_tree_selection_set_mode(tab->select, GTK_SELECTION_SINGLE);
}
