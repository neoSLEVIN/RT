/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:30:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 18:11:05 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	check_escape(GtkWidget *button, GdkEventKey *event,
							gpointer data)
{
	if (event->keyval == GDK_KEY_Escape)
		gtk_main_quit();
	else if (event->keyval == 'w' || event->keyval == 's' ||
		event->keyval == 'a' || event->keyval == 'd')
		draw_image(button, data);
	return (FALSE);
}

static gboolean	wrapper(GtkWidget *button, GdkEventKey *event, gpointer data)
{
	if (event->keyval == 'u')
		draw_image(button, data);
	return (FALSE);
}

void	gtk_set_signals(GTK_DATA *gtk)
{
	g_signal_connect(G_OBJECT(gtk->window), "key_press_event",
		G_CALLBACK(check_escape), &gtk->rt);
	g_signal_connect(G_OBJECT(gtk->button), "pressed",
		G_CALLBACK(draw_image), &gtk->rt);
	g_signal_connect(G_OBJECT(gtk->button), "key-press-event",
		G_CALLBACK(wrapper), &gtk->rt);
}
