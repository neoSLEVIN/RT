/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_color_changer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:44:50 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/13 14:44:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_color_changer_safe(gpointer data)
{
	t_rt			*rt;
	FLT3			*color;
	t_color_tab		*tab;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	color = &rt->gtk->ui.shape->shape->dto->material.color;
	tab = &rt->gtk->ui.shape->color;
	color->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->red.spin));
	color->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->green.spin));
	color->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->blue.spin));
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (FALSE);
}

void			spin_button_color_changer(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(spin_button_color_changer_safe, data);
}
