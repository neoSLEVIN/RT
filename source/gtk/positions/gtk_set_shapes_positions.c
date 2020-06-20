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
	gtk_container_add(GTK_CONTAINER(section->scrolled_window), section->grid);

	gtk_grid_attach(GTK_GRID(section->grid), section->style_frame,
					0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->grid), section->centre_button,
		section->style_frame, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->grid), section->tree,
		section->style_frame, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->grid), section->pos_grid,
		section->tree, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->grid), section->addition_v_box,
							section->pos_grid, GTK_POS_RIGHT, 1, 1);

	gtk_container_add(GTK_CONTAINER(section->style_frame), section->style_grid);
	gtk_grid_attach(GTK_GRID(section->style_grid), section->style_simple,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->style_grid), section->style_complex,
		section->style_simple, GTK_POS_RIGHT, 1, 1);

	gtk_grid_attach(GTK_GRID(section->pos_grid), section->pos_label,
					0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->pos_grid), section->pos_x.label,
							section->pos_label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->pos_grid), section->pos_y.label,
							section->pos_x.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->pos_grid), section->pos_z.label,
							section->pos_y.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->pos_grid), section->pos_x.spin,
							section->pos_x.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->pos_grid), section->pos_y.spin,
							section->pos_y.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->pos_grid), section->pos_z.spin,
							section->pos_z.label, GTK_POS_RIGHT, 1, 1);


	gtk_box_pack_start(GTK_BOX(section->addition_v_box),
					   GTK_WIDGET(section->plane_grid), FALSE, FALSE, 0);
	gtk_grid_attach(GTK_GRID(section->plane_grid), section->dir_label,
					0, 0, 3, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->plane_grid), section->spin_dir_x,
							section->dir_label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->plane_grid), section->spin_dir_y,
							section->spin_dir_x, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->plane_grid), section->spin_dir_z,
							section->spin_dir_y, GTK_POS_BOTTOM, 1, 1);



	gtk_box_pack_start(GTK_BOX(section->addition_v_box),
					   GTK_WIDGET(section->sphere_grid), FALSE, FALSE, 0);
	gtk_grid_attach(GTK_GRID(section->sphere_grid), section->radius.label,
					0, 0, 3, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->sphere_grid), section->radius.spin,
							section->radius.label, GTK_POS_BOTTOM, 1, 1);

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
		shape->section.scrolled_window, shape->section.label);
}

void	gtk_set_shapes_positions(t_gtk_shapes *shapes)
{
	gtk_container_add(GTK_CONTAINER(shapes->expander), shapes->scrolled_window);
	gtk_container_add(GTK_CONTAINER(shapes->scrolled_window), shapes->tree);
}
