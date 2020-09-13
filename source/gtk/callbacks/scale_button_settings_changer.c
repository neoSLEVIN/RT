/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_button_settings_changer.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amace-ty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:06:48 by amace-ty          #+#    #+#             */
/*   Updated: 2020/09/11 15:06:49 by amace-ty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	mirror_scale_moved_safe(gpointer data)
{
	t_rt		*rt;
	t_spinner	*mirror;

	rt = (t_rt*)data;
	mirror = &rt->gtk->ui.settings.mirror;
	rt->scene->mirror =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(mirror->spin));
	update_mirror_arg(rt->ocl);
	rt->info->update = TRUE;
	return (FALSE);
}

void			mirror_scale_moved(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(mirror_scale_moved_safe, data);
}

static gboolean	step_angle_scale_moved_safe(gpointer data)
{
	t_rt		*rt;
	t_spinner	*step;
	t_spinner	*angle;

	rt = (t_rt*)data;
	step = &rt->gtk->ui.settings.step;
	angle = &rt->gtk->ui.settings.angle;
	rt->scene->step =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(step->spin));
	rt->scene->angle =
		deg_to_rad(gtk_spin_button_get_value(GTK_SPIN_BUTTON(angle->spin)));
	return (FALSE);
}

void			step_angle_scale_moved(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(step_angle_scale_moved_safe, data);
}
