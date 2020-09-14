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
	t_changer	*mirror;

	rt = (t_rt*)data;
	mirror = &rt->gtk->ui.settings.mirror;
	rt->scene->mirror = GTK_CHANGER_GET_VALUE(mirror->change);
	update_mirror_arg(rt->ocl);
	rt->info->update = TRUE;
	return (FALSE);
}

void			mirror_scale_moved(GtkWidget *button, gpointer data)
{
	(void)button;
	g_idle_add(mirror_scale_moved_safe, data);
}

static gboolean	step_angle_scale_moved_safe(gpointer data)
{
	t_rt		*rt;
	t_changer	*step;
	t_changer	*angle;

	rt = (t_rt*)data;
	step = &rt->gtk->ui.settings.step;
	angle = &rt->gtk->ui.settings.angle;
	rt->scene->step = GTK_CHANGER_GET_VALUE(step->change);
	rt->scene->angle = deg_to_rad(GTK_CHANGER_GET_VALUE(angle->change));
	return (FALSE);
}

void			step_angle_scale_moved(GtkWidget *button, gpointer data)
{
	(void)button;
	g_idle_add(step_angle_scale_moved_safe, data);
}
