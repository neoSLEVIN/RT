/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 07:05:10 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

// TODO maybe delete this
static void	expander_callback(GObject *object, GParamSpec *param_spec,
								gpointer user_data)
{
	GtkExpander *expander;

	expander = GTK_EXPANDER(object);

	if (gtk_expander_get_expanded(expander))
	{
		// Show or create widgets
		ft_printf("open\n");
	}
	else
	{
		ft_printf("close\n");
		// Hide or destroy widgets
	}
}

void		gtk_set_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->ui.settings.expander),
			"notify::expanded", G_CALLBACK(expander_callback), NULL);
	gtk_set_motions_signals(rt->gtk->window, rt->gtk->img.image_event_box, rt);
	gtk_set_shape_signals(rt);
	gtk_set_shapes_signals(rt);
	gtk_set_ui_settings_signals(&rt->gtk->ui.settings, rt);
	rt->gtk->timeout_id =
		g_timeout_add(1000 / rt->scene->fps, draw_by_timeout, rt);
}
