/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_material_scale_moved.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:56 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:56 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	shape_material_scale_moved(GtkRange *range, gpointer data)
{
	t_rt				*rt;
	struct s_material	*material;
	t_material_tab		*material_tab;

	(void)range;
	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
	material = &rt->gtk->ui.shape->shape->dto->material;
	material_tab = &rt->gtk->ui.shape->material;
	material->transparency =
		gtk_range_get_value(GTK_RANGE(material_tab->transparency.scale));
	material->reflective =
		gtk_range_get_value(GTK_RANGE(material_tab->reflective.scale));
	material->specular =
		gtk_range_get_value(GTK_RANGE(material_tab->specular.scale));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}
