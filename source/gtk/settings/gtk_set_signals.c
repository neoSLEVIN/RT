/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/20 20:29:11 by cschoen          ###   ########.fr       */
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

static void	gtk_set_signals_on_motions(GtkWidget *window,
										GtkWidget *image_event_box, t_rt *rt)
{
	g_signal_connect(G_OBJECT(window), "key-press_event",
					G_CALLBACK(escape_window), NULL);
	g_signal_connect(G_OBJECT(window), "key-press_event",
					G_CALLBACK(press_key_on_window), rt);
	g_signal_connect(G_OBJECT(window), "key-release_event",
					G_CALLBACK(release_key_on_window), rt);
	g_signal_connect(G_OBJECT(image_event_box), "button-press-event",
					G_CALLBACK(press_button_on_image_event_box), rt);
	g_signal_connect(G_OBJECT(image_event_box), "button-release-event",
					G_CALLBACK(release_button_on_image_event_box), rt);
	g_signal_connect(G_OBJECT(image_event_box), "motion_notify_event",
					G_CALLBACK(motion_button_on_image_event_box), rt);
	g_signal_connect(G_OBJECT(image_event_box), "scroll-event",
					G_CALLBACK(scroll_on_image_event_box), rt);
}

static void	gtk_set_signals_on_ui_settings(t_gtk_settings *settings, t_rt *rt)
{
	g_signal_connect(G_OBJECT(settings->fps_scale), "value-changed",
					G_CALLBACK(fps_scale_moved), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(settings->y_axis), "toggled",
					G_CALLBACK(change_axis), &rt->info->axis.y);
	g_signal_connect(GTK_TOGGLE_BUTTON(settings->x_axis), "toggled",
					G_CALLBACK(change_axis), &rt->info->axis.x);
}

void		gtk_set_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->ui.settings.expander),
			"notify::expanded", G_CALLBACK(expander_callback), NULL);
	gtk_set_signals_on_motions(rt->gtk->window,
								rt->gtk->img.image_event_box, rt);
	gtk_set_signals_on_ui_settings(&rt->gtk->ui.settings, rt);
	rt->gtk->timeout_id =
		g_timeout_add(1000 / rt->scene->fps, draw_by_timeout, rt);
}
