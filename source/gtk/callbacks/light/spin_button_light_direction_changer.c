/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_light_direction_changer.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	back_to_previous_values(t_gtk_light *light, FLT3 dir)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->dir_x.spin), dir.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->dir_y.spin), dir.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->dir_z.spin), dir.z);
	return (FALSE);
}

static gboolean	spin_button_light_direction_changer_safe(gpointer data)
{
	t_rt		*rt;
	t_gtk_light	*light;
	FLT3		temp_dir;

	rt = (t_rt*)data;
	ASSERT_LIGHT(rt->gtk->ui.light->light);
	light = rt->gtk->ui.light;
	temp_dir.x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(light->dir_x.spin));
	temp_dir.y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(light->dir_y.spin));
	temp_dir.z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(light->dir_z.spin));
	if (v3_length_sq(temp_dir) == 0.0f)
		return (back_to_previous_values(light, light->light->dto->direction));
	light->light->dto->direction = temp_dir;
	rt->info->update_lights = TRUE;
	update_lights_arg(rt->ocl, &rt->info->update_l_cnt,
					&rt->info->update_lights);
	rt->info->update = TRUE;
	return (FALSE);
}

void			spin_button_light_direction_changer(GtkSpinButton *button,
													gpointer data)
{
	(void)button;
	g_idle_add(spin_button_light_direction_changer_safe, data);
}
