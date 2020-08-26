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

static void	gtk_set_base_positions(t_gtk *gtk)
{
	gtk_container_add(GTK_CONTAINER(gtk->window), gtk->window_h_box);
	gtk_box_pack_start(GTK_BOX(gtk->window_h_box),
		GTK_WIDGET(gtk->img.image_event_box), FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(gtk->img.image_event_box),
		GTK_WIDGET(gtk->img.image));
	gtk_box_pack_start(GTK_BOX(gtk->window_h_box),
		gtk->ui.scrolled_window, FALSE, TRUE, 0);
}

static void	gtk_set_ui_positions(t_ui *ui)
{
	gtk_container_add(GTK_CONTAINER(ui->scrolled_window), ui->grid);
	gtk_grid_attach(GTK_GRID(ui->grid), ui->buttons.grid,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->camera.expander,
		ui->buttons.grid, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->shape->expander,
		ui->camera.expander, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->shapes.expander,
		ui->shape->expander, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->light->expander,
		ui->shapes.expander, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->lights.expander,
		ui->light->expander, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->texture.expander,
		ui->lights.expander, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->normals.expander,
		ui->texture.expander, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(ui->grid), ui->settings.expander,
		ui->normals.expander, GTK_POS_BOTTOM, 2, 1);
}

void		gtk_set_positions(t_gtk *gtk)
{
	gtk_set_base_positions(gtk);
	gtk_set_buttons_positions(&gtk->ui.buttons);
	gtk_set_camera_positions(&gtk->ui.camera);
	gtk_set_shape_positions(gtk->ui.shape);
	gtk_set_shapes_positions(&gtk->ui.shapes);
	gtk_set_light_positions(gtk->ui.light);
	gtk_set_lights_positions(&gtk->ui.lights);
	gtk_set_textures_positions(&gtk->ui.texture);
	gtk_set_textures_positions(&gtk->ui.normals);
	gtk_set_settings_positions(&gtk->ui.settings);
	gtk_set_ui_positions(&gtk->ui);
}
