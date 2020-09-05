/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_marker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 07:52:50 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 05:38:33 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	set_focus_on_marked_shape(t_gtk_shapes *shapes,
										GtkTreeIter *shape_iter)
{
	GtkTreePath	*path;

	if (!(path = gtk_tree_model_get_path(shapes->model, shape_iter)))
		ft_error("Can't allocate memory");
	gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(shapes->tree),
			path, NULL, FALSE, 0, 0);
	gtk_tree_path_free(path);
}

void		update_shape_marker(t_rt *rt, SHAPE *shape)
{
	if (rt->info->s_marker && rt->info->s_marker->dto)
	{
		rt->info->s_marker->dto->marker = FALSE;
		gtk_tree_store_set(rt->gtk->ui.shapes.store,
			(GtkTreeIter*)rt->info->s_marker->tree_iter,
			S_MARKER_COL, FALSE,
			-1);
	}
	rt->info->s_marker = shape;
	if (shape && shape->dto)
	{
		shape->dto->marker = TRUE;
		set_focus_on_marked_shape(&rt->gtk->ui.shapes,
			(GtkTreeIter*)shape->tree_iter);
		gtk_tree_store_set(rt->gtk->ui.shapes.store,
			(GtkTreeIter*)shape->tree_iter,
			S_MARKER_COL, TRUE,
			-1);
	}
}

void		clear_shape_marker(t_rt *rt)
{
	rt->info->scroll_cnt = 0;
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->i_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->j_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->k_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->l_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->u_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->o_key);
	if (rt->info->s_marker && rt->info->s_marker->dto)
	{
		rt->info->s_marker->dto->marker = FALSE;
		gtk_tree_store_set(rt->gtk->ui.shapes.store,
			(GtkTreeIter*)rt->info->s_marker->tree_iter,
			S_MARKER_COL, FALSE,
			-1);
	}
	rt->info->s_marker = NULL;
}
