/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_widgets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:28:46 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:28:47 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	show_widgets(t_rt *rt)
{
	FILTER	filter;

	gtk_widget_show_all(rt->gtk->window);
	filter = rt->scene->filter;
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
	if (IS_APPLE)
	{
		gtk_widget_set_visible(rt->gtk->ui.settings.mirror.label, FALSE);
		gtk_widget_set_visible(rt->gtk->ui.settings.mirror.spin, FALSE);
	}
}
