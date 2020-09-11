/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_shape_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:33 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	changing_shape_type_safe(gpointer data)
{
	t_rt	*rt;
	char	*type_name;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	type_name = get_shape_type_name(rt->gtk->ui.shape->shape->dto->type);
	gtk_tree_store_set(rt->gtk->ui.shapes.store,
		(GtkTreeIter*)rt->gtk->ui.shape->shape->tree_iter,
		S_TYPE_COL, type_name,
		-1);
	ft_strdel(&type_name);
	if (rt->gtk->ui.shape->shape->dto->type != TRIANGLE &&
			rt->gtk->ui.shape->shape->dto->type != OFF)
		do_change_shape_param(&rt->gtk->ui.shape->shape->dto->params,
							rt->gtk->ui.shape->shape->dto->transform.dots,
							rt->gtk->ui.shape->shape->dto->type, 0);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update_s_main = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}

void			changing_shape_type(GtkComboBox *type_combo, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
	rt->gtk->ui.shape->shape->dto->type =
			gtk_combo_box_get_active(type_combo) + 1;
	g_idle_add(changing_shape_type_safe, data);
}
