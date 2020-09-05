/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_widgets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:03:47 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_shape_base_widgets(t_gtk_shape *gtk_shape,
										const char *shape_name)
{
	gtk_shape->expander = gtk_expander_new_with_mnemonic("_Shape");
	gtk_shape->frame = gtk_frame_new(shape_name ? shape_name : "NULL");
	gtk_frame_set_label_align(GTK_FRAME(gtk_shape->frame), 0.5, 0.0);
	gtk_shape->notebook = gtk_notebook_new();
	gtk_notebook_set_scrollable(GTK_NOTEBOOK(gtk_shape->notebook), TRUE);
	gtk_notebook_popup_enable(GTK_NOTEBOOK(gtk_shape->notebook));
	gtk_widget_set_hexpand(GTK_WIDGET(gtk_shape->notebook), TRUE);
}

static void	gtk_set_shape_tabs_widgets(t_gtk_shape *gtk_shape, SCENE *scene,
										SHAPE *scene_shape)
{
	gtk_set_main_tab_widgets(&gtk_shape->main, scene_shape->dto);
	gtk_set_transform_tab_widgets(&gtk_shape->transform,
		&scene_shape->dto->transform);
	gtk_set_material_tab_widgets(&gtk_shape->material,
		&scene_shape->dto->material);
	gtk_set_color_tab_widgets(&gtk_shape->color,
		&scene_shape->dto->material.color);
	gtk_set_texture_tab_widgets(&gtk_shape->texture,
		scene->textures, scene->normal_maps);
	gtk_set_sections_tab_widgets(&gtk_shape->section,
		scene_shape->dto->sections, scene_shape->dto->is_complex_section);
}

void		gtk_set_shape_widgets(t_gtk_shape **gtk_shape, SCENE *scene)
{
	SHAPE		*scene_shape;
	SHAPE		default_shape;
	DTO_SHAPE	default_dto_shape;

	if ((*gtk_shape = (t_gtk_shape*)malloc(sizeof(t_gtk_shape))) == NULL)
		ft_error("Can't allocate memory");
	scene_shape = scene->shapes;
	(*gtk_shape)->shape = scene_shape;
	default_dto_shape.type = SPHERE;
	if (!scene_shape)
		scene_shape = get_default_shape(&default_shape, &default_dto_shape);
	gtk_set_shape_base_widgets(*gtk_shape, scene_shape->name);
	gtk_set_shape_tabs_widgets(*gtk_shape, scene, scene_shape);
}
