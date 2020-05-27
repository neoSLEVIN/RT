/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shapes_positions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 22:43:51 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/28 20:23:41 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_shape_positions(t_gtk_shape *shape)
{
	gtk_container_add(GTK_CONTAINER(shape->expander), shape->notebook);
	gtk_grid_attach(GTK_GRID(shape->transform.grid), shape->transform.label_pos,
		0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(shape->transform.grid),
		shape->transform.label_x, shape->transform.label_pos,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(shape->transform.grid),
		shape->transform.label_y, shape->transform.label_x,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(shape->transform.grid),
		shape->transform.label_z, shape->transform.label_y,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(shape->transform.grid),
		shape->transform.spin_x, shape->transform.label_x, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(shape->transform.grid),
		shape->transform.spin_y, shape->transform.label_y, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(shape->transform.grid),
		shape->transform.spin_z, shape->transform.label_z, GTK_POS_RIGHT, 1, 1);
	gtk_notebook_append_page(GTK_NOTEBOOK(shape->notebook),
		shape->transform.grid, shape->transform.label);
}

void	gtk_set_shapes_positions(t_gtk_shapes *shapes)
{
	gtk_container_add(GTK_CONTAINER(shapes->expander), shapes->scrolled_window);
	gtk_container_add(GTK_CONTAINER(shapes->scrolled_window), shapes->tree);
}
