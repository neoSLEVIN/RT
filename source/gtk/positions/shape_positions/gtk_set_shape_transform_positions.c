/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_transform_positions.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:08 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_shape_transform_position_positions(t_transform_tab *tab)
{
	gtk_grid_attach(GTK_GRID(tab->pos_grid), tab->label_pos,
		0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->pos_grid), tab->x.label,
		tab->label_pos, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->pos_grid), tab->y.label,
		tab->x.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->pos_grid), tab->z.label,
		tab->y.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->pos_grid), tab->x.spin,
		tab->x.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->pos_grid), tab->y.spin,
		tab->y.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->pos_grid), tab->z.spin,
		tab->z.label, GTK_POS_RIGHT, 1, 1);
}

static void	gtk_set_shape_transform_dots_positions(t_transform_tab *tab)
{
	gtk_grid_attach(GTK_GRID(tab->dots_grid), tab->a[0].label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->b[0].label,
		tab->a[0].label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->c[0].label,
		tab->b[0].label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->a[0].spin,
		tab->a[0].label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->a[1].spin,
		tab->a[0].spin, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->a[2].spin,
		tab->a[1].spin, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->b[0].spin,
		tab->b[0].label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->b[1].spin,
		tab->b[0].spin, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->b[2].spin,
		tab->b[1].spin, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->c[0].spin,
		tab->c[0].label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->c[1].spin,
		tab->c[0].spin, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->dots_grid), tab->c[2].spin,
		tab->c[1].spin, GTK_POS_BOTTOM, 1, 1);
}

void		gtk_set_shape_transform_positions(t_transform_tab *tab)
{
	gtk_set_shape_transform_position_positions(tab);
	gtk_container_add(GTK_CONTAINER(GTK_EXPANDER(tab->dots_expander)),
					tab->dots_grid);
	gtk_set_shape_transform_dots_positions(tab);
	gtk_box_pack_start(GTK_BOX(tab->v_box), tab->pos_grid,
					FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(tab->v_box), tab->dots_expander,
					FALSE, FALSE, 0);
}
