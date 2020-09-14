/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_button_filter_changer.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:26:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:26:40 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	filter_spin_button_changer_safe(gpointer data)
{
	t_rt		*rt;
	t_changer	*blur;
	t_changer	*sepia;
	t_changer	*noise;

	rt = (t_rt*)data;
	blur = &rt->gtk->ui.settings.blur;
	sepia = &rt->gtk->ui.settings.sepia;
	noise = &rt->gtk->ui.settings.noise;
	rt->scene->filter_params.x = GTK_CHANGER_GET_VALUE(blur->change);
	rt->scene->filter_params.y = GTK_CHANGER_GET_VALUE(sepia->change);
	rt->scene->filter_params.z = GTK_CHANGER_GET_VALUE(noise->change);
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
	return (FALSE);
}

void			filter_spin_button_changer(GtkWidget *button, gpointer data)
{
	(void)button;
	g_idle_add(filter_spin_button_changer_safe, data);
}
