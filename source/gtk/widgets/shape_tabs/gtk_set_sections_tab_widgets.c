/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_sections_tab_widgets.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:11 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_sections_tab_base_widgets(t_section_tab *section_tab)
{
	section_tab->label = gtk_label_new("Sections");
	section_tab->grid = gtk_grid_new();
}

static void	gtk_set_sections_tab_buttons_widgets(t_section_tab *section_tab,
															_Bool is_complex)
{
	section_tab->style_frame = gtk_frame_new("Style");
	section_tab->style_grid = gtk_grid_new();
	section_tab->style_simple = gtk_radio_button_new_with_label(NULL, "Simple");
	section_tab->style_complex = gtk_radio_button_new_with_label_from_widget(
		GTK_RADIO_BUTTON(section_tab->style_simple), "Complex");
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(section_tab->style_simple), !is_complex);
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(section_tab->style_complex), is_complex);
	section_tab->centre_button =
		gtk_button_new_with_label("Centralize position");
	gtk_widget_set_halign(section_tab->centre_button, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(section_tab->centre_button, GTK_ALIGN_CENTER);
}

static void	gtk_set_sections_tab_position_widgets(t_section_tab *section_tab,
														SECTION *shape_sections)
{
	section_tab->pos_grid = gtk_grid_new();
	section_tab->pos_label = gtk_label_new("Position:");
	gtk_widget_set_margin_top(section_tab->pos_label, 5);
	gtk_widget_set_margin_bottom(section_tab->pos_label, 5);
	section_tab->pos_x.label = gtk_label_new("X:");
	gtk_widget_set_margin_start(section_tab->pos_x.label, 5);
	gtk_widget_set_margin_end(section_tab->pos_x.label, 5);
	gtk_set_spin_button_for_float(&section_tab->pos_x.spin,
								shape_sections[0].position.x);
	section_tab->pos_y.label = gtk_label_new("Y:");
	gtk_set_spin_button_for_float(&section_tab->pos_y.spin,
								shape_sections[0].position.y);
	section_tab->pos_z.label = gtk_label_new("Z:");
	gtk_set_spin_button_for_float(&section_tab->pos_z.spin,
								shape_sections[0].position.z);
}

static void	gtk_set_sections_tab_addition_widgets(t_section_tab *section_tab,
														SECTION *shape_sections)
{
	section_tab->addition_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	section_tab->plane_grid = gtk_grid_new();
	section_tab->dir_label = gtk_label_new("Direction:");
	gtk_widget_set_margin_top(section_tab->dir_label, 5);
	gtk_widget_set_margin_bottom(section_tab->dir_label, 5);
	gtk_set_spin_button_for_float(&section_tab->spin_dir_x,
								shape_sections[0].direction.x);
	gtk_widget_set_margin_start(section_tab->spin_dir_x, 5);
	gtk_widget_set_margin_end(section_tab->spin_dir_x, 5);
	gtk_set_spin_button_for_float(&section_tab->spin_dir_y,
								shape_sections[0].direction.y);
	gtk_widget_set_margin_start(section_tab->spin_dir_y, 5);
	gtk_widget_set_margin_end(section_tab->spin_dir_y, 5);
	gtk_set_spin_button_for_float(&section_tab->spin_dir_z,
								shape_sections[0].direction.z);
	gtk_widget_set_margin_start(section_tab->spin_dir_z, 5);
	gtk_widget_set_margin_end(section_tab->spin_dir_z, 5);
	section_tab->sphere_grid = gtk_grid_new();
	section_tab->radius.label = gtk_label_new("Radius:");
	gtk_widget_set_margin_top(section_tab->radius.label, 5);
	gtk_widget_set_margin_bottom(section_tab->radius.label, 5);
	gtk_set_spin_button_for_radius(&section_tab->radius.spin,
								shape_sections[0].param);
	gtk_widget_set_margin_start(section_tab->radius.spin, 5);
	gtk_widget_set_margin_end(section_tab->radius.spin, 5);
}

void		gtk_set_sections_tab_widgets(t_section_tab *section_tab,
									SECTION *shape_sections, _Bool is_complex)
{
	gtk_set_sections_tab_base_widgets(section_tab);
	gtk_set_sections_tab_buttons_widgets(section_tab, is_complex);
	gtk_set_sections_tab_tree_widgets(section_tab, shape_sections);
	gtk_set_sections_tab_position_widgets(section_tab, shape_sections);
	gtk_set_sections_tab_addition_widgets(section_tab, shape_sections);
}
