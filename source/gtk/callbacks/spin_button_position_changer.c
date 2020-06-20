/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_position_changer.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 07:05:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 07:05:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	spin_button_shape_position_changer_safe(gpointer data)
{
	t_rt			*rt;
	FLT3			*position;
	t_transform_tab	*transform;

	rt = (t_rt*)data;
	position = &rt->gtk->ui.shape->shape->dto->transform.position;
	transform = &rt->gtk->ui.shape->transform;
	position->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->x.spin));
	position->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->y.spin));
	position->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->z.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
	return (FALSE);
}

void	spin_button_shape_position_changer(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(spin_button_shape_position_changer_safe, data);
}

gboolean	spin_button_section_position_changer_safe(gpointer data)
{
	t_rt			*rt;
	t_section_tab	*section_tab;
	SECTION			*section;
	GtkTreeIter		iter;

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

void	spin_button_section_position_changer(GtkSpinButton *button,
											 gpointer data)
{
	(void)button;
	g_idle_add(spin_button_section_position_changer_safe, data);
}

gboolean	spin_button_section_radius_changer_safe(gpointer data)
{
	t_rt			*rt;
	SECTION			*section;
	GtkTreeIter		iter;

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

void	spin_button_section_radius_changer(GtkSpinButton *button,
											 gpointer data)
{
	(void)button;
	g_idle_add(spin_button_section_radius_changer_safe, data);
}

gboolean	spin_button_section_direction_changer_safe(gpointer data)
{
	t_rt			*rt;
	t_section_tab	*section_tab;
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
	section_tab = &rt->gtk->ui.shape->section;
	temp_dir.x =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(section_tab->spin_dir_x));
	temp_dir.y =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(section_tab->spin_dir_y));
	temp_dir.z =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(section_tab->spin_dir_z));
	if (v3_length_sq(temp_dir) == 0.0f)
	{
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(section_tab->spin_dir_x),
			section->direction.x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(section_tab->spin_dir_y),
								  section->direction.y);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(section_tab->spin_dir_z),
								  section->direction.z);
		return (FALSE);
	}
	section->direction = temp_dir;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					  &rt->info->update_shapes);
	rt->info->update = TRUE;
	return (FALSE);
}

void	spin_button_section_direction_changer(GtkSpinButton *button,
										   gpointer data)
{
	(void)button;
	g_idle_add(spin_button_section_direction_changer_safe, data);
}
