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

static void	shape_expander_callback(GObject *object, GParamSpec *param_spec,
									gpointer data)
{
	t_rt		*rt;
	GtkExpander	*expander;

	(void)param_spec;
	rt = (t_rt*)data;
	expander = GTK_EXPANDER(object);
	if (gtk_expander_get_expanded(expander))
	{
		if (rt->gtk->ui.shape->shape == NULL)
			return (gtk_expander_set_expanded(expander, FALSE));
		shape_to_true(rt->info);
		g_idle_add(update_shape_widget, rt);
	}
}

void	spin_button_shape_material_changer(GtkSpinButton *button, gpointer data)
{
	t_rt			*rt;
	MATERIAL		*material;
	t_material_tab	*material_tab;

	(void)button;
	rt = (t_rt*)data;
	material = &rt->gtk->ui.shape->shape->dto->material;
	material_tab = &rt->gtk->ui.shape->material;
	material->transparency = gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(material_tab->transparency.spin));
	material->reflective = gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(material_tab->reflective.spin));
	material->specular = gtk_spin_button_get_value(
		GTK_SPIN_BUTTON(material_tab->specular.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}

void	switch_page_shape_notebook(GtkNotebook *notebook, GtkWidget *page,
									guint page_num, gpointer data)
{
	t_rt	*rt;

	(void)notebook;
	(void)page;
	rt = (t_rt*)data;
	if (page_num == 0)
		rt->info->update_s_pos = TRUE;
	else if (page_num == 1)
		rt->info->update_s_mat = TRUE;
	g_idle_add(update_shape_widget, rt);
}


void	change_section_flag_x(GtkToggleButton *toggle_button, gpointer data)
{
	t_rt	*rt;
	_Bool	*flag;

	rt = (t_rt*)data;
	flag = &rt->gtk->ui.shape->shape->dto->sections[0].on;
	*flag = gtk_toggle_button_get_active(toggle_button);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}

void	change_section_flag_y(GtkToggleButton *toggle_button, gpointer data)
{
	t_rt	*rt;
	_Bool	*flag;

	rt = (t_rt*)data;
	flag = &rt->gtk->ui.shape->shape->dto->sections[1].on;
	*flag = gtk_toggle_button_get_active(toggle_button);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}

void	change_section_flag_z(GtkToggleButton *toggle_button, gpointer data)
{
	t_rt	*rt;
	_Bool	*flag;

	rt = (t_rt*)data;
	flag = &rt->gtk->ui.shape->shape->dto->sections[2].on;
	*flag = gtk_toggle_button_get_active(toggle_button);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}

void	combo_tree_listing(GtkCellRenderer *renderer, GtkCellEditable *editable,
			gchar *row_index, gpointer data)
{
	(void)renderer;
	(void)row_index;
	(void)data;
	if (GTK_IS_COMBO_BOX(editable))
		gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(editable), 10);
}



void	section_type_edited(GtkCellRendererCombo *combo, gchar *path_string,
							GtkTreeIter *new_iter, gpointer data)
{
	t_rt	*rt;
	gchar	*type;

	(void)combo;
	rt = (t_rt*)data;
	gtk_tree_model_get(GTK_TREE_MODEL(rt->gtk->ui.shape->section.type_store),
		new_iter, 0, &type, -1);
	gtk_tree_store_set(rt->gtk->ui.shape->section.store,
			&rt->gtk->ui.shape->section.iter[ft_atoi(path_string)],
			SEC_TYPE_COL, type,
			-1);
	rt->gtk->ui.shape->shape->dto->sections[ft_atoi(path_string)].type =
		(ft_strequ(type, "PLANE")) ? PLANE : SPHERE;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
		&rt->info->update_shapes);
	draw_image(rt);
}



void	gtk_set_shape_signals(t_rt *rt)
{
	t_gtk_shape	*shape;

	shape = rt->gtk->ui.shape;
	g_signal_connect(G_OBJECT(shape->expander), "notify::expanded",
		G_CALLBACK(shape_expander_callback), rt);
	g_signal_connect(G_OBJECT(shape->notebook), "switch-page",
		G_CALLBACK(switch_page_shape_notebook), rt);


	g_signal_connect(G_OBJECT(shape->transform.x.spin), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
	g_signal_connect(G_OBJECT(shape->transform.y.spin), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
	g_signal_connect(G_OBJECT(shape->transform.z.spin), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);

	g_signal_connect(G_OBJECT(shape->material.transparency.spin),
		"value-changed", G_CALLBACK(spin_button_shape_material_changer), rt);
	g_signal_connect(G_OBJECT(shape->material.reflective.spin),
		"value-changed", G_CALLBACK(spin_button_shape_material_changer), rt);
	g_signal_connect(G_OBJECT(shape->material.specular.spin),
		"value-changed", G_CALLBACK(spin_button_shape_material_changer), rt);

	g_signal_connect(G_OBJECT(shape->section.combo_renderer),
		"editing-started", G_CALLBACK(combo_tree_listing), NULL);
	g_signal_connect(G_OBJECT(shape->section.combo_renderer),
					 "changed", G_CALLBACK(section_type_edited), rt);
}
