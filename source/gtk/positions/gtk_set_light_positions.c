/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_light_positions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_light_positions_main_grid(t_gtk_light *light)
{
	gtk_grid_attach(GTK_GRID(light->grid), light->name_label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->grid), light->name_changer,
		light->name_label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->grid), light->type_label,
		light->name_label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->grid), light->type_combo,
		light->type_label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->grid), light->intensity.label,
		light->name_changer, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->grid), light->intensity.spin,
		light->intensity.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->grid), light->params_frame,
		light->type_label, GTK_POS_BOTTOM, 4, 1);
}

static void	gtk_set_light_positions_pos_grid(t_gtk_light *light)
{
	gtk_grid_attach(GTK_GRID(light->pos_grid), light->pos_label,
		0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->pos_grid), light->pos_x.label,
		light->pos_label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->pos_grid), light->pos_y.label,
		light->pos_x.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->pos_grid), light->pos_z.label,
		light->pos_y.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->pos_grid), light->pos_x.spin,
		light->pos_x.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->pos_grid), light->pos_y.spin,
		light->pos_y.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->pos_grid), light->pos_z.spin,
		light->pos_z.label, GTK_POS_RIGHT, 1, 1);
}

static void	gtk_set_light_positions_dir_grid(t_gtk_light *light)
{
	gtk_grid_attach(GTK_GRID(light->dir_grid), light->dir_label,
		0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->dir_grid), light->dir_x.label,
		light->dir_label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->dir_grid), light->dir_y.label,
		light->dir_x.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->dir_grid), light->dir_z.label,
		light->dir_y.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->dir_grid), light->dir_x.spin,
		light->dir_x.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->dir_grid), light->dir_y.spin,
		light->dir_y.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(light->dir_grid), light->dir_z.spin,
		light->dir_z.label, GTK_POS_RIGHT, 1, 1);
}

void		gtk_set_light_positions(t_gtk_light *light)
{
	gtk_container_add(GTK_CONTAINER(light->expander), light->frame);
	gtk_container_add(GTK_CONTAINER(light->frame), light->grid);
	gtk_container_add(GTK_CONTAINER(light->params_frame), light->h_params);
	gtk_box_pack_start(GTK_BOX(light->h_params), light->pos_grid,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(light->h_params), light->dir_grid,
		FALSE, FALSE, 0);
	gtk_set_light_positions_main_grid(light);
	gtk_set_light_positions_pos_grid(light);
	gtk_set_light_positions_dir_grid(light);
}
