/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shapes_positions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 22:43:51 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 06:14:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_shape_transform_positions(t_transform_tab *transform)
{
	gtk_grid_attach(GTK_GRID(transform->grid), transform->label_pos,
		0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(transform->grid), transform->x.label,
		transform->label_pos, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(transform->grid), transform->y.label,
		transform->x.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(transform->grid), transform->z.label,
		transform->y.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(transform->grid), transform->x.spin,
		transform->x.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(transform->grid), transform->y.spin,
		transform->y.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(transform->grid), transform->z.spin,
		transform->z.label, GTK_POS_RIGHT, 1, 1);
}

void	gtk_set_shape_material_positions(t_material_tab *material)
{
	gtk_grid_attach(GTK_GRID(material->grid), material->transparency.label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->reflective.label, material->transparency.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->specular.label, material->reflective.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->transparency.spin, material->transparency.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->reflective.spin, material->reflective.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->specular.spin, material->specular.label,
		GTK_POS_RIGHT, 1, 1);
}


void	gtk_set_shape_section_positions(t_section_tab *section)
{
	gtk_grid_attach(GTK_GRID(section->grid), section->scrolled_window,
		0, 0, 1, 1);
	gtk_container_add(GTK_CONTAINER(section->scrolled_window), section->tree);
}


void	gtk_set_shape_positions(t_gtk_shape *shape)
{
	gtk_container_add(GTK_CONTAINER(shape->expander), shape->frame);
	gtk_container_add(GTK_CONTAINER(shape->frame), shape->notebook);

	gtk_set_shape_transform_positions(&shape->transform);
	gtk_set_shape_material_positions(&shape->material);
	gtk_set_shape_section_positions(&shape->section);

	gtk_notebook_append_page(GTK_NOTEBOOK(shape->notebook),
		shape->transform.grid, shape->transform.label);
	gtk_notebook_append_page(GTK_NOTEBOOK(shape->notebook),
		shape->material.grid, shape->material.label);
	gtk_notebook_append_page(GTK_NOTEBOOK(shape->notebook),
		shape->section.grid, shape->section.label);
}

void	gtk_set_shapes_positions(t_gtk_shapes *shapes)
{
	gtk_container_add(GTK_CONTAINER(shapes->expander), shapes->scrolled_window);
	gtk_container_add(GTK_CONTAINER(shapes->scrolled_window), shapes->tree);
}
