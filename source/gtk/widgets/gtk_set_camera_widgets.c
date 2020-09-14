/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_camera_widgets.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:25 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_camera_widgets(t_gtk_camera *gtk_camera, CAMERA *cam)
{
	gtk_camera->expander = gtk_expander_new_with_mnemonic("Came_ra");
	gtk_camera->grid = gtk_grid_new();
	gtk_camera->y_axis = gtk_check_button_new_with_label("Invert Y-axis");
	gtk_widget_set_halign(gtk_camera->y_axis, GTK_ALIGN_CENTER);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_camera->y_axis), FALSE);
	gtk_camera->separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_widget_set_valign(gtk_camera->separator, GTK_ALIGN_FILL);
	gtk_widget_set_halign(gtk_camera->separator, GTK_ALIGN_CENTER);
	gtk_camera->x_axis = gtk_check_button_new_with_label("Invert X-axis");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_camera->x_axis), FALSE);
	gtk_camera->display_frame = gtk_frame_new("Display");
	gtk_camera->display_grid = gtk_grid_new();
	gtk_set_spinner(&gtk_camera->display_width, (INT2){MIN_WIDTH, COLS},
				cam->display.x, "Width:");
	gtk_set_spinner(&gtk_camera->display_height, (INT2){MIN_HEIGHT, ROWS},
				cam->display.y, "Height:");
	gtk_set_spinner(&gtk_camera->fov, (INT2){10, 160},
				cam->fov, "FOV:");
	gtk_set_spinner(&gtk_camera->fps, (INT2){1, 80},
				cam->fps, "FPS:");
	gtk_camera->pos_expander = gtk_expander_new("Camera position");
	gtk_camera->pos_grid = gtk_grid_new();
	gtk_set_float_spinner(&gtk_camera->pos[0], "X:", cam->dto->origin.x);
	gtk_set_float_spinner(&gtk_camera->pos[1], "Y:", cam->dto->origin.y);
	gtk_set_float_spinner(&gtk_camera->pos[2], "Z:", cam->dto->origin.z);
}
