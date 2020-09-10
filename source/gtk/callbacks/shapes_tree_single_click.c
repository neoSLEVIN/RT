/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tree_single_click.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:26:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:26:33 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void		free_shape_data(SHAPE *shape, t_rt *rt)
{
	gtk_tree_iter_free(shape->tree_iter);
	if (rt->gtk->ui.shape->shape == shape)
	{
		rt->gtk->ui.shape->shape = NULL;
		gtk_expander_set_expanded(GTK_EXPANDER(rt->gtk->ui.shape->expander),
									FALSE);
	}
	(shape->name) ? ft_strdel(&shape->name) : 0;
	(shape->texture_name) ? ft_strdel(&shape->texture_name) : 0;
	(shape->normal_map_name) ? ft_strdel(&shape->normal_map_name) : 0;
	(rt->info->s_marker == shape) ? (rt->info->s_marker = NULL) : 0;
	(rt->scene->shapes == shape) ? (rt->scene->shapes = shape->next) : 0;
	(shape->prev) ? (shape->prev->next = shape->next) : 0;
	(shape->next) ? (shape->next->prev = shape->prev) : 0;
}

static gboolean	delete_shape(gpointer data)
{
	t_rt		*rt;
	GtkTreeIter	iter;
	gboolean	marker;
	SHAPE		*shape;

	rt = (t_rt*)data;
	if (gtk_tree_model_get_iter(rt->gtk->ui.shapes.model, &iter,
								rt->gtk->ui.shapes.path))
	{
		gtk_tree_model_get(rt->gtk->ui.shapes.model, &iter,
			S_MARKER_COL, &marker, S_POINTER_COL, &shape, -1);
		gtk_tree_store_remove(rt->gtk->ui.shapes.store, &iter);
		free_shape_data(shape, rt);
		ft_memdel((void**)&shape);
		realloc_shapes_dto(&rt->ocl->dto.shapes, rt->scene->shapes,
							--rt->scene->s_cnt);
		update_flags(&rt->info->update_shapes, &rt->info->update_s_cnt);
		update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
							&rt->info->update_shapes);
		rt->info->update = TRUE;
	}
	gtk_tree_path_free(rt->gtk->ui.shapes.path);
	return (FALSE);
}

gboolean		shapes_tree_single_click(GtkTreeView *tree,
										GdkEventButton *event, gpointer data)
{
	t_rt				*rt;
	GtkTreeViewColumn	*column;

	if (event->type == GDK_BUTTON_PRESS && event->button == 1)
	{
		rt = (t_rt*)data;
		if (!gtk_tree_view_get_path_at_pos(tree, event->x, event->y,
				&rt->gtk->ui.shapes.path, &column, NULL, NULL))
			return (FALSE);
		if (column == gtk_tree_view_get_column(tree, S_MARKER_COL))
		{
			shapes_tree_double_click(tree, rt->gtk->ui.shapes.path, column, rt);
			gtk_tree_path_free(rt->gtk->ui.shapes.path);
			return (TRUE);
		}
		if (column == gtk_tree_view_get_column(tree, S_DELETE_COL))
		{
			delete_shape(data);
			return (TRUE);
		}
		gtk_tree_path_free(rt->gtk->ui.shapes.path);
	}
	return (FALSE);
}
