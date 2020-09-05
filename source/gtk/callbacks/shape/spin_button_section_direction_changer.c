/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_section_direction_changer.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:59 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:24:00 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	back_to_previous_values(t_section_tab *tab, SECTION *section)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->spin_dir_x),
							section->direction.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->spin_dir_y),
							section->direction.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->spin_dir_z),
							section->direction.z);
	return (FALSE);
}

static gboolean	spin_button_section_direction_changer_safe(gpointer data)
{
	t_rt			*rt;
	t_section_tab	*tab;
	SECTION			*section;
	FLT3			temp_dir;
	GtkTreeIter		iter;

	rt = (t_rt*)data;
	if (!gtk_tree_selection_get_selected(rt->gtk->ui.shape->section.select,
									&rt->gtk->ui.shape->section.model, &iter))
		iter = rt->gtk->ui.shape->section.iter[0];
	gtk_tree_model_get(rt->gtk->ui.shape->section.model, &iter,
					SEC_POINTER_COL, &section,
					-1);
	tab = &rt->gtk->ui.shape->section;
	temp_dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->spin_dir_x));
	temp_dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->spin_dir_y));
	temp_dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(tab->spin_dir_z));
	if (v3_length_sq(temp_dir) == 0.0f)
		return (back_to_previous_values(tab, section));
	section->direction = temp_dir;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
	return (FALSE);
}

void			spin_button_section_direction_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_section_direction_changer_safe, data);
}
