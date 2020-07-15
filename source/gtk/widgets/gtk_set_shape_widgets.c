/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_widgets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:03:47 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 06:22:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static SHAPE	*get_default_shape(SHAPE *shape, DTO_SHAPE *dto)
{
	shape->tree_iter = NULL;
	shape->name = NULL;
	shape->next = NULL;
	shape->prev = NULL;
	shape->widgets = NULL;
	shape->texture_name = NULL;
	shape->normal_map_name = NULL;
	shape->dto = dto;
	shape->dto->type = SPHERE;
	return (shape);
}

static void		gtk_set_transform_tab_widgets(t_transform_tab *transform_tab,
										TRANSFORM *shape_transform)
{
	transform_tab->label = gtk_label_new("Transform");
	transform_tab->grid = gtk_grid_new();
	transform_tab->label_pos = gtk_label_new("Position:");
	gtk_widget_set_margin_top(transform_tab->label_pos, 5);
	gtk_widget_set_margin_bottom(transform_tab->label_pos, 5);
	transform_tab->x.label = gtk_label_new("X:");
	gtk_widget_set_margin_start(transform_tab->x.label, 5);
	gtk_widget_set_margin_end(transform_tab->x.label, 5);
	gtk_set_spin_button_for_float(&transform_tab->x.spin,
							shape_transform->position.x);
	transform_tab->y.label = gtk_label_new("Y:");
	gtk_set_spin_button_for_float(&transform_tab->y.spin,
							shape_transform->position.y);
	transform_tab->z.label = gtk_label_new("Z:");
	gtk_set_spin_button_for_float(&transform_tab->z.spin,
							shape_transform->position.z);
}

static void		gtk_set_material_tab_widgets(t_material_tab *material_tab,
										MATERIAL *shape_material)
{
	material_tab->label = gtk_label_new("Material");
	material_tab->grid = gtk_grid_new();
	material_tab->transparency.label = gtk_label_new("Transparency:");
	material_tab->reflective.label = gtk_label_new("Reflective:");
	material_tab->specular.label = gtk_label_new("Specular:");
	gtk_widget_set_margin_start(material_tab->transparency.label, 5);
	gtk_widget_set_margin_end(material_tab->transparency.label, 5);
	gtk_set_spin_button_for_one(&material_tab->transparency.spin,
									shape_material->transparency);
	gtk_set_spin_button_for_one(&material_tab->reflective.spin,
									shape_material->reflective);
	gtk_set_spin_button_for_one(&material_tab->specular.spin,
									shape_material->specular);
	gtk_widget_set_margin_top(material_tab->transparency.spin, 5);
}

static void		gtk_set_color_tab_widgets(t_color_tab *color_tab, FLT3 *color)
{
	color_tab->label = gtk_label_new("Color");
	color_tab->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(
		color_tab->scrolled_window), 370);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
		color_tab->scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
	color_tab->color = gtk_color_chooser_widget_new();
	gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(color_tab->color), FALSE);
	g_object_set(color_tab->color, "show-editor", TRUE, NULL);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_tab->color),
		&(GdkRGBA){color->x, color->y, color->z, 1});
	gtk_widget_set_margin_top(color_tab->color, 10);
	gtk_widget_set_margin_bottom(color_tab->color, 15);
}






static void	gtk_tree_view_insert_section_type_column(t_section_tab *section)
{
	GtkTreeIter	iter;

	section->type_store = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_list_store_append(section->type_store, &iter);
	gtk_list_store_set(section->type_store, &iter, 0, "PLANE", -1);
	gtk_list_store_append(section->type_store, &iter);
	gtk_list_store_set(section->type_store, &iter, 0, "SPHERE", -1);
	g_object_set(section->combo_renderer, "model", section->type_store,
		"text-column", 0, "has-entry", FALSE, "editable", TRUE, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(section->tree),
		SEC_TYPE_COL, "Type", section->combo_renderer,
		"text", SEC_TYPE_COL, NULL);
}

static void	gtk_insert_columns_in_sections_tree(t_section_tab *section)
{
	section->toggle_on_renderer = gtk_cell_renderer_toggle_new();
	section->combo_renderer = gtk_cell_renderer_combo_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(section->tree),
		SEC_ON_COL, "On/Off", section->toggle_on_renderer,
		"active", SEC_ON_COL, NULL);
	gtk_tree_view_insert_section_type_column(section);
}

static void	gtk_insert_rows_in_sections_tree(t_section_tab *section_tab,
												SECTION *shape_sections)
{
	SECTION	*section;
	int		i;

	i = -1;
	while (++i < SECTION_CNT)
	{
		section = &shape_sections[i];
		gtk_tree_store_append(section_tab->store, &section_tab->iter[i], NULL);
		gtk_tree_store_set(section_tab->store, &section_tab->iter[i],
			SEC_ON_COL, section->on,
			SEC_TYPE_COL, (section->type == PLANE) ? "PLANE" : "SPHERE",
			SEC_POINTER_COL, section,
			-1);
	}
}

static void		gtk_set_sections_tab_widgets(t_section_tab *section_tab,
									SECTION *shape_sections, _Bool is_complex)
{
	section_tab->label = gtk_label_new("Sections");
	section_tab->grid = gtk_grid_new();
	section_tab->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(
		section_tab->scrolled_window), 200);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(
			section_tab->scrolled_window), 370);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
		section_tab->scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	section_tab->style_frame = gtk_frame_new("Style");
	section_tab->style_grid = gtk_grid_new();
	section_tab->style_simple = gtk_radio_button_new_with_label(NULL, "Simple");
	section_tab->style_complex =
		gtk_radio_button_new_with_label_from_widget(
			GTK_RADIO_BUTTON(section_tab->style_simple), "Complex");
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(section_tab->style_simple), !is_complex);
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(section_tab->style_complex), is_complex);

	section_tab->centre_button =
		gtk_button_new_with_label("Centralize position");
	gtk_widget_set_halign(section_tab->centre_button, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(section_tab->centre_button, GTK_ALIGN_CENTER);

	section_tab->store = gtk_tree_store_new(SEC_COL_CNT,
		G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_POINTER);
	section_tab->model = GTK_TREE_MODEL(section_tab->store);
	gtk_insert_rows_in_sections_tree(section_tab, shape_sections);
	section_tab->tree =
			gtk_tree_view_new_with_model(GTK_TREE_MODEL(section_tab->store));
	gtk_widget_set_margin_bottom(GTK_WIDGET(section_tab->tree), 10);
	gtk_insert_columns_in_sections_tree(section_tab);
	section_tab->select =
			gtk_tree_view_get_selection(GTK_TREE_VIEW(section_tab->tree));
	gtk_tree_selection_set_mode(section_tab->select, GTK_SELECTION_SINGLE);
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



void			gtk_set_shape_widgets(t_gtk_shape **gtk_shape,
									SHAPE *scene_shape)
{
	SHAPE		default_shape;
	DTO_SHAPE	default_dto_shape;

	if ((*gtk_shape = (t_gtk_shape*)malloc(sizeof(t_gtk_shape))) == NULL)
		ft_error("Can't allocate memory");
	(*gtk_shape)->shape = scene_shape ? scene_shape : NULL;
	if (!scene_shape)
		scene_shape = get_default_shape(&default_shape, &default_dto_shape);
	(*gtk_shape)->expander = gtk_expander_new_with_mnemonic("_Shape");

	(*gtk_shape)->frame =
		gtk_frame_new((scene_shape->name) ? scene_shape->name : "NULL");
	gtk_frame_set_label_align(GTK_FRAME((*gtk_shape)->frame), 0.5, 0.0);

	(*gtk_shape)->notebook = gtk_notebook_new();
	gtk_widget_set_hexpand(GTK_WIDGET((*gtk_shape)->notebook), TRUE);
	gtk_set_transform_tab_widgets(&(*gtk_shape)->transform,
		&scene_shape->dto->transform);
	gtk_set_material_tab_widgets(&(*gtk_shape)->material,
		&scene_shape->dto->material);
	gtk_set_color_tab_widgets(&(*gtk_shape)->color,
								 &scene_shape->dto->material.color);
	gtk_set_sections_tab_widgets(&(*gtk_shape)->section,
		scene_shape->dto->sections, scene_shape->dto->is_complex_section);
}
