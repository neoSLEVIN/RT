/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gtk_shape_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:10 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	do_invisible_params(t_main_tab *tab)
{
	gtk_widget_set_visible(tab->params_frame, FALSE);
	gtk_widget_set_visible(tab->h_radius, FALSE);
	gtk_widget_set_visible(tab->h_width, FALSE);
	gtk_widget_set_visible(tab->h_height, FALSE);
	gtk_widget_set_visible(tab->h_depth, FALSE);
	gtk_widget_set_visible(tab->h_angle, FALSE);
	gtk_widget_set_visible(tab->h_shift, FALSE);
}

static void	do_visible_params(t_main_tab *tab, SHAPE_TYPE type)
{
	if (type != PLANE && type != TRIANGLE && type != OFF)
		gtk_widget_set_visible(tab->params_frame, TRUE);
	if (type == PLANE || type == TRIANGLE || type == OFF)
		(void)type;
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		gtk_widget_set_visible(tab->h_radius, TRUE);
	else if (type == CONE || type == CAPPEDCONE)
	{
		gtk_widget_set_visible(tab->h_angle, TRUE);
		(type == CAPPEDCONE) ? gtk_widget_set_visible(tab->h_height, TRUE) : 0;
		(type == CAPPEDCONE) ? gtk_widget_set_visible(tab->h_shift, TRUE) : 0;
	}
	else if (type == CAPPEDCYLINDER || type == CAPSULE)
	{
		gtk_widget_set_visible(tab->h_radius, TRUE);
		gtk_widget_set_visible(tab->h_height, TRUE);
	}
	else if (type == CAPPEDPLANE || type == BOX)
	{
		gtk_widget_set_visible(tab->h_width, TRUE);
		gtk_widget_set_visible(tab->h_height, TRUE);
		(type == BOX) ? gtk_widget_set_visible(tab->h_depth, TRUE) : 0;
	}
	else
		ft_error("Unknown shape type (do_visible_params)");
}

static void	gtk_set_value_to_spin(t_spinner *spinner, cl_float value)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinner->spin), value);
}

static void	update_gtk_shape_main_params(t_main_tab *tab, FLT3 params,
										SHAPE_TYPE type)
{
	if (type == PLANE || type == TRIANGLE || type == OFF)
		(void)params;
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		gtk_set_value_to_spin(&tab->radius, params.x);
	else if (type == CONE || type == CAPPEDCONE)
	{
		gtk_set_value_to_spin(&tab->angle, rad_to_deg(params.x));
		(type != CONE) ? gtk_set_value_to_spin(&tab->height, params.y) : 0;
		(type != CONE) ? gtk_set_value_to_spin(&tab->shift, params.z) : 0;
	}
	else if (type == CAPPEDCYLINDER || type == CAPSULE)
	{
		gtk_set_value_to_spin(&tab->radius, params.x);
		gtk_set_value_to_spin(&tab->height, params.y);
	}
	else if (type == CAPPEDPLANE || type == BOX)
	{
		gtk_set_value_to_spin(&tab->width, params.x);
		gtk_set_value_to_spin(&tab->height, params.y);
		(type == BOX) ? gtk_set_value_to_spin(&tab->depth, params.z) : 0;
	}
	else
		ft_error("Unknown shape type (update_gtk_shape_main_params)");
}

void		update_gtk_shape_main(t_main_tab tab, SHAPE *shape)
{
	gtk_entry_set_text(GTK_ENTRY(tab.name_changer), shape->name);
	gtk_editable_select_region(GTK_EDITABLE(tab.name_changer), 0, 0);
	if (shape->dto->type != OFF)
	{
		gtk_widget_set_visible(tab.type_label, TRUE);
		gtk_widget_set_visible(tab.type_combo, TRUE);
		gtk_combo_box_set_active(GTK_COMBO_BOX(tab.type_combo),
								shape->dto->type - 1);
	}
	else
	{
		gtk_widget_set_visible(tab.type_label, FALSE);
		gtk_widget_set_visible(tab.type_combo, FALSE);
	}
	gtk_widget_grab_focus(tab.type_combo);
	do_invisible_params(&tab);
	do_visible_params(&tab, shape->dto->type);
	update_gtk_shape_main_params(&tab, shape->dto->params, shape->dto->type);
}
