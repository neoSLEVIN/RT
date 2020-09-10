/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_shape_dot_c_changer.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:24:35 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:24:36 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_shape_dot_c_changer_safe(gpointer data)
{
	t_rt			*rt;
	FLT3			*dot_c;
	t_transform_tab	*transform;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	dot_c = &rt->gtk->ui.shape->shape->dto->transform.dots[2];
	transform = &rt->gtk->ui.shape->transform;
	dot_c->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->c[0].spin));
	dot_c->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->c[1].spin));
	dot_c->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->c[2].spin));
	compute_triangle_position(transform,
				&rt->gtk->ui.shape->shape->dto->transform.position,
				rt->gtk->ui.shape->shape->dto->transform.dots);
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (FALSE);
}

void			spin_button_shape_dot_c_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_shape_dot_c_changer_safe, data);
}
