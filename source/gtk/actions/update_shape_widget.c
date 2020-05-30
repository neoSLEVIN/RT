/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shape_widget.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:58:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 07:03:03 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_gtk_shape_pos(t_transform_tab tab, FLT3 shape_pos)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.spin_x), shape_pos.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.spin_y), shape_pos.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.spin_z), shape_pos.z);
}

void	update_shape_widget(t_rt *rt)
{
	t_gtk_shape	*shape;

	shape = rt->gtk->ui.shape;
	//TODO do not update if closed expander
	update_gtk_shape_pos(shape->transform,
						shape->shape->dto->transform.position);
}
