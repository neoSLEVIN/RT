/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_section_positions.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:00 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:00 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_shape_section_base_positions(t_section_tab *section)
{
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
}

static void	gtk_set_shape_section_style_positions(t_section_tab *section)
{
	gtk_container_add(GTK_CONTAINER(section->style_frame), section->style_grid);
	gtk_grid_attach(GTK_GRID(section->style_grid), section->style_simple,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(section->style_grid),
		section->style_complex, section->style_simple,
		GTK_POS_RIGHT, 1, 1);
}

static void	gtk_set_shape_section_position_positions(t_section_tab *section)
{
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
}

static void	gtk_set_shape_section_addition_positions(t_section_tab *section)
{
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
	gtk_grid_attach_next_to(GTK_GRID(section->sphere_grid),
		section->radius.spin, section->radius.label,
		GTK_POS_BOTTOM, 1, 1);
}

void		gtk_set_shape_section_positions(t_section_tab *section)
{
	gtk_set_shape_section_base_positions(section);
	gtk_set_shape_section_style_positions(section);
	gtk_set_shape_section_position_positions(section);
	gtk_set_shape_section_addition_positions(section);
}
