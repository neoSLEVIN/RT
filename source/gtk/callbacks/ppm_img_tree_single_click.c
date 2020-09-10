/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_img_tree_single_click.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:59 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean		texture_tree_single_click(GtkTreeView *tree,
										GdkEventButton *event, gpointer data)
{
	t_rt				*rt;
	GtkTreeViewColumn	*column;

	if (event->type == GDK_BUTTON_PRESS && event->button == 1)
	{
		rt = (t_rt*)data;
		if (!gtk_tree_view_get_path_at_pos(tree, event->x, event->y,
				&rt->gtk->ui.texture.path, &column, NULL, NULL))
			return (FALSE);
		if (column == gtk_tree_view_get_column(tree, PPM_DELETE_COL))
		{
			delete_texture(rt);
			return (TRUE);
		}
		gtk_tree_path_free(rt->gtk->ui.texture.path);
	}
	return (FALSE);
}

gboolean		normal_map_tree_single_click(GtkTreeView *tree,
										GdkEventButton *event, gpointer data)
{
	t_rt				*rt;
	GtkTreeViewColumn	*column;

	if (event->type == GDK_BUTTON_PRESS && event->button == 1)
	{
		rt = (t_rt*)data;
		if (!gtk_tree_view_get_path_at_pos(tree, event->x, event->y,
				&rt->gtk->ui.normals.path, &column, NULL, NULL))
			return (FALSE);
		if (column == gtk_tree_view_get_column(tree, PPM_DELETE_COL))
		{
			delete_normal_map(rt);
			return (TRUE);
		}
		gtk_tree_path_free(rt->gtk->ui.normals.path);
	}
	return (FALSE);
}
