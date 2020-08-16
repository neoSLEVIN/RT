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

static void	update_gtk_shape_col(t_color_tab tab, FLT3 color)
{
	if (!gtk_widget_get_visible(tab.color))
		gtk_widget_set_visible(tab.color, TRUE);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(tab.color),
		&(GdkRGBA){color.x, color.y, color.z, 1});
}

static void	do_invisible_params(t_main_tab *tab)
{
	gtk_widget_set_visible(tab->params_frame, FALSE);
	gtk_widget_set_visible(tab->h_radius, FALSE);
	gtk_widget_set_visible(tab->h_height, FALSE);
	gtk_widget_set_visible(tab->h_angle, FALSE);
}

static void	do_visible_params(t_main_tab *tab, SHAPE_TYPE type)
{
	if (type != PLANE)
		gtk_widget_set_visible(tab->params_frame, TRUE);
	if (type == PLANE)
		(void)type;
	else if (type == SPHERE || type == CYLINDER)
		gtk_widget_set_visible(tab->h_radius, TRUE);
	else if (type == CONE)
		gtk_widget_set_visible(tab->h_angle, TRUE);
	else if (type == CAPPEDCYLINDER)
	{
		gtk_widget_set_visible(tab->h_radius, TRUE);
		gtk_widget_set_visible(tab->h_height, TRUE);
	}
	else
		ft_error("Unknown shape type (do_visible_params)");
}

static void	update_gtk_shape_params(t_main_tab *tab, DTO_SHAPE *dto)
{
	if (dto->type == PLANE)
		(void)dto;
	else if (dto->type == SPHERE || dto->type == CYLINDER)
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->radius.spin),
			dto->params.x);
	else if (dto->type == CONE)
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->angle.spin),
			rad_to_deg(dto->params.x));
	else if (dto->type == CAPPEDCYLINDER)
	{
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->radius.spin),
			dto->params.x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->height.spin),
			dto->params.y);
	}
	else
		ft_error("Unknown shape type (update_gtk_shape_params)");
}

static void	update_gtk_shape_main(t_main_tab tab, SHAPE *shape)
{
	gtk_entry_set_text(GTK_ENTRY(tab.name_changer), shape->name);
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.type_combo),
			shape->dto->type - 1);
	do_invisible_params(&tab);
	do_visible_params(&tab, shape->dto->type);
	update_gtk_shape_params(&tab, shape->dto);

}

static void	update_gtk_shape_tex(t_texture_tab tab,
							int texture_id, int normal_map_id)
{
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.texture_combo),
		texture_id + 5);
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.normals_combo),
		normal_map_id + 1);
}

void	update_gtk_shape_sec_spins(t_section_tab *tab, SECTION *section)
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

static void	update_gtk_shape_sec(t_section_tab tab, SECTION *shape_sec,
								_Bool is_complex)
{
/*	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.on_x), shape_sec[0].on);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.on_y), shape_sec[1].on);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.on_z), shape_sec[2].on);*/

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
	if (!gtk_tree_selection_get_selected(tab.select,
										 &tab.model, &iter))
		iter = tab.iter[0];
	gtk_tree_model_get(tab.model, &iter,
					   SEC_POINTER_COL, &section,
					   -1);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.style_complex), is_complex);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tab.style_simple), !is_complex);
	update_gtk_shape_sec_spins(&tab, section);
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
		if (current_page != COLOR_TAB &&
				gtk_widget_get_visible(rt->gtk->ui.shape->color.color))
			gtk_widget_set_visible(rt->gtk->ui.shape->color.color, FALSE);
		if (rt->info->update_s_name)
			gtk_frame_set_label(GTK_FRAME(shape->frame), shape->shape->name);
		if (current_page == MAIN_TAB && rt->info->update_s_main)
			update_gtk_shape_main(shape->main, shape->shape);
		else if (current_page == TRANSFORM_TAB && rt->info->update_s_pos)
			update_gtk_shape_pos(shape->transform,
				shape->shape->dto->transform.position);
		else if (current_page == MATERIAL_TAB && rt->info->update_s_mat)
			update_gtk_shape_mat(shape->material, shape->shape->dto->material);
		else if (current_page == COLOR_TAB && rt->info->update_s_col)
			update_gtk_shape_col(shape->color,
				shape->shape->dto->material.color);
		else if (current_page == TEXTURE_TAB && rt->info->update_s_tex)
			update_gtk_shape_tex(shape->texture,
				shape->shape->dto->texture.id,
				shape->shape->dto->normal_map.id);
		else if (current_page == SECTION_TAB && rt->info->update_s_sec)
			update_gtk_shape_sec(shape->section, shape->shape->dto->sections,
					shape->shape->dto->is_complex_section);
	}
	shape_to_false(rt->info);
	return (FALSE);
}
