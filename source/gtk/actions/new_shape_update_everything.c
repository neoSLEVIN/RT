/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shape_update_everything.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:24 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void		new_shape_update_everything(t_rt *rt, t_gtk_shapes *gtk_shapes,
										SHAPE *shape)
{
	GtkTreePath	*path;
	char		*type;

	gtk_tree_store_append(gtk_shapes->store, &gtk_shapes->iter, NULL);
	if (!(shape->tree_iter = (void*)gtk_tree_iter_copy(&gtk_shapes->iter)))
		ft_error("Can't allocate memory");
	type = get_shape_type_name(shape->dto->type);
	gtk_tree_store_set(gtk_shapes->store, &gtk_shapes->iter, S_NAME_COL,
		shape->name, S_TYPE_COL, type, S_MARKER_COL, shape->dto->marker,
		S_POINTER_COL, shape, -1);
	ft_strdel(&type);
	if (!(path = gtk_tree_model_get_path(gtk_shapes->model, shape->tree_iter)))
		ft_error("Can't allocate memory");
	gtk_tree_selection_select_path(gtk_shapes->select, path);
	gtk_tree_path_free(path);
	realloc_shapes_dto(&rt->ocl->dto.shapes, rt->scene->shapes,
					++rt->scene->s_cnt);
	update_shape_marker(rt, shape);
	update_flags(&rt->info->update_shapes, &rt->info->update_s_cnt);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
	rt->gtk->ui.shape->shape = shape;
	shape_to_true(rt->info);
	g_idle_add(update_shape_widget, rt);
}
