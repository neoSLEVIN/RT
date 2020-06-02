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
	gtk_set_spin_button_for_percent(&material_tab->transparency.spin,
									shape_material->transparency);
	gtk_set_spin_button_for_percent(&material_tab->reflective.spin,
									shape_material->reflective);
	gtk_set_spin_button_for_percent(&material_tab->specular.spin,
									shape_material->specular);
	gtk_widget_set_margin_top(material_tab->transparency.spin, 5);
}


static void		gtk_set_section_tab_widgets(t_section_tab *section_tab,
												SECTION *shape_section)
{
	section_tab->label = gtk_label_new("Section");
	section_tab->grid = gtk_grid_new();
	section_tab->on_x = gtk_check_button_new();
	section_tab->on_y = gtk_check_button_new();
	section_tab->on_z = gtk_check_button_new();
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
	gtk_set_section_tab_widgets(&(*gtk_shape)->section,
								&scene_shape->dto->section);
}
