/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_camera_positions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:15 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:16 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_camera_display_positions(t_gtk_camera *camera)
{
	gtk_container_add(GTK_CONTAINER(camera->display_frame),
		GTK_WIDGET(camera->display_grid));
	gtk_grid_attach(GTK_GRID(camera->display_grid),
		camera->display_width.label, 0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->display_grid),
		camera->display_width.spin, camera->display_width.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->display_grid),
		camera->display_height.label, camera->display_width.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->display_grid),
		camera->display_height.spin, camera->display_height.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->display_grid),
		camera->fov.label, camera->display_height.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->display_grid),
		camera->fov.spin, camera->fov.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->display_grid),
		camera->fps.label, camera->fov.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->display_grid),
		camera->fps.spin, camera->fps.label,
		GTK_POS_RIGHT, 1, 1);
}

static void	gtk_set_camera_position_positions(t_gtk_camera *camera)
{
	gtk_container_add(GTK_CONTAINER(camera->pos_expander),
		GTK_WIDGET(camera->pos_grid));
	gtk_grid_attach(GTK_GRID(camera->pos_grid), camera->pos[0].label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->pos_grid), camera->pos[0].spin,
		camera->pos[0].label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->pos_grid), camera->pos[1].label,
		camera->pos[0].label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->pos_grid), camera->pos[1].spin,
		camera->pos[1].label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->pos_grid), camera->pos[2].label,
		camera->pos[1].label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->pos_grid), camera->pos[2].spin,
		camera->pos[2].label, GTK_POS_RIGHT, 1, 1);
}

void		gtk_set_camera_positions(t_gtk_camera *camera)
{
	gtk_container_add(GTK_CONTAINER(camera->expander),
		GTK_WIDGET(camera->grid));
	gtk_set_camera_display_positions(camera);
	gtk_set_camera_position_positions(camera);
	gtk_grid_attach(GTK_GRID(camera->grid), camera->pos_expander,
		0, 0, 6, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->grid), camera->y_axis,
		camera->pos_expander, GTK_POS_BOTTOM, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->grid), camera->separator,
		camera->y_axis, GTK_POS_RIGHT, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->grid), camera->x_axis,
		camera->separator, GTK_POS_RIGHT, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(camera->grid), camera->display_frame,
		camera->y_axis, GTK_POS_BOTTOM, 6, 1);
}
