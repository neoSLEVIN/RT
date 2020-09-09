/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tree_double_click.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:28:47 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 20:08:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	shapes_tree_double_click(GtkTreeView *tree, GtkTreePath *path,
								GtkTreeViewColumn *col, gpointer data)
{
	t_rt			*rt;
	GtkTreeIter		iter;
	gboolean		marker;
	struct s_shape	*shape;

	(void)tree;
	(void)col;
	rt = (t_rt*)data;
	if (gtk_tree_model_get_iter(rt->gtk->ui.shapes.model, &iter, path))
	{
		gtk_tree_model_get(rt->gtk->ui.shapes.model, &iter,
			S_MARKER_COL, &marker,
			S_POINTER_COL, &shape,
			-1);
		if (marker)
			clear_shape_marker(rt);
		else
			update_shape_marker(rt, shape);
		shape_to_true(rt->info);
		g_idle_add(update_shape_widget, rt);
		update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
						&rt->info->update_shapes);
	}
}
