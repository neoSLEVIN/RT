/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_textures_normals.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:36 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	changing_texture_type(GtkComboBox *texture_combo, gpointer data)
{
	t_rt	*rt;
	gint	index;

	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
	if ((index = gtk_combo_box_get_active(texture_combo)) == -1)
		return ;
	rt->gtk->ui.shape->shape->dto->texture.id = index - 5;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
}

void	changing_normals_type(GtkComboBox *normals_combo, gpointer data)
{
	t_rt	*rt;
	gint	index;

	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
	if ((index = gtk_combo_box_get_active(normals_combo)) == -1)
		return ;
	rt->gtk->ui.shape->shape->dto->normal_map.id = index - 1;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
}
