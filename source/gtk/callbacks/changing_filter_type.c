/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_filter_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:14 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:15 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	changing_filter_type(GtkComboBox *filter_combo, gpointer data)
{
	t_rt	*rt;
	cl_int	err;
	FILTER	filter;

	rt = (t_rt*)data;
	filter = gtk_combo_box_get_active(filter_combo);
	rt->scene->filter = filter;
	if (filter == BLUR || filter == SEPIA || filter == NOISE)
	{
		gtk_widget_set_visible(rt->gtk->ui.settings.v_filter_params, TRUE);
		gtk_widget_set_visible(rt->gtk->ui.settings.grid_blur,
								filter == BLUR);
		gtk_widget_set_visible(rt->gtk->ui.settings.grid_sepia,
								filter == SEPIA);
		gtk_widget_set_visible(rt->gtk->ui.settings.grid_noise,
								filter == NOISE);
	}
	else
		gtk_widget_set_visible(rt->gtk->ui.settings.v_filter_params, FALSE);
	err = clSetKernelArg(rt->ocl->kernel, 10, sizeof(FILTER),
						rt->ocl->dto.filter);
	check_error_cl(err, "clSetKernelArg", "filter");
	draw_image(rt);
}
