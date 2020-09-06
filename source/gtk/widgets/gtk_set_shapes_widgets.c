/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shapes_widgets.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 05:47:30 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 05:47:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_insert_columns_in_shape_tree(t_gtk_shapes *shapes)
{
	shapes->text_renderer = gtk_cell_renderer_text_new();
	shapes->toggle_renderer = gtk_cell_renderer_toggle_new();
	shapes->pixbuf_renderer = gtk_cell_renderer_pixbuf_new();
	g_object_set(shapes->pixbuf_renderer, "icon-name", "window-close", NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(shapes->tree),
		S_NAME_COL, "Name", shapes->text_renderer, "text", S_NAME_COL, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(shapes->tree),
		S_TYPE_COL, "Type", shapes->text_renderer, "text", S_TYPE_COL, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(shapes->tree),
		S_MARKER_COL, "Marked", shapes->toggle_renderer,
		"active", S_MARKER_COL, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(shapes->tree),
		S_DELETE_COL, "Delete", shapes->pixbuf_renderer,
		NULL);
}

static void	gtk_insert_rows_in_shape_tree(SHAPE *shape, t_gtk_shapes *shapes)
{
	char	*type_name;

	while (shape)
	{
		gtk_tree_store_append(shapes->store, &shapes->iter, NULL);
		if (!(shape->tree_iter = (void*)gtk_tree_iter_copy(&shapes->iter)))
			ft_error("Can't allocate memory");
		type_name = get_shape_type_name(shape->dto->type);
		gtk_tree_store_set(shapes->store, &shapes->iter,
			S_NAME_COL, shape->name,
			S_TYPE_COL, type_name,
			S_MARKER_COL, shape->dto->marker,
			S_POINTER_COL, shape,
			-1);
		ft_strdel(&type_name);
		shape = shape->next;
	}
}

void		gtk_set_shapes_tree(t_gtk_shapes *shapes, t_rt *rt)
{
	shapes->expander = gtk_expander_new_with_mnemonic("Sh_apes");
	shapes->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(
		shapes->scrolled_window), 200);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(shapes->scrolled_window),
		GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	shapes->store = gtk_tree_store_new(S_COL_CNT,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN,
		G_TYPE_POINTER);
	shapes->model = GTK_TREE_MODEL(shapes->store);
	gtk_insert_rows_in_shape_tree(rt->scene->shapes, shapes);
	shapes->tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(shapes->store));
	gtk_widget_set_margin_bottom(GTK_WIDGET(shapes->tree), 10);
	gtk_insert_columns_in_shape_tree(shapes);
	shapes->select = gtk_tree_view_get_selection(GTK_TREE_VIEW(shapes->tree));
	gtk_tree_selection_set_mode(shapes->select, GTK_SELECTION_SINGLE);
	shapes->path = NULL;
}
