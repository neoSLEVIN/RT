/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 05:24:23 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	real_draw_image(GtkWidget *button, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	draw_image(rt);
	rt->scene->cam.transform.position.z += 0.5;
	update_cam(rt);
}

static gboolean	check_escape(GtkWidget *button, GdkEventKey *event,
							gpointer data)
{
	if (event->keyval == GDK_KEY_Escape)
		gtk_main_quit();
	else if (event->keyval == 'w' || event->keyval == 's' ||
		event->keyval == 'a' || event->keyval == 'd')
		real_draw_image(button, data);
	return (FALSE);
}

static gboolean	wrapper(GtkWidget *button, GdkEventKey *event, gpointer data)
{
	if (event->keyval == 'u')
		real_draw_image(button, data);
	return (FALSE);
}

void	gtk_set_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-press_event",
		G_CALLBACK(check_escape), rt);
//	g_signal_connect(G_OBJECT(rt->gtk->button), "pressed",
//		G_CALLBACK(real_draw_image), rt);
//	g_signal_connect(G_OBJECT(rt->gtk->button), "key-press-event",
//		G_CALLBACK(wrapper), rt);
}
