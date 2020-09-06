/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_light_intensity_changer.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_light_intensity_changer_safe(gpointer data)
{
	t_rt		*rt;
	cl_float	*intensity;

	rt = (t_rt*)data;
	ASSERT_LIGHT(rt->gtk->ui.light->light);
	intensity = &rt->gtk->ui.light->light->dto->intensity;
	*intensity = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
									rt->gtk->ui.light->intensity.spin));
	rt->info->update_lights = TRUE;
	update_lights_arg(rt->ocl, &rt->info->update_l_cnt,
					&rt->info->update_lights);
	rt->info->update = TRUE;
	return (FALSE);
}

void			spin_button_light_intensity_changer(GtkSpinButton *button,
													gpointer data)
{
	(void)button;
	g_idle_add(spin_button_light_intensity_changer_safe, data);
}
