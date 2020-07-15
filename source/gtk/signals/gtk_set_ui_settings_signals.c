/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_ui_settings_signals.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:42:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:43:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	changing_filter_type(GtkComboBox *filter_combo, gpointer data)
{
	t_rt	*rt;
	cl_int	err;

	rt = (t_rt*)data;
	rt->scene->filter = gtk_combo_box_get_active(filter_combo);
	err = clSetKernelArg(rt->ocl->kernel, 10, sizeof(FILTER),
			rt->ocl->dto.filter);
	check_error_cl(err,"clSetKernelArg", "filter");
	draw_image(rt);
}

void	gtk_set_ui_settings_signals(t_gtk_settings *settings, t_rt *rt)
{
	g_signal_connect(G_OBJECT(settings->fps_scale), "value-changed",
		G_CALLBACK(fps_scale_moved), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(settings->y_axis), "toggled",
		G_CALLBACK(change_axis), &rt->info->axis.y);
	g_signal_connect(GTK_TOGGLE_BUTTON(settings->x_axis), "toggled",
		G_CALLBACK(change_axis), &rt->info->axis.x);
	g_signal_connect(G_OBJECT(settings->filter_combo), "changed",
					 G_CALLBACK(changing_filter_type), rt);
}
