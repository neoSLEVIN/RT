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
	if (page_num == TRANSFORM_TAB)
		rt->info->update_s_pos = TRUE;
	else if (page_num == MATERIAL_TAB)
		rt->info->update_s_mat = TRUE;
	else if (page_num == COLOR_TAB)
		rt->info->update_s_col = TRUE;
	else if (page_num == SECTION_TAB)
		rt->info->update_s_sec = TRUE;
	else
		ft_error("Update flag for unknown page in switch_page_shape_notebook, "
				"update_shape_widget");
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

void	cell_editable_holders(GtkCellRenderer *renderer,
					GtkCellEditable *editable, gchar *row_index, gpointer data)
{
	(void)renderer;
	(void)row_index;
	(void)data;
	if (GTK_IS_COMBO_BOX(editable))
		gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(editable), 10);
	else if (GTK_IS_SPIN_BUTTON(editable))
		gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(editable), TRUE);
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
	gtk_widget_set_visible(rt->gtk->ui.shape->section.plane_grid,
		ft_strequ(type, "PLANE"));
	gtk_widget_set_visible(rt->gtk->ui.shape->section.sphere_grid,
		ft_strequ(type, "SPHERE"));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
		&rt->info->update_shapes);
	draw_image(rt);
}

void	section_on_edited(GtkCellRendererToggle *toggle, gchar *path_string,
						gpointer data)
{
	t_rt		*rt;
	gboolean	on;
	int			iter_num;

	(void)toggle;
	rt = (t_rt*)data;
	iter_num = ft_atoi(path_string);
	gtk_tree_model_get(GTK_TREE_MODEL(rt->gtk->ui.shape->section.store),
		&rt->gtk->ui.shape->section.iter[iter_num], SEC_ON_COL, &on, -1);
	gtk_tree_store_set(rt->gtk->ui.shape->section.store,
		&rt->gtk->ui.shape->section.iter[iter_num],
		SEC_ON_COL, !on,
		-1);
	rt->gtk->ui.shape->shape->dto->sections[iter_num].on = !on;
	rt->gtk->ui.shape->shape->dto->working_sections += on ? -1 : 1;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}

void	sections_tree_row_select(GtkTreeSelection *selection, gpointer data)
{
	t_rt	*rt;

	(void)selection;
	rt = (t_rt*)data;
	rt->info->update_s_sec = TRUE;
	g_idle_add(update_shape_widget, rt);
}

void	sections_style_toggle_button(GtkWidget *button, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->gtk->ui.shape->shape->dto->is_complex_section =
						gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
								&rt->info->update_shapes);
	rt->info->update = TRUE;
}

gboolean	centralize_section_position(GtkWidget *event_box,
										GdkEventButton *event, gpointer data)
{
	t_rt			*rt;
	GtkTreeIter		iter;
	SECTION			*section;
	t_section_tab	*tab;

	(void)event_box;
	rt = (t_rt*)data;
	tab = &rt->gtk->ui.shape->section;
	if (event->button != 1)
		return (FALSE);
	if (!gtk_tree_selection_get_selected(tab->select, &tab->model, &iter))
		iter = tab->iter[0];
	gtk_tree_model_get(tab->model, &iter, SEC_POINTER_COL, &section, -1);
	section->position = rt->gtk->ui.shape->shape->dto->transform.position;
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->pos_x.spin),
							  section->position.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->pos_y.spin),
							  section->position.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->pos_z.spin),
							  section->position.z);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
								&rt->info->update_shapes);
	rt->info->update = TRUE;
	return (TRUE);
}

void	color_activated_changer(GtkColorChooser *chooser,
								GParamSpec *param_spec, gpointer data)
{
	t_rt	*rt;
	GdkRGBA	color;

	(void)param_spec;
	if (!gtk_widget_get_visible(GTK_WIDGET(chooser)))
		return ;
	rt = (t_rt*)data;
	gtk_color_chooser_get_rgba(chooser, &color);
	rt->gtk->ui.shape->shape->dto->material.color =
		(FLT3){(float)color.red, (float)color.green, (float)color.blue};
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					  &rt->info->update_shapes);
	rt->info->update = TRUE;
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

	g_signal_connect(G_OBJECT(shape->color.color),
					 "notify", G_CALLBACK(color_activated_changer), rt);

	g_signal_connect(G_OBJECT(shape->section.combo_renderer),
		"editing-started", G_CALLBACK(cell_editable_holders), NULL);

	g_signal_connect(G_OBJECT(shape->section.combo_renderer),
		"changed", G_CALLBACK(section_type_edited), rt);
	g_signal_connect(G_OBJECT(shape->section.toggle_on_renderer),
		"toggled", G_CALLBACK(section_on_edited), rt);

	g_signal_connect(G_OBJECT(shape->section.pos_x.spin), "value-changed",
					 G_CALLBACK(spin_button_section_position_changer), rt);
	g_signal_connect(G_OBJECT(shape->section.pos_y.spin), "value-changed",
					 G_CALLBACK(spin_button_section_position_changer), rt);
	g_signal_connect(G_OBJECT(shape->section.pos_z.spin), "value-changed",
					 G_CALLBACK(spin_button_section_position_changer), rt);
	g_signal_connect(G_OBJECT(shape->section.radius.spin), "value-changed",
					 G_CALLBACK(spin_button_section_radius_changer), rt);
	g_signal_connect(G_OBJECT(shape->section.spin_dir_x), "value-changed",
					 G_CALLBACK(spin_button_section_direction_changer), rt);
	g_signal_connect(G_OBJECT(shape->section.spin_dir_y), "value-changed",
					 G_CALLBACK(spin_button_section_direction_changer), rt);
	g_signal_connect(G_OBJECT(shape->section.spin_dir_z), "value-changed",
					 G_CALLBACK(spin_button_section_direction_changer), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.shape->section.select), "changed",
					 G_CALLBACK(sections_tree_row_select), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(rt->gtk->ui.shape->section.style_complex), "toggled",
					 G_CALLBACK(sections_style_toggle_button), rt);
	g_signal_connect(GTK_BUTTON(rt->gtk->ui.shape->section.centre_button), "button-press-event",
					 G_CALLBACK(centralize_section_position), rt);

}
