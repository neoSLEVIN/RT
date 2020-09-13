/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 07:03:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/02 04:19:00 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_shape_base_signals(t_gtk_shape *shape, t_rt *rt)
{
	g_signal_connect(G_OBJECT(shape->expander), "notify::expanded",
		G_CALLBACK(shape_expander_callback), rt);
	g_signal_connect(G_OBJECT(shape->notebook), "switch-page",
		G_CALLBACK(switch_page_shape_notebook), rt);
}

static void	gtk_set_shape_trans_mat_color_signals(t_transform_tab *transform,
						t_material_tab *material, t_color_tab *color, t_rt *rt)
{
	g_signal_connect(G_OBJECT(transform->x.spin), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
	g_signal_connect(G_OBJECT(transform->y.spin), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
	g_signal_connect(G_OBJECT(transform->z.spin), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
	g_signal_connect(G_OBJECT(material->transparency.spin), "value-changed",
		G_CALLBACK(shape_material_scale_moved), rt);
	g_signal_connect(G_OBJECT(material->refraction.spin), "value-changed",
		G_CALLBACK(shape_material_scale_moved), rt);
	g_signal_connect(G_OBJECT(material->reflective.spin), "value-changed",
		G_CALLBACK(shape_material_scale_moved), rt);
	g_signal_connect(G_OBJECT(material->specular.spin), "value-changed",
		G_CALLBACK(shape_material_scale_moved), rt);
	g_signal_connect(G_OBJECT(color->red.spin), "value-changed",
		G_CALLBACK(spin_button_color_changer), rt);
	g_signal_connect(G_OBJECT(color->green.spin), "value-changed",
		G_CALLBACK(spin_button_color_changer), rt);
	g_signal_connect(G_OBJECT(color->blue.spin), "value-changed",
		G_CALLBACK(spin_button_color_changer), rt);
}

static void	gtk_set_shape_sections_signals(t_section_tab *tab, t_rt *rt)
{
	g_signal_connect(G_OBJECT(tab->combo_renderer), "changed",
		G_CALLBACK(section_type_edited), rt);
	g_signal_connect(G_OBJECT(tab->toggle_on_renderer), "toggled",
		G_CALLBACK(section_on_edited), rt);
	g_signal_connect(G_OBJECT(tab->pos_x.spin), "value-changed",
		G_CALLBACK(spin_button_section_position_changer), rt);
	g_signal_connect(G_OBJECT(tab->pos_y.spin), "value-changed",
		G_CALLBACK(spin_button_section_position_changer), rt);
	g_signal_connect(G_OBJECT(tab->pos_z.spin), "value-changed",
		G_CALLBACK(spin_button_section_position_changer), rt);
	g_signal_connect(G_OBJECT(tab->radius.spin), "value-changed",
		G_CALLBACK(spin_button_section_radius_changer), rt);
	g_signal_connect(G_OBJECT(tab->spin_dir_x), "value-changed",
		G_CALLBACK(spin_button_section_direction_changer), rt);
	g_signal_connect(G_OBJECT(tab->spin_dir_y), "value-changed",
		G_CALLBACK(spin_button_section_direction_changer), rt);
	g_signal_connect(G_OBJECT(tab->spin_dir_z), "value-changed",
		G_CALLBACK(spin_button_section_direction_changer), rt);
	g_signal_connect(G_OBJECT(tab->select), "changed",
		G_CALLBACK(sections_tree_row_select), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(tab->style_complex), "toggled",
		G_CALLBACK(sections_style_toggle_button), rt);
	g_signal_connect(GTK_BUTTON(tab->centre_button), "button-press-event",
		G_CALLBACK(centralize_section_position), rt);
}

static void	gtk_set_shape_texture_main_signals(t_texture_tab *texture,
												t_main_tab *main_tab, t_rt *rt)
{
	g_signal_connect(G_OBJECT(texture->texture_combo), "changed",
		G_CALLBACK(changing_texture_type), rt);
	g_signal_connect(G_OBJECT(texture->normals_combo), "changed",
		G_CALLBACK(changing_normals_type), rt);
	g_signal_connect(G_OBJECT(main_tab->type_combo), "changed",
		G_CALLBACK(changing_shape_type), rt);
	g_signal_connect(G_OBJECT(main_tab->name_changer), "key-press_event",
		G_CALLBACK(press_key_on_shape_name), rt);
	g_signal_connect(G_OBJECT(main_tab->radius.spin), "value-changed",
		G_CALLBACK(spin_button_shape_radius_changer), rt);
	g_signal_connect(G_OBJECT(main_tab->width.spin), "value-changed",
		G_CALLBACK(spin_button_shape_width_changer), rt);
	g_signal_connect(G_OBJECT(main_tab->height.spin), "value-changed",
		G_CALLBACK(spin_button_shape_height_changer), rt);
	g_signal_connect(G_OBJECT(main_tab->shift.spin), "value-changed",
		G_CALLBACK(spin_button_shape_shift_changer), rt);
	g_signal_connect(G_OBJECT(main_tab->depth.spin), "value-changed",
		G_CALLBACK(spin_button_shape_depth_changer), rt);
	g_signal_connect(G_OBJECT(main_tab->angle.spin), "value-changed",
		G_CALLBACK(spin_button_shape_angle_changer), rt);
}

void		gtk_set_shape_signals(t_rt *rt)
{
	t_gtk_shape	*shape;

	shape = rt->gtk->ui.shape;
	gtk_set_shape_base_signals(shape, rt);
	gtk_set_shape_trans_mat_color_signals(&shape->transform, &shape->material,
		&shape->color, rt);
	gtk_set_triangle_dots_signals(&shape->transform, rt);
	gtk_set_shape_sections_signals(&shape->section, rt);
	gtk_set_shape_texture_main_signals(&shape->texture, &shape->main, rt);
	g_signal_connect(G_OBJECT(shape->section.combo_renderer), "editing-started",
		G_CALLBACK(cell_editable_holders), NULL);
}
