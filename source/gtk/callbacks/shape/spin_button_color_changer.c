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
	color->x = GTK_CHANGER_GET_VALUE(tab->red.change);
	color->y = GTK_CHANGER_GET_VALUE(tab->green.change);
	color->z = GTK_CHANGER_GET_VALUE(tab->blue.change);
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (FALSE);
}

void			spin_button_color_changer(GtkWidget *button, gpointer data)
{
	(void)button;
	g_idle_add(spin_button_color_changer_safe, data);
}
