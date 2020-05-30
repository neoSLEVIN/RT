/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_scroll_locker.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:11:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:11:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	spin_button_scroll_locker(GtkWidget *widget, GdkEvent *event,
									gpointer data)
{
	(void)event;
	(void)data;
	g_signal_stop_emission_by_name(widget, "scroll-event");
	return (FALSE);
}
