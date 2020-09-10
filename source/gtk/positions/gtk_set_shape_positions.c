/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_positions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:30 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_shape_tabs_positions(t_gtk_shape *shape)
{
	gtk_notebook_insert_page(GTK_NOTEBOOK(shape->notebook),
		shape->main.grid, shape->main.label, MAIN_TAB);
	gtk_notebook_insert_page(GTK_NOTEBOOK(shape->notebook),
		shape->transform.v_box, shape->transform.label, TRANSFORM_TAB);
	gtk_notebook_insert_page(GTK_NOTEBOOK(shape->notebook),
		shape->material.grid, shape->material.label, MATERIAL_TAB);
	gtk_notebook_insert_page(GTK_NOTEBOOK(shape->notebook),
		shape->color.scrolled_window, shape->color.label, TEXTURE_COLOR_TAB);
	gtk_notebook_insert_page(GTK_NOTEBOOK(shape->notebook),
		shape->section.grid, shape->section.label, SECTION_TAB);
}

void		gtk_set_shape_positions(t_gtk_shape *shape)
{
	gtk_container_add(GTK_CONTAINER(shape->expander), shape->frame);
	gtk_container_add(GTK_CONTAINER(shape->frame), shape->notebook);
	gtk_set_shape_main_positions(&shape->main);
	gtk_set_shape_transform_positions(&shape->transform);
	gtk_set_shape_material_positions(&shape->material);
	gtk_set_shape_texture_positions(&shape->texture);
	gtk_set_shape_color_positions(&shape->color, &shape->texture);
	gtk_set_shape_section_positions(&shape->section);
	gtk_set_shape_tabs_positions(shape);
}
