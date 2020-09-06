/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_section_radius_changer.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 07:05:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:24:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_section_radius_changer_safe(gpointer data)
{
	t_rt				*rt;
	GtkTreeIter			iter;
	struct s_section	*section;

	rt = (t_rt*)data;
	if (!gtk_tree_selection_get_selected(rt->gtk->ui.shape->section.select,
									&rt->gtk->ui.shape->section.model, &iter))
		iter = rt->gtk->ui.shape->section.iter[0];
	gtk_tree_model_get(rt->gtk->ui.shape->section.model, &iter,
					SEC_POINTER_COL, &section,
					-1);
	section->param = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
								rt->gtk->ui.shape->section.radius.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
	return (FALSE);
}

void			spin_button_section_radius_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_section_radius_changer_safe, data);
}
