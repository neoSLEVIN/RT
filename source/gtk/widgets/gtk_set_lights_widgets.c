/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_lights_widgets.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:35 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:35 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_insert_columns_in_light_tree(t_gtk_lights *lights)
{
	lights->text_renderer = gtk_cell_renderer_text_new();
	lights->pixbuf_renderer = gtk_cell_renderer_pixbuf_new();
	g_object_set(lights->pixbuf_renderer, "icon-name", "window-close", NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(lights->tree),
		LIGHT_NAME_COL, "Name", lights->text_renderer,
		"text", LIGHT_NAME_COL, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(lights->tree),
		LIGHT_TYPE_COL, "Type", lights->text_renderer,
		"text", LIGHT_TYPE_COL, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(lights->tree),
		LIGHT_DELETE_COL, "Delete", lights->pixbuf_renderer, NULL);
}

static void	gtk_insert_rows_in_light_tree(LIGHT *light, t_gtk_lights *lights)
{
	char	*type_name;

	while (light)
	{
		gtk_tree_store_append(lights->store, &lights->iter, NULL);
		if (!(light->tree_iter = (void*)gtk_tree_iter_copy(&lights->iter)))
			ft_error("Can't allocate memory");
		type_name = get_light_type_name(light->dto->type);
		gtk_tree_store_set(lights->store, &lights->iter,
			LIGHT_NAME_COL, light->name,
			LIGHT_TYPE_COL, type_name,
			LIGHT_POINTER_COL, light,
			-1);
		ft_strdel(&type_name);
		light = light->next;
	}
}

void		gtk_set_lights_tree(t_gtk_lights *lights, t_rt *rt)
{
	lights->expander = gtk_expander_new_with_mnemonic("L_ights");
	lights->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(
		lights->scrolled_window), 150);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(lights->scrolled_window),
		GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	lights->store = gtk_tree_store_new(LIGHT_COL_CNT,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER);
	lights->model = GTK_TREE_MODEL(lights->store);
	gtk_insert_rows_in_light_tree(rt->scene->lights, lights);
	lights->tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(lights->store));
	gtk_widget_set_margin_bottom(GTK_WIDGET(lights->tree), 10);
	gtk_insert_columns_in_light_tree(lights);
	lights->select = gtk_tree_view_get_selection(GTK_TREE_VIEW(lights->tree));
	gtk_tree_selection_set_mode(lights->select, GTK_SELECTION_SINGLE);
	lights->path = NULL;
}
