/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_positions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/26 23:09:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_textures_positions(t_gtk_textures *textures)
{
	gtk_container_add(GTK_CONTAINER(textures->expander),
		textures->scrolled_window);
	gtk_container_add(GTK_CONTAINER(textures->scrolled_window), textures->tree);
}

void	gtk_set_ui_positions(t_ui *ui)
{
	gtk_container_add(GTK_CONTAINER(ui->scrolled_window), ui->grid);
	gtk_grid_attach(GTK_GRID(ui->grid), ui->shape->expander,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->shapes.expander,
		ui->shape->expander, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->texture.expander,
		ui->shapes.expander, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->normals.expander,
		ui->texture.expander, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->settings.expander,
		ui->normals.expander, GTK_POS_BOTTOM, 1, 1);
}

void	gtk_set_positions(t_gtk *gtk)
{
	gtk_container_add(GTK_CONTAINER(gtk->window), gtk->window_h_box);

	gtk_box_pack_start(GTK_BOX(gtk->window_h_box),
		GTK_WIDGET(gtk->img.image_event_box), FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(gtk->img.image_event_box),
		GTK_WIDGET(gtk->img.image));

	gtk_box_pack_start(GTK_BOX(gtk->window_h_box),
					gtk->ui.scrolled_window, FALSE, TRUE, 0);

	gtk_set_shape_positions(gtk->ui.shape);
	gtk_set_shapes_positions(&gtk->ui.shapes);
	gtk_set_textures_positions(&gtk->ui.texture);
	gtk_set_textures_positions(&gtk->ui.normals);
	gtk_set_settings_positions(&gtk->ui.settings);
	gtk_set_ui_positions(&gtk->ui);
}
