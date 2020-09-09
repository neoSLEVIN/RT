/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_expander_callback.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:01 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:01 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	light_expander_callback(GObject *object, GParamSpec *param_spec,
								gpointer data)
{
	t_rt		*rt;
	GtkExpander	*expander;

	(void)param_spec;
	rt = (t_rt*)data;
	expander = GTK_EXPANDER(object);
	if (gtk_expander_get_expanded(expander))
	{
		if (rt->gtk->ui.light->light == NULL)
			return (gtk_expander_set_expanded(expander, FALSE));
		update_flags(&rt->info->update_l_name, &rt->info->update_l_params);
		g_idle_add(update_light_widget, rt);
	}
}
