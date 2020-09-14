/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_settings_widgets.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:14:53 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:46 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_settings_widgets(t_gtk_settings *settings, t_rt *rt)
{
	settings->expander = gtk_expander_new_with_mnemonic("S_ettings");
	settings->v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	settings->grid_scale_params = gtk_grid_new();
	gtk_set_spinner(&settings->mirror, (INT2){1, 5},
		rt->scene->mirror, "Mirror:");
	settings->step = gtk_set_spinner_float("Step:", (FLT2){0.01f, 1.0f},
		rt->scene->step, 0.01f);
	settings->angle = gtk_set_spinner_float("Angle:", (FLT2){0.1f, 1.0f},
		rad_to_deg(rt->scene->angle), 0.05f);
	settings->grid = gtk_grid_new();
	settings->anti_aliasing = gtk_check_button_new_with_label("Anti-aliasing");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(settings->anti_aliasing),
								(_Bool)rt->scene->anti_aliasing);
	gtk_set_setting_filter_widgets(settings, rt);
}
