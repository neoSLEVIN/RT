/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gtk_shape_section.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:21 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	update_gtk_shape_sec_spins(t_section_tab *tab, SECTION *section)
{
	gtk_widget_set_visible(tab->plane_grid, section->type == PLANE);
	gtk_widget_set_visible(tab->sphere_grid, section->type == SPHERE);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->pos_x.spin),
		section->position.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->pos_y.spin),
		section->position.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->pos_z.spin),
		section->position.z);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->radius.spin),
		section->param);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->spin_dir_x),
		section->direction.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->spin_dir_y),
		section->direction.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->spin_dir_z),
		section->direction.z);
}

void		update_gtk_shape_section(t_section_tab tab, SECTION *shape_sec,
									_Bool is_complex)
{
	GtkTreeIter	iter;
	SECTION		*section;
	int			i;

	i = -1;
	while (++i < SECTION_CNT)
		gtk_tree_store_set(tab.store, &tab.iter[i],
			SEC_ON_COL, shape_sec[i].on,
			SEC_TYPE_COL, (shape_sec[i].type == PLANE) ? "PLANE" : "SPHERE",
			SEC_POINTER_COL, &shape_sec[i],
			-1);
	if (!gtk_tree_selection_get_selected(tab.select, &tab.model, &iter))
		iter = tab.iter[0];
	gtk_tree_model_get(tab.model, &iter,
			SEC_POINTER_COL, &section,
			-1);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.style_complex),
			is_complex);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.style_simple),
			!is_complex);
	update_gtk_shape_sec_spins(&tab, section);
}
