/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tree_selection_changer.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:56:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:56:10 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	shapes_tree_selection_changer(GtkTreeSelection *selection,
									gpointer data)
{
	t_rt		*rt;
	GtkTreeIter	iter;
	gboolean	marker;
	SHAPE		*shape;

	rt = (t_rt*)data;
	if (gtk_tree_selection_get_selected(selection, &rt->gtk->ui.shapes.model,
		&iter))
	{
		gtk_tree_model_get(rt->gtk->ui.shapes.model, &iter,
			S_MARKER_COL, &marker,
			S_POINTER_COL, &shape,
			-1);
		rt->gtk->ui.shape->shape = shape;
		update_shape_widget(rt);
	}
}
