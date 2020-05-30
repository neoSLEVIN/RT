/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_widgets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:03:47 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:09:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_transform_tab_widgets(t_transform_tab *transform_tab,
										TRANSFORM *shape_transform)
{
	transform_tab->label = gtk_label_new("Transform");
	transform_tab->grid = gtk_grid_new();
	transform_tab->label_pos = gtk_label_new("Position:");
	gtk_widget_set_margin_top(transform_tab->label_pos, 5);
	gtk_widget_set_margin_bottom(transform_tab->label_pos, 5);
	transform_tab->label_x = gtk_label_new("X:");
	gtk_widget_set_margin_start(transform_tab->label_x, 5);
	gtk_widget_set_margin_end(transform_tab->label_x, 5);
	gtk_set_spin_button_for_float(&transform_tab->spin_x,
							shape_transform->position.x);
	transform_tab->label_y = gtk_label_new("Y:");
	gtk_set_spin_button_for_float(&transform_tab->spin_y,
							shape_transform->position.y);
	transform_tab->label_z = gtk_label_new("Z:");
	gtk_set_spin_button_for_float(&transform_tab->spin_z,
							shape_transform->position.z);
}

void		gtk_set_shape_widgets(t_gtk_shape **gtk_shape, SHAPE *scene_shape)
{
	if ((*gtk_shape = (t_gtk_shape*)malloc(sizeof(t_gtk_shape))) == NULL)
		ft_error("Can't allocate memory");
	(*gtk_shape)->shape = scene_shape;
	(*gtk_shape)->expander = gtk_expander_new_with_mnemonic("_Shape");
	(*gtk_shape)->notebook = gtk_notebook_new();
	gtk_widget_set_hexpand(GTK_WIDGET((*gtk_shape)->notebook), TRUE);
	gtk_set_transform_tab_widgets(&(*gtk_shape)->transform,
								&scene_shape->dto->transform);

}
