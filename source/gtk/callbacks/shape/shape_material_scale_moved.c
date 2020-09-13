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

static gboolean	shape_material_scale_moved_safe(gpointer data)
{
	t_rt				*rt;
	struct s_material	*material;
	t_material_tab		*tab;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	material = &rt->gtk->ui.shape->shape->dto->material;
	tab = &rt->gtk->ui.shape->material;
	material->transparency =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->transparency.spin));
	material->refraction =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->refraction.spin));
	material->reflective =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->reflective.spin));
	material->specular =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->specular.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
	return (FALSE);
}

void			shape_material_scale_moved(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(shape_material_scale_moved_safe, data);
}
