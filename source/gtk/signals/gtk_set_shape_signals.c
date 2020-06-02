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
	flag = &rt->gtk->ui.shape->shape->dto->section[0].on;
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
	flag = &rt->gtk->ui.shape->shape->dto->section[1].on;
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
	flag = &rt->gtk->ui.shape->shape->dto->section[2].on;
	*flag = gtk_toggle_button_get_active(toggle_button);
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

	g_signal_connect(GTK_TOGGLE_BUTTON(shape->section.on_x), "toggled",
		G_CALLBACK(change_section_flag_x), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(shape->section.on_y), "toggled",
		G_CALLBACK(change_section_flag_y), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(shape->section.on_z), "toggled",
		G_CALLBACK(change_section_flag_z), rt);
}
