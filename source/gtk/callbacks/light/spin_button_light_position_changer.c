/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_light_position_changer.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_light_position_changer_safe(gpointer data)
{
	t_rt		*rt;
	FLT3		*pos;
	t_gtk_light	*light;

	rt = (t_rt*)data;
	ASSERT_LIGHT(rt->gtk->ui.light->light);
	pos = &rt->gtk->ui.light->light->dto->position;
	light = rt->gtk->ui.light;
	pos->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(light->pos_x.spin));
	pos->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(light->pos_y.spin));
	pos->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(light->pos_z.spin));
	rt->info->update_lights = TRUE;
	update_lights_arg(rt->ocl, &rt->info->update_l_cnt,
					&rt->info->update_lights);
	rt->info->update = TRUE;
	return (FALSE);
}

void			spin_button_light_position_changer(GtkSpinButton *button,
													gpointer data)
{
	(void)button;
	g_idle_add(spin_button_light_position_changer_safe, data);
}
