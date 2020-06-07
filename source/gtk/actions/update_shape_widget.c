/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shape_widget.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:58:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 21:36:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	update_gtk_shape_pos(t_transform_tab tab, FLT3 shape_pos)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.x.spin), shape_pos.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.y.spin), shape_pos.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.z.spin), shape_pos.z);
}

static void	update_gtk_shape_mat(t_material_tab tab, MATERIAL shape_mat)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.transparency.spin),
		shape_mat.transparency);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.reflective.spin),
		shape_mat.reflective);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.specular.spin),
		shape_mat.specular);
}

static void	update_gtk_shape_sec(t_section_tab tab, SECTION *shape_sec)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.on_x), shape_sec[0].on);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.on_y), shape_sec[1].on);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.on_z), shape_sec[2].on);
}

gboolean	update_shape_widget(gpointer data)
{
	t_rt		*rt;
	t_gtk_shape	*shape;
	gint		current_page;

	rt = (t_rt*)data;
	shape = rt->gtk->ui.shape;
	if (gtk_expander_get_expanded(GTK_EXPANDER(shape->expander)))
	{
		current_page =
			gtk_notebook_get_current_page(GTK_NOTEBOOK(shape->notebook));
		if (rt->info->update_s_name)
			gtk_frame_set_label(GTK_FRAME(shape->frame), shape->shape->name);
		if (current_page == 0 && rt->info->update_s_pos)
			update_gtk_shape_pos(shape->transform,
				shape->shape->dto->transform.position);
		else if (current_page == 1 && rt->info->update_s_mat)
			update_gtk_shape_mat(shape->material, shape->shape->dto->material);
		else if (current_page == 2 && rt->info->update_s_sec)
			update_gtk_shape_sec(shape->section, shape->shape->dto->sections);
	}
	shape_to_false(rt->info);
	return (FALSE);
}
