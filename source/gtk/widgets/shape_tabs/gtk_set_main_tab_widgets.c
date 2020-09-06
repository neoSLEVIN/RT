/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_main_tab_widgets.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:01 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

/*
** TODO add new types
*/

static void	gtk_set_type_list(GtkComboBoxText *type_combo)
{
	gtk_combo_box_text_append_text(type_combo, "PLANE");
	gtk_combo_box_text_append_text(type_combo, "SPHERE");
	gtk_combo_box_text_append_text(type_combo, "CONE");
	gtk_combo_box_text_append_text(type_combo, "CAPPED CONE");
	gtk_combo_box_text_append_text(type_combo, "CYLINDER");
	gtk_combo_box_text_append_text(type_combo, "CAPSULE");
	gtk_combo_box_text_append_text(type_combo, "CAPPED CYLINDER");
	gtk_combo_box_text_append_text(type_combo, "CIRCLE");
	gtk_combo_box_text_append_text(type_combo, "CAPPED PLANE");
	gtk_combo_box_text_append_text(type_combo, "BOX");
	gtk_combo_box_text_append_text(type_combo, "TRIANGLE");
}

static void	gtk_set_main_tab_name_type_widgets(t_main_tab *main_tab)
{
	main_tab->name_label = gtk_label_new("Name:");
	gtk_widget_set_margin_start(main_tab->name_label, 5);
	gtk_widget_set_margin_end(main_tab->name_label, 5);
	gtk_widget_set_margin_top(main_tab->name_label, 5);
	main_tab->name_changer = gtk_entry_new();
	gtk_widget_set_margin_end(main_tab->name_changer, 5);
	gtk_widget_set_margin_top(main_tab->name_changer, 5);
	gtk_entry_set_max_length(GTK_ENTRY(main_tab->name_changer), 20);
	main_tab->type_label = gtk_label_new("Type:");
	gtk_widget_set_margin_start(main_tab->type_label, 5);
	gtk_widget_set_margin_end(main_tab->type_label, 5);
	gtk_widget_set_margin_top(main_tab->type_label, 5);
	main_tab->type_combo = gtk_combo_box_text_new();
	gtk_widget_set_margin_end(main_tab->type_combo, 5);
	gtk_widget_set_margin_top(main_tab->type_combo, 5);
	gtk_set_type_list(GTK_COMBO_BOX_TEXT(main_tab->type_combo));
	gtk_combo_box_set_active(GTK_COMBO_BOX(main_tab->type_combo), 0);
}

void		gtk_set_radius_spinner(t_spinner *spinner, const char *name,
									cl_float value)
{
	spinner->label = gtk_label_new(name);
	gtk_widget_set_margin_start(spinner->label, 5);
	gtk_widget_set_margin_end(spinner->label, 5);
	gtk_set_spin_button_for_radius(&spinner->spin, value);
}

static void	gtk_set_main_tab_params_widgets(t_main_tab *main_tab,
											DTO_SHAPE *dto)
{
	main_tab->params_frame = gtk_frame_new("Params");
	main_tab->v_params = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	main_tab->h_radius = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_radius_spinner(&main_tab->radius, "Radius:", dto->params.x);
	main_tab->h_width = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_radius_spinner(&main_tab->width, "Width:", dto->params.x);
	main_tab->h_height = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_radius_spinner(&main_tab->height, "Height:", dto->params.y);
	main_tab->h_depth = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_radius_spinner(&main_tab->depth, "Depth:", dto->params.z);
	main_tab->h_angle = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	main_tab->angle.label = gtk_label_new("Angle:");
	gtk_widget_set_margin_start(main_tab->angle.label, 5);
	gtk_widget_set_margin_end(main_tab->angle.label, 5);
	gtk_set_spin_button_for_angle(&main_tab->angle.spin,
								rad_to_deg(dto->params.x));
	main_tab->h_shift = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	main_tab->shift.label = gtk_label_new("Shift:");
	gtk_widget_set_margin_start(main_tab->shift.label, 5);
	gtk_widget_set_margin_end(main_tab->shift.label, 5);
	gtk_set_spin_button_for_float(&main_tab->shift.spin, dto->params.z);
}

void		gtk_set_main_tab_widgets(t_main_tab *main_tab, DTO_SHAPE *dto)
{
	main_tab->label = gtk_label_new("Main");
	main_tab->grid = gtk_grid_new();
	gtk_set_main_tab_name_type_widgets(main_tab);
	gtk_set_main_tab_params_widgets(main_tab, dto);
}
