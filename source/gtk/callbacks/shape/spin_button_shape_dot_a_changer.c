/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_shape_dot_a_changer.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:24:26 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:24:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void			compute_triangle_position(t_transform_tab *tab,
											FLT3 *pos, FLT3 *dots)
{
	*pos = v3_scale(v3_add(v3_add(dots[0], dots[1]), dots[2]), 1.0f / 3.0f);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->x.spin), pos->x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->y.spin), pos->y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->z.spin), pos->z);
}

static gboolean	spin_button_shape_dot_a_changer_safe(gpointer data)
{
	t_rt			*rt;
	FLT3			*dot_a;
	t_transform_tab	*transform;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	dot_a = &rt->gtk->ui.shape->shape->dto->transform.dots[0];
	transform = &rt->gtk->ui.shape->transform;
	dot_a->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->a[0].spin));
	dot_a->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->a[1].spin));
	dot_a->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->a[2].spin));
	compute_triangle_position(transform,
		&rt->gtk->ui.shape->shape->dto->transform.position,
		rt->gtk->ui.shape->shape->dto->transform.dots);
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (FALSE);
}

void			spin_button_shape_dot_a_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_shape_dot_a_changer_safe, data);
}
