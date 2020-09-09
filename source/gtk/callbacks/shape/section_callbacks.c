/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_callbacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void		section_type_edited(GtkCellRendererCombo *combo, gchar *path_string,
							GtkTreeIter *new_iter, gpointer data)
{
	t_rt	*rt;
	gchar	*type;

	(void)combo;
	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
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
	g_free(type);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}

void		section_on_edited(GtkCellRendererToggle *toggle, gchar *path_string,
						gpointer data)
{
	t_rt		*rt;
	gboolean	on;
	int			iter_num;

	(void)toggle;
	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
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

void		sections_tree_row_select(GtkTreeSelection *selection, gpointer data)
{
	t_rt	*rt;

	(void)selection;
	rt = (t_rt*)data;
	rt->info->update_s_sec = TRUE;
	g_idle_add(update_shape_widget, rt);
}

void		sections_style_toggle_button(GtkWidget *button, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
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
	t_rt				*rt;
	GtkTreeIter			iter;
	t_section_tab		*tab;
	struct s_section	*section;

	(void)event_box;
	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
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
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (TRUE);
}
