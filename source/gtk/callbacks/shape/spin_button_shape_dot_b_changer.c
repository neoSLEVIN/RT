/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_shape_dot_b_changer.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:24:32 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:24:32 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_shape_dot_b_changer_safe(gpointer data)
{
	t_rt			*rt;
	FLT3			*dot_b;
	t_transform_tab	*transform;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	dot_b = &rt->gtk->ui.shape->shape->dto->transform.dots[1];
	transform = &rt->gtk->ui.shape->transform;
	dot_b->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->b[0].spin));
	dot_b->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->b[1].spin));
	dot_b->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->b[2].spin));
	compute_triangle_position(transform,
				&rt->gtk->ui.shape->shape->dto->transform.position,
				rt->gtk->ui.shape->shape->dto->transform.dots);
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (FALSE);
}

void			spin_button_shape_dot_b_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_shape_dot_b_changer_safe, data);
}
