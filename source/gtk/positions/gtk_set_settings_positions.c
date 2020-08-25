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

static void	gtk_set_filter_params_positions(t_gtk_settings *settings)
{
	gtk_box_pack_start(GTK_BOX(settings->v_filter_params), settings->h_blur,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->v_filter_params), settings->h_sepia,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->v_filter_params), settings->h_noise,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->h_blur), settings->blur_size.label,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->h_blur), settings->blur_size.spin,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->h_sepia), settings->sepia_depth.label,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->h_sepia), settings->sepia_depth.spin,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->h_noise), settings->noise_depth.label,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->h_noise), settings->noise_depth.spin,
						FALSE, FALSE, 0);
}

void		gtk_set_settings_positions(t_gtk_settings *settings)
{
	gtk_container_add(GTK_CONTAINER(settings->expander),
		GTK_WIDGET(settings->v_box));
	gtk_box_pack_start(GTK_BOX(settings->v_box), settings->grid,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(settings->v_box), settings->v_filter_params,
		FALSE, FALSE, 0);
	gtk_grid_attach(GTK_GRID(settings->grid), settings->fps_label, 0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->fps_scale,
		settings->fps_label, GTK_POS_RIGHT, 8, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->y_axis,
		settings->fps_label, GTK_POS_BOTTOM, 3, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->separator,
		settings->y_axis, GTK_POS_RIGHT, 3, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->x_axis,
		settings->separator, GTK_POS_RIGHT, 3, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->fov.label,
		settings->y_axis, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->fov.spin,
		settings->fov.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->filter_label,
		settings->fov.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->filter_combo,
		settings->filter_label, GTK_POS_RIGHT, 1, 1);
	gtk_set_filter_params_positions(settings);
}
