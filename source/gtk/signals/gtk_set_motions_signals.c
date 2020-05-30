/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_motions_signals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:39:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:46:35 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_motions_signals(GtkWidget *window, GtkWidget *image_event_box,
								t_rt *rt)
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
