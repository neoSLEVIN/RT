/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_section_position_changer.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:24:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:24:04 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_section_position_changer_safe(gpointer data)
{
	t_rt				*rt;
	t_section_tab		*section_tab;
	struct s_section	*section;
	GtkTreeIter			iter;

	rt = (t_rt*)data;
	if (!gtk_tree_selection_get_selected(rt->gtk->ui.shape->section.select,
									&rt->gtk->ui.shape->section.model, &iter))
		iter = rt->gtk->ui.shape->section.iter[0];
	gtk_tree_model_get(rt->gtk->ui.shape->section.model, &iter,
					SEC_POINTER_COL, &section,
					-1);
	section_tab = &rt->gtk->ui.shape->section;
	section->position.x =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(section_tab->pos_x.spin));
	section->position.y =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(section_tab->pos_y.spin));
	section->position.z =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(section_tab->pos_z.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
	return (FALSE);
}

void			spin_button_section_position_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_section_position_changer_safe, data);
}
