/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_settings_positions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 22:40:57 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/26 22:40:57 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_scale_params_positions(t_gtk_settings *settings)
{
	gtk_grid_attach(GTK_GRID(settings->grid_scale_params),
		settings->mirror.label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_scale_params),
		settings->mirror.spin, settings->mirror.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_scale_params),
		settings->step.label, settings->mirror.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_scale_params),
		settings->step.spin, settings->step.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_scale_params),
		settings->angle.label, settings->step.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_scale_params),
		settings->angle.spin, settings->angle.label,
		GTK_POS_RIGHT, 1, 1);
}

static void	gtk_set_filter_params_positions(t_gtk_settings *settings)
{
	gtk_box_pack_start(GTK_BOX(settings->v_filter_params), settings->grid_blur,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->v_filter_params), settings->grid_sepia,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->v_filter_params), settings->grid_noise,
						FALSE, FALSE, 0);
	gtk_grid_attach(GTK_GRID(settings->grid_blur), settings->blur.label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_blur), settings->blur.spin,
		settings->blur.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach(GTK_GRID(settings->grid_sepia), settings->sepia.label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_sepia),
		settings->sepia.spin, settings->sepia.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach(GTK_GRID(settings->grid_noise), settings->noise.label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid_noise),
		settings->noise.spin, settings->noise.label,
		GTK_POS_RIGHT, 1, 1);
}

void		gtk_set_settings_positions(t_gtk_settings *settings)
{
	gtk_container_add(GTK_CONTAINER(settings->expander),
		GTK_WIDGET(settings->v_box));
	gtk_box_pack_start(GTK_BOX(settings->v_box), settings->grid_scale_params,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->v_box), settings->grid,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->v_box), settings->v_filter_params,
		FALSE, FALSE, 0);
	gtk_set_scale_params_positions(settings);
	gtk_grid_attach(GTK_GRID(settings->grid), settings->anti_aliasing,
		0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->filter_label,
		settings->anti_aliasing, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->filter_combo,
		settings->filter_label, GTK_POS_RIGHT, 1, 1);
	gtk_set_filter_params_positions(settings);
}
