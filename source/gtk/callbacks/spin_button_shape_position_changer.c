/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_shape_position_changer.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 07:05:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 07:05:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	spin_button_shape_position_changer(GtkSpinButton *button, gpointer data)
{
	t_rt			*rt;
	FLT3			*position;
	t_transform_tab	*transform;

	(void)button;
	rt = (t_rt*)data;
	position = &rt->gtk->ui.shape->shape->dto->transform.position;
	transform = &rt->gtk->ui.shape->transform;
	position->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->x.spin));
	position->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->y.spin));
	position->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->z.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}
