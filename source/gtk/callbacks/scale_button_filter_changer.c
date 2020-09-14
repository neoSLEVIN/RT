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
	t_spinner	*blur;
	t_spinner	*sepia;
	t_spinner	*noise;

	rt = (t_rt*)data;
	blur = &rt->gtk->ui.settings.blur;
	sepia = &rt->gtk->ui.settings.sepia;
	noise = &rt->gtk->ui.settings.noise;
	rt->scene->filter_params.x =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(blur->spin));
	rt->scene->filter_params.y =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(sepia->spin));
	rt->scene->filter_params.z =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(noise->spin));
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
	return (FALSE);
}

void			filter_spin_button_changer(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(filter_spin_button_changer_safe, data);
}
